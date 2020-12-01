#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleInput.h"
#include "ModuleGeometryManager.h"
#include "ModuleMeshImporter.h"
#include "ModuleEditor.h"
#include "Game_Time.h"

#include "libraries/MathGeoLib/include/Math/MathFunc.h"
#include "libraries/MathGeoLib/include/Geometry/LineSegment.h"

ModuleCamera3D::ModuleCamera3D(Application* app, const char* name, bool start_enabled) : Module(app,name, start_enabled)
{
	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOGFIX("Setting up the camera");
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOGFIX("Cleaning camera");

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
		float speed = 20.0f * dt;
		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
			speed = 40.0f * dt;

		if (App->input->GetKey(SDL_SCANCODE_KP_7) == KEY_REPEAT) newPos.y += speed;
		if (App->input->GetKey(SDL_SCANCODE_KP_9) == KEY_REPEAT) newPos.y -= speed;

		//if ((App->input->GetKey(SDL_SCANCODE_KP_8) == KEY_REPEAT) && (App->input->GetKey(SDL_BUTTON_LEFT) == SDL_MOUSEBUTTONDOWN))newPos -= Z * speed;

		if (App->input->GetKey(SDL_SCANCODE_KP_8) == KEY_REPEAT) newPos -= Z * speed;
		else if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)&& (App->input->GetMouseButton(SDL_BUTTON_RIGHT))) newPos -= Z * speed;
		if (App->input->GetKey(SDL_SCANCODE_KP_5) == KEY_REPEAT) newPos += Z * speed;
		else if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && (App->input->GetMouseButton(SDL_BUTTON_RIGHT))) newPos += Z * speed;

		if (App->input->GetKey(SDL_SCANCODE_KP_4) == KEY_REPEAT) newPos -= X * speed;
		else if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && (App->input->GetMouseButton(SDL_BUTTON_RIGHT))) newPos -= X * speed;
		if (App->input->GetKey(SDL_SCANCODE_KP_6) == KEY_REPEAT) newPos += X * speed;
		else if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (App->input->GetMouseButton(SDL_BUTTON_RIGHT))) newPos += X * speed;

		Position += newPos;
		Reference += newPos;

		// Wheel Zoom
		if (App->input->GetMouseZ() != 0)
		{
			vec3 Distance = Position - Reference;
			vec3 newPos = { 0,0,0 };

			if (App->input->GetMouseZ() > 0 || App->input->GetMouseZ() < 0)
			{
				newPos -= Z * App->input->GetMouseZ() * length(Distance) / (1 / zoomValue * 4);
				Position += newPos;
			}

			Position += newPos;
		}

		//Left Click (altenative for the arrows)
		if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT)
		{
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);

			int dx = -App->input->GetMouseXMotion();
			int dy = -App->input->GetMouseYMotion();

			if (dx != 0 || dy != 0)
			{
				newPos -= Y * dy * App->GetDT() * wheelSpeedValue;
				newPos += X * dx * App->GetDT() * wheelSpeedValue;
			}

			Position += newPos;
			Reference += newPos;
		}

		// Mouse motion ----------------
		if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
		{
			int dx = -App->input->GetMouseXMotion();
			int dy = -App->input->GetMouseYMotion();

			float Sensitivity = 0.25f;

			Position -= Reference;

			if (dx != 0)
			{
				float DeltaX = (float)dx * Sensitivity;

				X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			}

			if (dy != 0)
			{
				float DeltaY = (float)dy * Sensitivity;

				Y = rotate(Y, DeltaY, X);
				Z = rotate(Z, DeltaY, X);

				if (Y.y < 0.0f)
				{
					Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
					Y = cross(Z, X);
				}
			}

			Position = Reference + Z * length(Position);
		}

		//Center to object
		

		std::vector<GameObject*>::iterator IteratorToAddMesh = App->meshimporter->MeshesOnScene.begin();
		GameObject* selected_mesh;
		for (int count = 0; count < App->meshimporter->MeshesOnScene.size(); ++count)
		{
			selected_mesh = *IteratorToAddMesh;
			if (selected_mesh->Modifier.ToBeDrawInspector == true)
			{
				if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
				{
					CenterToObject(selected_mesh);
					LOGFIX("Centering Object");
				}

				if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
				{
					if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT)
					{
						//Orbit()
						ResetRotation = true;
						LookAt({ selected_mesh->Mesh_Transform_Modifiers.VectorTranslation.x,
							selected_mesh->Mesh_Transform_Modifiers.VectorTranslation.y,
							selected_mesh->Mesh_Transform_Modifiers.VectorTranslation.z 
						});

					}
				}
			}
			else if (ResetRotation == true)
			{
				ResetRotation = false;
				LookAt({ 0,0,0 });
			}

			std::vector<GameObject*>::iterator IteratorToAddMesh2 = selected_mesh->ChildObjects.begin();

			GameObject* selected_mesh_child;

			for (int count2 = 0; count2 < selected_mesh->ChildObjects.size(); ++count2)
			{
				selected_mesh_child = *IteratorToAddMesh2;
				if (selected_mesh_child->Modifier.ToBeDrawInspector == true)
				{
					if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
					{
						CenterToObject(selected_mesh_child);
						LOGFIX("Centering Object");
					}

					

					if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
					{
						if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT)
						{
							CenterToObject(selected_mesh_child);

						}
					}
				}
				++IteratorToAddMesh2;
			}

			++IteratorToAddMesh;
		}
		// Recalculate matrix -------------
		CalculateViewMatrix();
	}

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3& Position, const vec3& Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if (!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt(const vec3& Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec3& Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return &ViewMatrix;
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}

void ModuleCamera3D::CenterToObject( GameObject* object)
{
	LookAt({ object->Mesh_Transform_Modifiers.VectorTranslation.x,object->Mesh_Transform_Modifiers.VectorTranslation.y,object->Mesh_Transform_Modifiers.VectorTranslation.z });
}

void ModuleCamera3D::Orbit() {

}

void ModuleCamera3D::CreateConsolelog(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
	OutputDebugString(tmp_string2);


	App->editor->ConsoleLogs.push_back(tmp_string2);
}
