#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleInput.h"
#include "ModuleGeometryManager.h"
#include "ModuleMeshImporter.h"
#include "ModuleEditor.h"
#include "ModuleScene.h"
#include "Game_Time.h"
#include "ModuleWindow.h"
#include "GameObject.h"
#include "ComponentTransform.h"
#include "ComponentCamera.h"
#include "ResourceManager.h"
#include "ModuleHierarchy.h"

#include "libraries/MathGeoLib/include/Math/MathFunc.h"
#include "libraries/MathGeoLib/include/Geometry/LineSegment.h"

ModuleCamera3D::ModuleCamera3D(Application* app, const char* name, bool start_enabled) : Module(app,name, start_enabled)
{
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;

	scene_camera = new Component_Camera(App->scene->object_scene_camera);
	App->geometrymanager->ObjectsOnScene.begin();

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	if (io.WantCaptureMouse == false || Game_Time::running == true)
	{

		// Movement Camera
		vec3 newPos(0, 0, 0);
		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
			scene_camera->camera_speed = 80.0f * dt;

		if (App->input->GetKey(SDL_SCANCODE_KP_7) == KEY_REPEAT) newPos.y += scene_camera->camera_speed;
		if (App->input->GetKey(SDL_SCANCODE_KP_9) == KEY_REPEAT) newPos.y -= scene_camera->camera_speed;

		//if ((App->input->GetKey(SDL_SCANCODE_KP_8) == KEY_REPEAT) && (App->input->GetKey(SDL_BUTTON_LEFT) == SDL_MOUSEBUTTONDOWN))newPos -= Z * speed;

		if (App->input->GetKey(SDL_SCANCODE_KP_8) == KEY_REPEAT) newPos -= scene_camera->Z * scene_camera->camera_speed;
		else if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) && (App->input->GetMouseButton(SDL_BUTTON_RIGHT))) newPos -= scene_camera->Z * scene_camera->camera_speed;
		if (App->input->GetKey(SDL_SCANCODE_KP_5) == KEY_REPEAT) newPos += scene_camera->Z * scene_camera->camera_speed;
		else if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && (App->input->GetMouseButton(SDL_BUTTON_RIGHT))) newPos += scene_camera->Z * scene_camera->camera_speed;

		if (App->input->GetKey(SDL_SCANCODE_KP_4) == KEY_REPEAT) newPos -= scene_camera->X * scene_camera->camera_speed;
		else if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && (App->input->GetMouseButton(SDL_BUTTON_RIGHT))) newPos -= scene_camera->X * scene_camera->camera_speed;
		if (App->input->GetKey(SDL_SCANCODE_KP_6) == KEY_REPEAT) newPos += scene_camera->X * scene_camera->camera_speed;
		else if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (App->input->GetMouseButton(SDL_BUTTON_RIGHT))) newPos += scene_camera->X * scene_camera->camera_speed;

		scene_camera->Position += newPos;
		scene_camera->Reference += newPos;

		mouse_picking = true;
		

		// Wheel Zoom
		if (ImGui::IsAnyItemFocused() == false && ImGui::IsAnyWindowFocused()==false) {
			if (App->input->GetMouseZ() != 0)
			{
				vec3 Distance = scene_camera->Position - scene_camera->Reference;
				vec3 newPos = { 0,0,0 };

				if (App->input->GetMouseZ() > 0 || App->input->GetMouseZ() < 0)
				{
					newPos -= scene_camera->Z * App->input->GetMouseZ() * length(Distance) / (1 / scene_camera->zoomValue * 4);
					scene_camera->Position += newPos;
				}

				scene_camera->Position += newPos;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN || reset_camera == true)
		{
			LookAt({ 0,0,0 });
			scene_camera->Position.x = 0.875;
			scene_camera->Position.y = 0.875;
			scene_camera->Position.z = 4,375;

			reset_camera = false;

		}


		//Left Click (altenative for the arrows)
		if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT)
		{
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);

			int dx = -App->input->GetMouseXMotion();
			int dy = -App->input->GetMouseYMotion();

			if (dx != 0 || dy != 0)
			{
				newPos -= scene_camera->Y * dy * App->GetDT() * scene_camera->wheelSpeedValue;
				newPos += scene_camera->X * dx * App->GetDT() * scene_camera->wheelSpeedValue;
			}

			scene_camera->Position += newPos;
			scene_camera->Reference += newPos;
		}

		// Mouse motion ----------------
		if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
		{
			int dx = -App->input->GetMouseXMotion();
			int dy = -App->input->GetMouseYMotion();

			float Sensitivity = 0.25f;

			scene_camera->Position -= scene_camera->Reference;

			if (dx != 0)
			{
				float DeltaX = (float)dx * Sensitivity;

				scene_camera->X = rotate(scene_camera->X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				scene_camera->Y = rotate(scene_camera->Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				scene_camera->Z = rotate(scene_camera->Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			}

			if (dy != 0)
			{
				float DeltaY = (float)dy * Sensitivity;

				scene_camera->Y = rotate(scene_camera->Y, DeltaY, scene_camera->X);
				scene_camera->Z = rotate(scene_camera->Z, DeltaY, scene_camera->X);

				if (scene_camera->Y.y < 0.0f)
				{
					scene_camera->Z = vec3(0.0f, scene_camera->Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
					scene_camera->Y = cross(scene_camera->Z, scene_camera->X);
				}
			}

			scene_camera->Position = scene_camera->Reference + scene_camera->Z * length(scene_camera->Position);
		}

		//Center to object
		std::vector<Game_Object*>::iterator IteratorObject = App->geometrymanager->ObjectsOnScene.begin();
		Game_Object* selected_object;
		for (int count = 0; count < App->geometrymanager->ObjectsOnScene.size(); ++count) {
			selected_object = *IteratorObject;

			if (selected_object->is_Selected == true) {

				if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
				{
					CenterToObject(selected_object);
					LOG("Centering Object");
				}

				if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
				{
					if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT)
					{
						//Orbit()
						scene_camera->ResetRotation = true;
						LookAt({ selected_object->Transformations->Translation.x,
							 selected_object->Transformations->Translation.y,
							 selected_object->Transformations->Translation.z
						});

					}
				}

			}

			else if (scene_camera->ResetRotation == true)
			{
				scene_camera->ResetRotation = false;
				LookAt({ 0,0,0 });
			}

			std::vector<Game_Object*>::iterator IteratorObjectChild = selected_object->Children_List.begin();

			Game_Object* selected_object_child;

			for (int countchild = 0; countchild < selected_object->Children_List.size(); ++countchild) {

				selected_object_child = *IteratorObjectChild;

				if (selected_object_child->is_Selected == true) {

					if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
					{
						CenterToObject(selected_object_child);
						LOG("Centering Object");
					}

					if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
					{
						if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT)
						{
							//Orbit()
							scene_camera->ResetRotation = true;
							LookAt({ selected_object_child->Transformations->Translation.x,
								 selected_object_child->Transformations->Translation.y,
								 selected_object_child->Transformations->Translation.z
							});

						}
					}

				}

			}


		}

		// Recalculate matrix -------------
		scene_camera->CalculateViewMatrix();
	}

	if ((App->input->GetKey(SDL_SCANCODE_DELETE) == KEY_DOWN) || App->hierarchy->ITEM_TO_BE_DELETED == true) {
		if (App->scene->ObjectToBeDeleted != nullptr) {
			Component_Source* SRCCmp = (Component_Source*)App->scene->ObjectToBeDeleted->GetComponent(Component_Types::Source);
			std::vector<Game_Object*>::iterator IterSrc = App->scene->ObjectToBeDeleted->Children_List.begin();

			for (int i = 0; i < App->scene->ObjectToBeDeleted->Children_List.size(); ++i) {

				Game_Object* Obj = *IterSrc;

				Component_Source* SRCCmpo = (Component_Source*)Obj->GetComponent(Component_Types::Source);

				if (SRCCmpo != nullptr) {

					App->scene->ObjectToBeDeleted = nullptr;
					break;
				}

				++IterSrc;

			}

			if (SRCCmp == nullptr) {


				std::vector<Game_Object*>::iterator It = App->geometrymanager->ObjectsOnScene.begin();
				for (int i = 0; i < App->geometrymanager->ObjectsOnScene.size(); ++i) {

					Game_Object* Obj = *It;

					App->scene->RemoveSelectedItem(Obj);

					++It;
				}
			}
			else {
				App->scene->ObjectToBeDeleted = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3& Position, const vec3& Reference, bool RotateAroundReference)
{
	scene_camera->Position = Position;
	scene_camera->Reference = Reference;

	scene_camera->Z = normalize(Position - Reference);
	scene_camera->X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), scene_camera->Z));
	scene_camera->Y = cross(scene_camera->Z, scene_camera->X);

	if (!RotateAroundReference)
	{
		scene_camera->Reference = scene_camera->Position;
		scene_camera->Position += scene_camera->Z * 0.05f;
	}

	scene_camera->CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt(const vec3& Spot)
{
	scene_camera->Reference = Spot;

	scene_camera->Z = normalize(scene_camera->Position - scene_camera->Reference);
	scene_camera->X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), scene_camera->Z));
	scene_camera->Y = cross(scene_camera->Z, scene_camera->X);

	scene_camera->CalculateViewMatrix();
}

void ModuleCamera3D::Zoom(float dt)
{
	scene_camera->Position -= scene_camera->Z * (float)App->input->GetMouseZ() * scene_camera->zoomValue * dt;
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec3& Movement)
{
	scene_camera->Position += Movement;
	scene_camera->Reference += Movement;

	scene_camera->CalculateViewMatrix();
}

void ModuleCamera3D::CenterToObject( Game_Object* object)
{
	LookAt({ object->Transformations->Translation.x, object->Transformations->Translation.y, object->Transformations->Translation.z });
}

void ModuleCamera3D::Orbit() {

}

update_status ModuleCamera3D::Load()
{
	scene_camera->Load();

	return UPDATE_CONTINUE;
}

Component_Camera* ModuleCamera3D::GetSceneCamera() const
{
	return scene_camera;
}


