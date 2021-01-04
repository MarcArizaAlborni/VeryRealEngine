#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "Definitions.h"
#include "ModuleInspector.h"
#include "ModuleRenderer3D.h"
#include "FileSystem.h"
#include "ModuleCamera3D.h"
#include "Component.h"
#include "ComponentCamera.h"
#include "ComponentMesh.h"
#include "ComponentListener.h"
#include "ComponentSource.h"
#include "ModuleAudio.h"
#include "ComponentTransform.h"
#include "ComponentTexture.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include "ModuleCamera3D.h"
#include "ModuleTextureImporter.h"
#include "ModuleEditor.h"
#include "libraries/Glew/include/GL/glew.h"
#include "libraries/SDL/include/SDL_opengl.h"
#include "Primitive.h"
#include "GameObject.h"
#include "ModuleMeshImporter.h"
#include "ModuleHierarchy.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ModuleTextureImporter.h"
#include "libraries/Wwise/IO/Win32/AkFilePackageLowLevelIOBlocking.h"
#include "libraries/imGuizmo/ImGuizmo.h"
#include "libraries/MathGeoLib/include/Geometry/LineSegment.h"
#include "..\Game\Assets\Audio\Wwise_IDs.h"
#include "ImportSettings.h"



#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleScene::ModuleScene(Application* app, const char* name, bool start_enabled) : Module(app, "Scene", start_enabled)
{
	

}

// Destructor
ModuleScene::~ModuleScene()
{}

// Called before render is available
bool ModuleScene::Init()
{


	LOG("Creating Scene context");
	bool ret = true;
	ROOT_SCENE_OBJECT = new Game_Object("MainScene");
	App->geometrymanager->ObjectsOnScene.push_back(ROOT_SCENE_OBJECT);
	ROOT_SCENE_OBJECT->Parent = nullptr;

	object_scene_camera = new Game_Object("Scene Camera");
	ROOT_SCENE_OBJECT->Children_List.push_back(object_scene_camera);
	object_scene_camera->Parent = ROOT_SCENE_OBJECT;

	ImGuizmo::Enable(true);
	return ret;
}

bool ModuleScene::Start()
{
	object_scene_camera->AddComponent(Component_Types::Listener);

	
	LoadMusicSource();


	object_scene_camera->AddExistingComponent(App->camera->scene_camera);

	App->textureImporter->TextureCheckers = App->textureImporter->LoadTextureImage("Assets/Models/Checkers/checkers.png");
	
	App->meshimporter->LoadFile_Mesh("Assets/Models/Street/Street_environment_V01.FBX");

	MusicPlaylistTimer.Start();
	MusicPlaylistTime = 0;
	PlayingMus1 = true;

	LoadDynamicSoundSource();

	LoadStaticSoundSource(); 

	LoadReverbSoundSource();
	
	return true;
}


// PreUpdate: clear buffer
update_status ModuleScene::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt)
{

	Plane2 p(0, 1, 0, 0);
	p.axis = true;

	if (App->editor->show_grid)
	{
		p.Render();
	}

	App->scene->GuizmoDrawn();


	
	//AudioControlls();
	
	//RotateMusics();


	return UPDATE_CONTINUE;
}


