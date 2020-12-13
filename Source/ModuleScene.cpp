#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "Definitions.h"
#include "ModuleRenderer3D.h"
#include "FileSystem.h"
#include "ModuleCamera3D.h"
#include "Component.h"
#include "ComponentCamera.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"
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
#include "libraries/imGuizmo/ImGuizmo.h"

#include "libraries/MathGeoLib/include/Geometry/LineSegment.h"



#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleScene::ModuleScene(Application* app, const char* name, bool start_enabled) : Module(app, "Scene", start_enabled)
{
	ROOT_SCENE_OBJECT = new Game_Object("MainScene");
	App->geometrymanager->ObjectsOnScene.push_back(ROOT_SCENE_OBJECT);
	ROOT_SCENE_OBJECT->Parent = nullptr;

	object_scene_camera = new Game_Object("Scene Camera");
	ROOT_SCENE_OBJECT->Children_List.push_back(object_scene_camera);
	object_scene_camera->Parent = ROOT_SCENE_OBJECT;

	ImGuizmo::Enable(true);

}

// Destructor
ModuleScene::~ModuleScene()
{}

// Called before render is available
bool ModuleScene::Init()
{
	LOG("Creating Scene context");
	bool ret = true;

	return ret;
}

bool ModuleScene::Start()
{
	object_scene_camera->AddExistingComponent(App->camera->scene_camera);

	App->textureImporter->TextureCheckers = App->textureImporter->LoadTextureImage("Assets/Models/Checkers/checkers.png");

	// BAKER HOUSE FOR DRAW W/TEXTURES ON START

	//App->textureImporter->TextureHouse = App->textureImporter->LoadTextureImage("Assets/Models/House/Baker_house.png");

	


	//This
	//App->meshimporter->LoadFile_Mesh("Assets/Models/House/BakerHouse.fbx");
	//this
	
	App->meshimporter->LoadFile_Mesh("Assets/Models/Street/Street_environment_V01.FBX");
	//App->meshimporter->LoadFile_Mesh("Assets/Models/Street/Street_environment_V01.FBX");
	


	//App->meshimporter->LoadFile_Mesh("Assets/Models/Street/Street_environment_V01.FBX");
	//App->meshimporter->LoadFile_Mesh("Assets/Models/Street/Street_environment.FBX");

	
	


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

	return UPDATE_CONTINUE;
}


// PostUpdate present buffer to screen
update_status ModuleScene::PostUpdate(float dt)
{
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

Game_Object* ModuleScene::MousePicking(const LineSegment& segment, float& distance, bool closest) 
{
	distance = 99999999999.f;

	Game_Object* pick_GO = nullptr;

	for (auto it : App->geometrymanager->ObjectsOnScene[0]->Children_List[1]->Children_List[1]->Children_List)
	{
		Component_Mesh* MeshBB = (Component_Mesh*)it->GetComponent(Component_Types::Mesh);

		if (MeshBB->global_AABB.IsFinite())
		{
			if (segment.Intersects(MeshBB->local_AABB))
			{
				Component_Transform* transf = (Component_Transform*)it->GetComponent(Component_Types::Transform);
				Component_Mesh* mesh = (Component_Mesh*)it->GetComponent(Component_Types::Mesh);

				if (mesh != nullptr)
				{
					if (mesh->Mesh->vertex!= nullptr && mesh->Mesh->index != nullptr)
					{
						LineSegment ray(segment);
						ray.Transform(transf->GetGlobalTransform().Inverted());

						Triangle triangle;

						for (uint i = 0; i < mesh->Mesh->num_index;)
						{
							triangle.a = mesh->Mesh->vertex[mesh->Mesh->index[i]]; ++i;
							triangle.b = mesh->Mesh->vertex[mesh->Mesh->index[i]]; ++i;
							triangle.c = mesh->Mesh->vertex[mesh->Mesh->index[i]]; ++i;

							float length; 
							float3 hitPos;

							if (ray.Intersects(triangle, &length, &hitPos))
							{
								if (closest && length < distance)
								{
									distance = length;
									pick_GO = (Game_Object*)it;
								}
							}
						}
					}
				}
			}
		}
	}

	return pick_GO;
}
