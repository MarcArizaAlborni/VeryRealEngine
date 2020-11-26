#include "Globals.h"
#include "Application.h"
#include "ModuleInspector.h"
#include "ModuleGeometryManager.h"
#include "ModuleMeshImporter.h"
#include "ModuleEditor.h"

#include "libraries/ImGUI/imgui.h"
#include "libraries/ImGUI/imgui_internal.h"
#include "libraries/ImGUI/imgui_impl_sdl.h"
#include "libraries/ImGUI/imgui_impl_opengl3.h"

#include "libraries/Glew/include/GL/glew.h" 
#include "libraries/SDL/include/SDL_opengl.h"

#include "libraries/mmgr/mmgr.h"




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
	if (App->editor->show_inspector_window)
	{
		ImGui::Begin("Inspector", &App->editor->show_inspector_window);

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

				GameObject* ChildFoundDraw;
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
			ImGui::Text("No Objects Selected");
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
		if (ImGui::CollapsingHeader("General Information"))
		{
			int ChildAmount;

			ImGui::InputText(" ", (char*)item->mesh_name.c_str(), 100, ImGuiInputTextFlags_EnterReturnsTrue);

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

			ImGui::Checkbox("Draw", &item->is_Drawn);

			ImGui::Text("Item Id:");
			ImGui::SameLine(0.0f, 10.0f);
			ImGui::Text("%d", item->item_id);

			ImGui::Separator();
		}
		
		///TRANSFORMATIONS
		if (ImGui::CollapsingHeader("Transformation")) {

			if (ImGui::DragFloat3("Position", { &item->Mesh_Transform_Modifiers.VectorTranslation.x}, 0.2f, 0.0, 0.0, "%.2f")) {}
			if (ImGui::DragFloat("Angle", { &item->Mesh_Transform_Modifiers.VectorRotation.angle }, 0.2f, -359.0, 359.0, "%.2f")) {}
			if (ImGui::DragFloat3("Rotation", { &item->Mesh_Transform_Modifiers.VectorRotation.x }, 0.02f, 0.0, 1.0, "%.3f")) {}
			if (ImGui::DragFloat3("Scale", { &item->Mesh_Transform_Modifiers.VectorScale.x }, 0.2f, 0.0, 0.0, "%.2f")) {}

			ImGui::Checkbox("Move Family", &item->is_FamilyMove);

			ImGui::Separator();
		}

		//MESH INFO
		if (ImGui::CollapsingHeader("Mesh")) {

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
			ImGui::Text("Mesh Path:");
			ImGui::SameLine();
			ImGui::TextColored({ 255,255,0,1 }, "%s", &item->path);

			if (ImGui::TreeNodeEx("Vertex Normals:", ImGuiTreeNodeFlags_DefaultOpen)) {

				ImGui::Checkbox("Show Vertex Normals", &item->showVertexNormals);
				ImGui::TreePop();
			}
		}

		
		//TEXTURES INFO
		if (ImGui::CollapsingHeader("Texture")) {

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
			ImGui::TextColored({ 255,255,0,1 }, "%s", nameTexture);

			if (item->is_Textured) {
				ImGui::Text("Texture Path:");
				ImGui::SameLine(0.0f, 10.0f);
				const char* pathnameTexture = item->TextureData.texture_path.c_str();
				ImGui::TextColored({ 255,255,0,1 }, "%s", pathnameTexture);
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
			
			ImGui::Text("Texture Width");
			ImGui::SameLine(0.0f, 10.0f);
			ImGui::TextColored({ 255,255,0,1 }, "%d", item->TextureData.width);
			
			ImGui::Text("Texture Height");
			ImGui::SameLine(0.0f, 10.0f);
			ImGui::TextColored({ 255,255,0,1 }, "%d", item->TextureData.height);

			ImGui::Text("Texture id");
			ImGui::SameLine(0.0f, 10.0f);
			ImGui::TextColored({ 255,255,0,1 }, "%d", item->TextureData.texture_id);

			ImGui::Image((void*)(intptr_t)item->TextureData.texture_id, { 200,200 });
		}

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


	App->editor->ConsoleLogs.push_back(tmp_string2);
}