// PostUpdate present buffer to screen
update_status ModuleScene::PostUpdate(float dt)
{

	DynamicSourceMovement();


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearStencil(0);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleScene::CleanUp()
{
	LOG("Destroying Scene");


	return true;
}

bool ModuleScene::ResetScene()
{
	
	App->geometrymanager->ObjectsOnScene.clear();
	//SHOULD WE DELETE BUFFERS

	return true;
}

bool ModuleScene::LoadScene()
{
	ResetScene();

	return true;
}

void ModuleScene::SaveScene()
{

}

//Guizmo
void ModuleScene::GuizmoDrawn()
{
	if (App->editor->guizmos)
	{
		std::vector < Game_Object* >::iterator it = App->geometrymanager->ObjectsOnScene.begin();
		Game_Object* object_guizmo;

		for (int i = 0; i < App->geometrymanager->ObjectsOnScene.size(); ++i)
		{
			object_guizmo = *it;
			object_guizmo = LookForSelectedChild(object_guizmo);

			if (object_guizmo != nullptr)
			{
				if (object_guizmo->ToBeDrawInspector)
				{
					i = App->geometrymanager->ObjectsOnScene.size();
				}
			}
			++it;
		}

		if (object_guizmo != nullptr)
		{
			Component_Transform* selected_transform = (Component_Transform*)object_guizmo->GetComponent(Component_Types::Transform);

			float4x4 viewMatrix = App->camera->scene_camera->frustum.ViewMatrix();
			viewMatrix.Transpose();
			float4x4 projectionMatrix = App->camera->scene_camera->frustum.ProjectionMatrix();
			projectionMatrix.Transpose();
			float4x4 modelProjection = selected_transform->GetGlobalTransform();
			modelProjection.Transpose();

			ImGuizmo::SetRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

			//gizmoOperation
			float modelPtr[16];
			memcpy(modelPtr, modelProjection.ptr(), 16 * sizeof(float));
			ImGuizmo::MODE finalMode = (gizmoOperation == ImGuizmo::OPERATION::SCALE ? ImGuizmo::MODE::LOCAL : gizmoMode);
			ImGuizmo::Manipulate(viewMatrix.ptr(), projectionMatrix.ptr(), gizmoOperation, finalMode, modelPtr);


			if (ImGuizmo::IsUsing())
			{
				float4x4 newMatrix;
				newMatrix.Set(modelPtr);
				modelProjection = newMatrix.Transposed();


				//Set Global Transform 
				selected_transform->UpdateGlobalTransform();
			}
		}
	}	
			
}

void ModuleScene::ChangeOperationGuizmo(ImGuizmo::OPERATION& op)
{
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
		op = ImGuizmo::OPERATION::TRANSLATE;
	}
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
		op = ImGuizmo::OPERATION::ROTATE;
	}
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
		op = ImGuizmo::OPERATION::SCALE;
	}
}


void ModuleScene::RemoveSelectedItem(Game_Object* Object)
{
	std::vector<Game_Object*>::iterator It = Object->Children_List.begin();

	for (int i = 0; i < Object->Children_List.size(); ++i) {

		Game_Object* Obj = *It;

		++It;
		RemoveSelectedItem(Obj);

		if (ObjectToBeDeleted == Obj) {

			Object->DeleteSpecificChildren(Obj);

			App->hierarchy->ITEM_TO_BE_DELETED = false;
			delete Obj;
			Obj = nullptr;
			ObjectToBeDeleted = nullptr;
			i = Object->Children_List.size();
		}
	}
}

Game_Object* ModuleScene::LookForSelectedChild(Game_Object* obj)
{
	std::vector < Game_Object* >::iterator it = obj->Children_List.begin();
	Game_Object* object_guizmo;

	for (int i = 0;  i < obj->Children_List.size(); ++i)
	{
		object_guizmo = *it;

		if (object_guizmo->ToBeDrawInspector)
		{
			i = obj->Children_List.size(); 
			return object_guizmo;
		}

		object_guizmo = LookForSelectedChild(object_guizmo);
		if (object_guizmo != nullptr)
		{
			if (object_guizmo->ToBeDrawInspector)
			{
				i = obj->Children_List.size();
				return object_guizmo;
			}
		}
		
		++it;
	}

	return nullptr;
	
}

