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
	if (App->mainMenubar->show_inspector_window) {
		ImGui::Begin("Inspector", &App->mainMenubar->show_inspector_window);
		
		
		if (ObjectToBeShownInspector == NULL) {

			
			ImGui::SetWindowFontScale(1.5);
			ImGui::Text("No object Selected");
			ImGui::SetWindowFontScale(1.0);
			
			
		}
		else {

			ImGui::SetWindowFontScale(1.5);
			ImGui::Text("General Information");
			ImGui::SetWindowFontScale(1.0);

			const char* Name;
			Name = ObjectToBeShownInspector->mesh_name.c_str();

			ImGui::Text(Name = ObjectToBeShownInspector->mesh_name.c_str());

			int ChildAmount;
			
			ImGui::Text("Child Amount  %d", ChildAmount = ObjectToBeShownInspector->ChildObjects.size());


			ImGui::Text("Currently Textured:");
			ImGui::SameLine(0.0f, 10.0f);

			if (ObjectToBeShownInspector->is_Textured == true) {

				ImGui::Text("True");
			}
			else {
				ImGui::Text("False");
			}

			ImGui::Text("Currently Wireframed:");
			ImGui::SameLine(0.0f, 10.0f);
			if (ObjectToBeShownInspector->is_Wireframed == true) {

				ImGui::Text("True");
			}
			else {
				ImGui::Text("False");
			}

			ImGui::Text("Item Id:");
			ImGui::SameLine(0.0f, 10.0f);
			ImGui::Text("%d", ObjectToBeShownInspector->item_id);


			ImGui::Separator();

			ImGui::SetWindowFontScale(1.5);
			ImGui::Text("Transformation");
			ImGui::SetWindowFontScale(1.0);

			ImGui::Separator();

			ImGui::SetWindowFontScale(1.5);
			ImGui::Text("Mesh Information");
			ImGui::SetWindowFontScale(1.0);

			ImGui::Text("Index Amount:");
			ImGui::SameLine(0.0f, 10.0f);
			ImGui::Text("%d", ObjectToBeShownInspector->MeshData.num_index);

			ImGui::Text("Vertex Amount:");
			ImGui::SameLine(0.0f, 10.0f);
			ImGui::Text("%d", ObjectToBeShownInspector->MeshData.num_vertex);

			ImGui::Text("Id Index:");
			ImGui::SameLine(0.0f, 10.0f);
			ImGui::Text("%d", ObjectToBeShownInspector->MeshData.id_index);

			ImGui::Text("Id Vertex:");
			ImGui::SameLine(0.0f, 10.0f);
			ImGui::Text("%d", ObjectToBeShownInspector->MeshData.id_vertex);

			

			ImGui::Separator();

			ImGui::SetWindowFontScale(1.5);
			ImGui::Text("Textures");
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