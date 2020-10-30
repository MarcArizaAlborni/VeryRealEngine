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
				SomethingDrawn = true;
				DrawInspectorWindowInfo(ItemToDraw);
			}
			else if (ItemToDraw->ChildObjects.size() > 0) {

				GameObject* ChildFoundDraw = new GameObject();
				std::vector<GameObject*>::iterator ChildIteratorLoaded = ItemToDraw->ChildObjects.begin();
				for (int itB=0; itB < ItemToDraw->ChildObjects.size(); ++itB) {

					ChildFoundDraw = *ChildIteratorLoaded;

					if (ChildFoundDraw->ToBeDrawInspector == true) {

						SomethingDrawn = true;


						DrawInspectorWindowInfo(ChildFoundDraw);

						itB = ItemToDraw->ChildObjects.size();


					}
					else{ 
						++ChildIteratorLoaded; 
					}

					
				}
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

void ModuleInspectorGameObject::DrawInspectorWindowInfo(GameObject* item)
{

		const char* Name;
		Name = item->mesh_name.c_str();

		ImGui::Text(Name);
		//GENERAL INFORMATION
		ImGui::SetWindowFontScale(1.5);
		ImGui::Text("General Information");
		ImGui::SetWindowFontScale(1.0);

		int ChildAmount;

		ImGui::Text("Child Amount  %d", ChildAmount = item->ChildObjects.size());

		ImGui::Text("Currently Textured:");
		ImGui::SameLine(0.0f, 10.0f);

		if (item->is_Textured == true) {

			ImGui::Text("True");
		}
		else {
			ImGui::Text("False");
		}

		ImGui::Checkbox("Wireframed", &item->is_Wireframed);

		if (ImGui::Checkbox("Draw", &item->is_Drawn)) {
			int abcdefg = 0;
		}

		ImGui::Text("Item Id:");
		ImGui::SameLine(0.0f, 10.0f);
		ImGui::Text("%d", item->item_id);

		ImGui::Separator();


		///TRANSFORMATIONS
		ImGui::SetWindowFontScale(1.5);
		ImGui::Text("Transformation");
		ImGui::SetWindowFontScale(1.0);

		ImGui::Text("Position:");

		ImGui::InputFloat("X pos:", &item->Mesh_Transform_Modifiers.VectorTranslation.x);
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(":%.3f", item->Mesh_Transform_Modifiers.VectorTranslation.x);

		ImGui::InputFloat("Y pos", &item->Mesh_Transform_Modifiers.VectorTranslation.y);
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(":%.3f", item->Mesh_Transform_Modifiers.VectorTranslation.y);

		ImGui::InputFloat("Z pos", &item->Mesh_Transform_Modifiers.VectorTranslation.z);
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(":%.3f", item->Mesh_Transform_Modifiers.VectorTranslation.z);

		ImGui::Text("Rotation:");

		ImGui::InputFloat("Angle:", &item->Mesh_Transform_Modifiers.VectorRotation.angle);
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(":%.3f", item->Mesh_Transform_Modifiers.VectorRotation.angle);

		ImGui::InputFloat("X rot:", &item->Mesh_Transform_Modifiers.VectorRotation.x);
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(":%.3f", item->Mesh_Transform_Modifiers.VectorRotation.x);

		ImGui::InputFloat("Y rot", &item->Mesh_Transform_Modifiers.VectorRotation.y);
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(":%.3f", item->Mesh_Transform_Modifiers.VectorRotation.y);

		ImGui::InputFloat("Z rot", &item->Mesh_Transform_Modifiers.VectorRotation.z);
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(":%.3f", item->Mesh_Transform_Modifiers.VectorRotation.z);

		ImGui::Text("Scale:");

		ImGui::InputFloat("X scale:", &item->Mesh_Transform_Modifiers.VectorScale.x);
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(":%.3f", item->Mesh_Transform_Modifiers.VectorScale.x);

		ImGui::InputFloat("Y scale", &item->Mesh_Transform_Modifiers.VectorScale.y);
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(":%.3f", item->Mesh_Transform_Modifiers.VectorScale.y);

		ImGui::InputFloat("Z scale", &item->Mesh_Transform_Modifiers.VectorScale.z);
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(":%.3f", item->Mesh_Transform_Modifiers.VectorScale.z);

		ImGui::Separator();

		//MESH INFO
		ImGui::SetWindowFontScale(1.5);
		ImGui::Text("Mesh Information");
		ImGui::SetWindowFontScale(1.0);

		ImGui::Text("Index Amount:");
		ImGui::SameLine(0.0f, 10.0f);
		ImGui::Text("%d", item->MeshData.num_index);

		ImGui::Text("Vertex Amount:");
		ImGui::SameLine(0.0f, 10.0f);
		ImGui::Text("%d", item->MeshData.num_vertex);

		ImGui::Text("Id Index:");
		ImGui::SameLine(0.0f, 10.0f);
		ImGui::Text("%d", item->MeshData.id_index);

		ImGui::Text("Id Vertex:");
		ImGui::SameLine(0.0f, 10.0f);
		ImGui::Text("%d", item->MeshData.id_vertex);

		ImGui::Separator();

		ImGui::Checkbox("Show Face Normals", &item->showFaceNormals);

		//TEXTURES INFO
		ImGui::SetWindowFontScale(1.5);
		ImGui::Text("Textures");
		ImGui::SetWindowFontScale(1.0);

		ImGui::Checkbox("Checkered", &item->is_Checkered);

		if (item->is_Checkered == true) {
			item->is_Textured = false;
		}

		ImGui::Checkbox("Textured", &item->is_Textured);

		if (item->is_Textured == true) {
			item->is_Checkered = false;
		}

		ImGui::Text("Texture Name: ");
		ImGui::SameLine(0.0f, 10.0f);
		const char* nameTexture = item->TextureData.texture_name.c_str();
		ImGui::Text("%s", nameTexture);

		if (item->is_Textured) {
			ImGui::Text("Texture Path:");
			ImGui::SameLine(0.0f, 10.0f);
			const char* pathnameTexture = item->TextureData.texture_path.c_str();
			ImGui::Text("%s", pathnameTexture);
		}
		else if (item->is_Checkered) {
			ImGui::Text("Texture Path:");
			ImGui::SameLine(0.0f, 10.0f);

			ImGui::Text("Checkered Texture");
		}
		else {
			ImGui::Text("Texture Path:");
			ImGui::SameLine(0.0f, 10.0f);

			ImGui::Text("No texture Selected");
		}

		ImGui::Text("%d", item->TextureData.width);
		ImGui::SameLine(0.0f, 10.0f);
		ImGui::Text("Texture Width");

		ImGui::Text("%d", item->TextureData.height);
		ImGui::SameLine(0.0f, 10.0f);
		ImGui::Text("Texture Height");

		ImGui::Text("Texture id");
		ImGui::SameLine(0.0f, 10.0f);
		ImGui::Text("%d", item->TextureData.texture_id);

		ImGui::Image((void*)(intptr_t)item->TextureData.texture_id, { 200,200 });

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