void ModuleScene::LoadStaticSoundSource()
{
	App->editor->Importer_Settings->GlobalScale = true;

	App->meshimporter->LoadFile_Mesh("Assets/Models/Penguin/Penguin.fbx");
	const char* path_file = "Assets/Textures/Penguin Diffuse Color.png";
	TextureInfo PengTex;

	PengTex = App->textureImporter->LoadTextureImage(path_file);

	App->textureImporter->AvailableTextures.push_back(&PengTex);


	Static_Source = ROOT_SCENE_OBJECT->Children_List[ROOT_SCENE_OBJECT->Children_List.size() - 1]->Children_List[0];

	Static_Source->ToBeDrawInspector = true;
	App->input->CheckSelectedChild(Static_Source, PengTex);
	Static_Source->ToBeDrawInspector = false;



	Static_Source->is_spatial_Origin = true;
	Static_Source->AddComponent(Component_Types::Source);
	


	Component_Source* StaticSource = (Component_Source*)Static_Source->GetComponent(Component_Types::Source);
	Component_Mesh* MeshStatic= (Component_Mesh*)Static_Source->Children_List[0]->GetComponent(Component_Types::Mesh);
	

	//Static_Source->Children_List[0];
	MeshStatic->UpdateOnTransformOBB();
	
	

	StaticSource->SetID(AK::EVENTS::PENGUIN_STATIC);
	

	StaticSource->WiseItem->PlayEvent(AK::EVENTS::PENGUIN_STATIC);

	App->editor->Importer_Settings->GlobalScale = false;
}

void ModuleScene::LoadDynamicSoundSource()
{
	App->editor->Importer_Settings->GlobalScale = true;
	App->editor->Importer_Settings->GlobalScale = true;
	App->editor->Importer_Settings->DesiredScaleZ = 2;

	App->meshimporter->LoadFile_Mesh("Assets/Models/Fish/fish.fbx");

	const char* path_file = "Assets/Textures/fish.png";
	TextureInfo PengTex;

	PengTex = App->textureImporter->LoadTextureImage(path_file);

	App->textureImporter->AvailableTextures.push_back(&PengTex);


	Dynamic_Source = ROOT_SCENE_OBJECT->Children_List[ROOT_SCENE_OBJECT->Children_List.size() - 1]->Children_List[0];

	Dynamic_Source->ToBeDrawInspector = true;
	App->input->CheckSelectedChild(Dynamic_Source, PengTex);
	Dynamic_Source->ToBeDrawInspector = false;

	App->editor->Importer_Settings->DesiredScaleZ = 1;
	App->editor->Importer_Settings->GlobalScale = false;

	Component_Transform* TransformDynamic = (Component_Transform*)Dynamic_Source->GetComponent(Component_Types::Transform);
	Component_Mesh* MeshDynamic = (Component_Mesh*)Dynamic_Source->GetComponent(Component_Types::Mesh);

	

	TransformDynamic->Scale = { 6,6,6 };
	TransformDynamic->UpdateTransformationsObjects(TransformDynamic->Translation, TransformDynamic->Scale, TransformDynamic->Rotation);
	MeshDynamic->UpdateOnTransformOBB();
	Dynamic_Source->is_spatial_Origin = true;
	Dynamic_Source->AddComponent(Component_Types::Source);

	Component_Source* DynamicSource = (Component_Source*)Dynamic_Source->GetComponent(Component_Types::Source);

	DynamicSource->SetID(AK::EVENTS::FISH_DYNAMIC);

	DynamicSource->WiseItem->PlayEvent(AK::EVENTS::FISH_DYNAMIC);

	//Remember to create the SPATIAL AUDIO==TRUE



}

void ModuleScene::LoadReverbSoundSource()
{
	App->editor->Importer_Settings->GlobalScale = true;
	App->editor->Importer_Settings->DesiredScaleX = 0.6;
	App->editor->Importer_Settings->DesiredScaleY = 0.6;
	App->editor->Importer_Settings->DesiredScaleZ = 0.6;


	App->meshimporter->LoadFile_Mesh("Assets/Models/Tunnel/Tunnel.fbx");

	Reverb_Source = ROOT_SCENE_OBJECT->Children_List[ROOT_SCENE_OBJECT->Children_List.size() - 1]->Children_List[0];
	Component_Transform* TransformReverb = (Component_Transform*)Reverb_Source->GetComponent(Component_Types::Transform);

	Reverb_Source->name = "Reverb Tunnel";
		

	App->editor->Importer_Settings->DesiredScaleX = 1;
	App->editor->Importer_Settings->DesiredScaleY = 1;
	App->editor->Importer_Settings->DesiredScaleZ = 1;
	App->editor->Importer_Settings->GlobalScale = false;

	TransformReverb->Translation = { -68,0,-156 };
	TransformReverb->UpdateTransformationsObjects(TransformReverb->Translation, TransformReverb->Scale, TransformReverb->Rotation);

	Component_Mesh* MeshReverb = (Component_Mesh*)Reverb_Source->GetComponent(Component_Types::Mesh);

	MeshReverb->UpdateOnTransformOBB();
}

