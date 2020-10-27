#include "Globals.h"
#include "Application.h"
#include "ModuleInspector.h"

#include "libraries/ImGUI/imgui.h"
#include "libraries/ImGUI/imgui_internal.h"
#include "libraries/ImGUI/imgui_impl_sdl.h"
#include "libraries/ImGUI/imgui_impl_opengl3.h"

#include "libraries/Glew/include/GL/glew.h" 
#include "libraries/SDL/include/SDL_opengl.h"


ModuleInspectorGameObject::ModuleInspectorGameObject(Application* app, const char* name, bool start_enabled) : Module(app, name, start_enabled)
{



}

ModuleInspectorGameObject::~ModuleInspectorGameObject()
{}


bool ModuleInspectorGameObject::Start()
{



	return true;
}

update_status ModuleInspectorGameObject::Update(float dt)
{
	
	return UPDATE_CONTINUE;
}

bool ModuleInspectorGameObject::CleanUp()
{


	return true;
}

void ModuleInspectorGameObject::CreateInspectorWindow()
{
	if (App->mainMenubar->show_inspector_window)
	{
		ImGui::Begin("Inspector", &App->mainMenubar->show_inspector_window);


		//std::vector<GameObject*>::iterator IteratorLoaded = App->meshimporter->MeshesOnScene.begin();
		bool SomethingDrawn = false; // if there isnt an object in the list or if none of them
		//has ToBeDrawInspector==true we print a message saying theres nothing to draw
		GameObject* ItemToDraw;
		for (std::vector<GameObject*>::iterator IteratorLoaded = App->meshimporter->MeshesOnScene.begin(); IteratorLoaded != App->meshimporter->MeshesOnScene.end(); ++IteratorLoaded) {
			ItemToDraw = *IteratorLoaded;

			if (ItemToDraw->ToBeDrawInspector == true) {


				if (SomethingDrawn == true) {
					ImGui::Text("");
					ImGui::Text("");


					ImGui::Separator();
					ImGui::Separator();
					ImGui::Separator();
					ImGui::Separator();
				}

				const char* Name;
				Name = ItemToDraw->mesh_name.c_str();

				ImGui::Text(Name);

				ImGui::SetWindowFontScale(1.5);
				ImGui::Text("General Information");
				ImGui::SetWindowFontScale(1.0);



				int ChildAmount;

				ImGui::Text("Child Amount  %d", ChildAmount = ItemToDraw->ChildObjects.size());


				ImGui::Text("Currently Textured:");
				ImGui::SameLine(0.0f, 10.0f);

				if (ItemToDraw->is_Textured == true) {

					ImGui::Text("True");
				}
				else {
					ImGui::Text("False");
				}

				/*ImGui::Text("Currently Wireframed:");
				ImGui::SameLine(0.0f, 10.0f);*/


				ImGui::Checkbox("Wireframed", &ItemToDraw->is_Wireframed);

				ImGui::Checkbox("Draw", &ItemToDraw->is_Drawn);

				ImGui::Text("Item Id:");
				ImGui::SameLine(0.0f, 10.0f);
				ImGui::Text("%d", ItemToDraw->item_id);


				ImGui::Separator();

				ImGui::SetWindowFontScale(1.5);
				ImGui::Text("Transformation");
				ImGui::SetWindowFontScale(1.0);

				ImGui::Text("Position:");

				

				ImGui::InputFloat("X:", &ItemToDraw->Mesh_Transform_Modifiers.VectorTranslation.x);
				ImGui::SameLine(0.0f, 0.0f);
				ImGui::Text(":%.3f", ItemToDraw->Mesh_Transform_Modifiers.VectorTranslation.x);


				ImGui::InputFloat("Y", &ItemToDraw->Mesh_Transform_Modifiers.VectorTranslation.y);
				ImGui::SameLine(0.0f, 0.0f);
				ImGui::Text(":%.3f", ItemToDraw->Mesh_Transform_Modifiers.VectorTranslation.y);

				ImGui::InputFloat("Z", &ItemToDraw->Mesh_Transform_Modifiers.VectorTranslation.z);
				ImGui::SameLine(0.0f, 0.0f);
				ImGui::Text(":%.3f", ItemToDraw->Mesh_Transform_Modifiers.VectorTranslation.z);



				ImGui::Text("Rotation:");

				//IMGUI INPUT NO FUNCIONA SI EL NOM DE LA ULTIMA VARIALBE ES IGUAL no te ni puta idea de programar

				ImGui::InputFloat("Angle:", &ItemToDraw->Mesh_Transform_Modifiers.VectorRotation.angle);
				ImGui::SameLine(0.0f, 0.0f);
				ImGui::Text(":%.3f", ItemToDraw->Mesh_Transform_Modifiers.VectorRotation.angle);

				ImGui::InputFloat("X:", &ItemToDraw->Mesh_Transform_Modifiers.VectorRotation.x);
				ImGui::SameLine(0.0f, 0.0f);
				ImGui::Text(":%.3f", ItemToDraw->Mesh_Transform_Modifiers.VectorRotation.x);


				ImGui::InputFloat("Y", &ItemToDraw->Mesh_Transform_Modifiers.VectorRotation.y);
				ImGui::SameLine(0.0f, 0.0f);
				ImGui::Text(":%.3f", ItemToDraw->Mesh_Transform_Modifiers.VectorRotation.y);

				ImGui::InputFloat("Z", &ItemToDraw->Mesh_Transform_Modifiers.VectorRotation.z);
				ImGui::SameLine(0.0f, 0.0f);
				ImGui::Text(":%.3f", ItemToDraw->Mesh_Transform_Modifiers.VectorRotation.z);


				ImGui::Text("Scale:");


				ImGui::InputFloat("X:", &ItemToDraw->Mesh_Transform_Modifiers.VectorScale.x);
				ImGui::SameLine(0.0f, 0.0f);
				ImGui::Text(":%.3f", ItemToDraw->Mesh_Transform_Modifiers.VectorScale.x);


				ImGui::InputFloat("Y", &ItemToDraw->Mesh_Transform_Modifiers.VectorScale.y);
				ImGui::SameLine(0.0f, 0.0f);
				ImGui::Text(":%.3f", ItemToDraw->Mesh_Transform_Modifiers.VectorScale.y);

				ImGui::InputFloat("Z", &ItemToDraw->Mesh_Transform_Modifiers.VectorScale.z);
				ImGui::SameLine(0.0f, 0.0f);
				ImGui::Text(":%.3f", ItemToDraw->Mesh_Transform_Modifiers.VectorScale.z);




				ImGui::Separator();
				ImGui::SetWindowFontScale(1.5);
				ImGui::Text("Mesh Information");
				ImGui::SetWindowFontScale(1.0);

				ImGui::Text("Index Amount:");
				ImGui::SameLine(0.0f, 10.0f);
				ImGui::Text("%d", ItemToDraw->MeshData.num_index);

				ImGui::Text("Vertex Amount:");
				ImGui::SameLine(0.0f, 10.0f);
				ImGui::Text("%d", ItemToDraw->MeshData.num_vertex);

				ImGui::Text("Id Index:");
				ImGui::SameLine(0.0f, 10.0f);
				ImGui::Text("%d", ItemToDraw->MeshData.id_index);

				ImGui::Text("Id Vertex:");
				ImGui::SameLine(0.0f, 10.0f);
				ImGui::Text("%d", ItemToDraw->MeshData.id_vertex);

				ImGui::Separator();

				ImGui::SetWindowFontScale(1.5);
				ImGui::Text("Textures");
				ImGui::SetWindowFontScale(1.0);


				ImGui::Checkbox("Checkered", &ItemToDraw->is_Checkered);




				if (ItemToDraw->is_Checkered == true) {
					ItemToDraw->is_Textured = false;
				}

				ImGui::Checkbox("Textured", &ItemToDraw->is_Textured);

				if (ItemToDraw->is_Textured == true) {
					ItemToDraw->is_Checkered = false;
				}

				SomethingDrawn = true;

				//++IteratorLoaded;

			}

		}

		if (SomethingDrawn == false) {



			ImGui::SetWindowFontScale(1.5);
			ImGui::Text("No object Selected");
			ImGui::SetWindowFontScale(1.0);
		}

		ImGui::End();
	}
	
}

void ModuleInspectorGameObject::ShowSelectedObjectInfo(GameObject* object)
{

	// THIS ONLY COPIES INFORMATION IT DOESNT MODIFY THE OBJECT ITSELF SO LATER ON WE WILL HAVE TO CHANGE THIS TO BE ABLE TO MODIFY ITEMS FROM THE INSPECTOR
	ObjectToBeShownInspector = object;

}

void ModuleInspectorGameObject::CreateConsolelog(const char file[], int line, const char* format, ...)
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


	App->console->ConsoleLogs.push_back(tmp_string2);
}