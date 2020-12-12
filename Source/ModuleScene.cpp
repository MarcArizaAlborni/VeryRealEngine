#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "Definitions.h"
#include "ModuleRenderer3D.h"
#include "FileSystem.h"
#include "ModuleCamera3D.h"
#include "ComponentCamera.h"
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

	GuizmoDrawn();




	

	

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

			// View parametres
			float4x4 view_matrix = App->camera->scene_camera->frustum.ViewMatrix();
			view_matrix.Transpose();
			float4x4 proj_matrix = App->camera->scene_camera->frustum.ProjectionMatrix().Transposed();

			// Draw guizmos axis
			ImGuiIO& io = ImGui::GetIO();
			ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

			// Change guizmos operations
			ChangeOperationGuizmo(g_operator);

			float4x4 matrix;
			matrix = selected_transform->Global_Matrix.Transposed();

			ImGuizmo::MODE actualMode = (g_operator == ImGuizmo::OPERATION::SCALE ? ImGuizmo::MODE::LOCAL : mode);

			ImGuizmo::Manipulate(view_matrix.ptr(), proj_matrix.ptr(), g_operator, actualMode, (float*)matrix.v);

			if (ImGuizmo::IsUsing() == true)
			{
				selected_transform->Global_Matrix = matrix.Transposed();
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