void ModuleScene::LoadMusicSource()
{
	background_music = new Game_Object("THE DOOM SLEYAR");
	ROOT_SCENE_OBJECT->Children_List.push_back(background_music);
	background_music->Parent = ROOT_SCENE_OBJECT;

	background_music_2 = new Game_Object("THOMAS THE TRAIN");
	ROOT_SCENE_OBJECT->Children_List.push_back(background_music_2);
	background_music_2->Parent = ROOT_SCENE_OBJECT;


	background_music->AddComponent(Component_Types::Source);
	background_music_2->AddComponent(Component_Types::Source);


	Component_Source* musicSource = (Component_Source*)background_music->GetComponent(Component_Types::Source);
	Component_Source* musicSource2 = (Component_Source*)background_music_2->GetComponent(Component_Types::Source);



	musicSource->SetID(AK::EVENTS::FIRST30);
	musicSource2->SetID(AK::EVENTS::SECOND30);

	musicSource->WiseItem->PlayEvent(AK::EVENTS::FIRST30);
	musicSource->isPlaying = true;



}

void ModuleScene::RotateMusics()
{
	Component_Source* temp = (Component_Source*)background_music->GetComponent(Component_Types::Source);
	Component_Source* temp2 = (Component_Source*)background_music_2->GetComponent(Component_Types::Source);


	if (MusicPlaylistTimer.ReadSec() > MusicPlaylistTime + 30) {
		SwapMusic = true;
	}


	if (SwapMusic == true) {

		MusicPlaylistTime = MusicPlaylistTimer.ReadSec();

		if (PlayingMus1) {

			temp->WiseItem->PauseEvent(AK::EVENTS::FIRST30);

			PlayingMus1 = false;
			PlayingMus2 = true;

			if (StartMusic2) {
				StartMusic2 = false;
				temp2->WiseItem->PlayEvent(AK::EVENTS::SECOND30);
				MusicPlaylistTime = MusicPlaylistTimer.ReadSec();
			}
			else {
				temp2->WiseItem->ResumeEvent(AK::EVENTS::SECOND30);
				MusicPlaylistTime = MusicPlaylistTimer.ReadSec();
			}



		}
		else if (PlayingMus2) {

			temp2->WiseItem->PauseEvent(AK::EVENTS::SECOND30);
			PlayingMus1 = true;
			PlayingMus2 = false;

			temp->WiseItem->ResumeEvent(AK::EVENTS::FIRST30);

			MusicPlaylistTime = MusicPlaylistTimer.ReadSec();

		}

		SwapMusic = false;


	}
}

void ModuleScene::AudioControlls()
{
	//Audio ------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
	{
		Component_Source* temp = (Component_Source*) background_music->GetComponent(Component_Types::Source);

		temp->isPlaying = false;
		temp->isPaused = false;
		temp->WiseItem->StopEvent(AK::EVENTS::FIRST30);
	}

	if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
	{

		Component_Source* temp = (Component_Source*)background_music->GetComponent(Component_Types::Source);

		if (temp->isPaused)
		{
			temp->isPlaying = true;
			temp->isPaused = false;
			temp->WiseItem->PlayEvent(AK::EVENTS::FIRST30);
		}

	}


	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		Component_Source* temp = (Component_Source*)background_music->GetComponent(Component_Types::Source);

		if (temp->isPlaying)
		{
			temp->isPlaying = false;
			temp->isPaused = true;
			temp->WiseItem->PauseEvent(AK::EVENTS::FIRST30);
		}
		else if (temp->isPaused)
		{
			temp->isPlaying = true;
			temp->isPaused = false;
			temp->WiseItem->ResumeEvent(AK::EVENTS::FIRST30);
		}
	}


	
}

void ModuleScene::DynamicSourceMovement()
{

	Component_Transform* TransformStatic=(Component_Transform*)Dynamic_Source->GetComponent(Component_Types::Transform);

	
	

	if (In_Pos1 == false) {
		TransformStatic->Translation=MoveDynamicSourceTo(PositionSq1, TransformStatic->Translation);
		
		TransformStatic->EulerRot = { -90, 90, 0 };
		Quat NewRot = Quat::FromEulerXYZ(TransformStatic->EulerRot.x, TransformStatic->EulerRot.y, TransformStatic->EulerRot.z);
		TransformStatic->SetEulerRotation(TransformStatic->EulerRot);

		//WORKING

	}
	else if (In_Pos2 == false) {

		TransformStatic->Translation= MoveDynamicSourceTo(PositionSq2, TransformStatic->Translation);

		//TransformStatic->EulerRot = { 0,0,0 };
		Quat NewRot = Quat::FromEulerXYZ(TransformStatic->EulerRot.x, TransformStatic->EulerRot.y, TransformStatic->EulerRot.z);
		TransformStatic->SetEulerRotation(TransformStatic->EulerRot);


	}
	else if (In_Pos3 == false) {
		TransformStatic->Translation= MoveDynamicSourceTo(PositionSq3, TransformStatic->Translation);


		TransformStatic->EulerRot = { 90, -90, 0 };
		Quat NewRot = Quat::FromEulerXYZ(TransformStatic->EulerRot.x, TransformStatic->EulerRot.y, TransformStatic->EulerRot.z);
		TransformStatic->SetEulerRotation(TransformStatic->EulerRot);

		//WORKING
	}
	else if (In_Pos4 == false) {
		TransformStatic->Translation= MoveDynamicSourceTo(PositionSq4, TransformStatic->Translation);

		//TransformStatic->EulerRot = { 0,0,0 };
		Quat NewRot = Quat::FromEulerXYZ(TransformStatic->EulerRot.x, TransformStatic->EulerRot.y, TransformStatic->EulerRot.z);
		TransformStatic->SetEulerRotation(TransformStatic->EulerRot);

	}

	TransformStatic->UpdateTransformationsObjects(TransformStatic->Translation, TransformStatic->Scale, TransformStatic->Rotation);

	Component_Mesh* MeshDynamic = (Component_Mesh*)Dynamic_Source->GetComponent(Component_Types::Mesh);

	MeshDynamic->UpdateOnTransformOBB();

}

float3 ModuleScene::MoveDynamicSourceTo(float3 GoTo, float3 TranslationVec)
{

	if (GoTo.x < TranslationVec.x) {

		TranslationVec.x = TranslationVec.x - 0.5;
	}
	else if (GoTo.x > TranslationVec.x) {
		TranslationVec.x = TranslationVec.x + 0.5;
	}

	if (GoTo.z < TranslationVec.z) {

		TranslationVec.z = TranslationVec.z - 0.5;
	}
	else if (GoTo.z > TranslationVec.z) {
		TranslationVec.z = TranslationVec.z + 0.5;
	}
	

	if (GoTo.x == TranslationVec.x && GoTo.z == TranslationVec.z) {

		if (In_Pos1 == false) {
			In_Pos1 = true;
			In_Pos2 = false;

		}
		else if (In_Pos2 == false) {
			In_Pos2 = true;
			In_Pos3 = false;
		}
		else if (In_Pos3 == false) {
			In_Pos3 = true;
			In_Pos4 = false;
		}
		else if (In_Pos4 == false) {
			In_Pos4 = true;
			In_Pos1 = false;
		}


	}

	return TranslationVec;

}


	

