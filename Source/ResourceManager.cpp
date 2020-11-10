#include "Globals.h"
#include "Application.h"
#include "ResourceManager.h"
#include <filesystem>

namespace fs = std::filesystem;






ResourceManager::ResourceManager(Application* app, const char* name, bool start_enabled) : Module(app, "ResourceManager", start_enabled)
{

}

ResourceManager::~ResourceManager()
{

}

bool ResourceManager::Start()
{

	std::string path = "Assets";
	for (const auto& entry : fs::recursive_directory_iterator(path)) {

		Resource* Item = new Resource();
		std::string PathName = entry.path().string();
		const char* PathName_C = PathName.c_str();


		if (ResourceEntryList.size() == 0) {
			Item->Name = path;
			ResourceEntryList.push_back(Item);
		}

		if (App->input->CheckImportedFileType(".fbx", PathName_C) != -1) {
		}
		else if (App->input->CheckImportedFileType(".FBX", PathName_C) != -1) {
		}
		else if (App->input->CheckImportedFileType(".png", PathName_C) != -1) {
		}
		else if (App->input->CheckImportedFileType(".PNG", PathName_C) != -1) {
		}
		else if (App->input->CheckImportedFileType(".dds", PathName_C) != -1) {
		}
		else if (App->input->CheckImportedFileType(".DDS", PathName_C) != -1) {
		}
		else {
			Item->Name = PathName;

			ResourceEntryList.push_back(Item);
		}

		ResourceEntryList.size();

	}
	return true;
}

update_status ResourceManager::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ResourceManager::CleanUp()
{
	return true;
}

void ResourceManager::CreateResourcesWindow()
{
	if (App->mainMenubar->show_resources_window) {

		ImGui::Begin("Resouces", &App->mainMenubar->show_resources_window);

		ImGui::Checkbox("Show Textures", &resource_display_textures);
		ImGui::SameLine();
		ImGui::Checkbox("Show Meshes", &resource_display_mesh);

		/*if (resource_display_textures == true) {

			if (App->meshimporter->LoadedTexturesList.size() > 0) {

				TextureInfo* TextureToPrint;
				std::vector<TextureInfo*>::iterator ItTex = App->meshimporter->LoadedTexturesList.begin();
				for (int i = 0; i < App->meshimporter->LoadedTexturesList.size(); ++i) {

					TextureToPrint = *ItTex;

					ImGui::ImageButton((void*)(intptr_t)TextureToPrint->texture_id, { 50,50 });

					ImGui::SameLine();

					++ItTex;
				}
			}
		}*/

		

		if (resource_display_mesh == true) {

			
		}

		
	
		std::vector<Resource*>::iterator ResIt = ResourceEntryList.begin();
		
		for (int r = 0; r < ResourceEntryList.size(); ++r) {

			Resource* ItemR = *ResIt;

			const char* PathName_R = ItemR->Name.c_str();

			if (App->input->CheckImportedFileType(".fbx", ItemR->Name) != -1) {
				ImGui::ImageButton((void*)(intptr_t)App->textureImporter->MeshIcon.texture_id, { 50,50 });
				ImGui::SameLine();
				ImGui::Text(PathName_R);


			}
			else if (App->input->CheckImportedFileType(".FBX", ItemR->Name) != -1) {
				ImGui::ImageButton((void*)(intptr_t)App->textureImporter->MeshIcon.texture_id, { 50,50 });
				ImGui::SameLine();
				ImGui::Text(PathName_R);


			}
			else if (App->input->CheckImportedFileType(".png", ItemR->Name) != -1) {
				ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
				ImGui::SameLine();
				ImGui::Text(PathName_R);

			}
			else if (App->input->CheckImportedFileType(".PNG", ItemR->Name) != -1) {
				ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
				ImGui::SameLine();
				ImGui::Text(PathName_R);

			}
			else if (App->input->CheckImportedFileType(".dds", ItemR->Name) != -1) {
				ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
				ImGui::SameLine();
				ImGui::Text(PathName_R);

			}
			else if (App->input->CheckImportedFileType(".DDS", ItemR->Name) != -1) {
				ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
				ImGui::SameLine();
				ImGui::Text(PathName_R);

			}
			else {
				ImGui::ImageButton((void*)(intptr_t)App->textureImporter->FolderIcon.texture_id, { 50,50 });
				ImGui::SameLine();
				ImGui::Text(PathName_R);

			}


			++ResIt;
		}
		
	
		
			/*std::string PathName=entry.path().string();
			const char* PathName_C = PathName.c_str();*/
			
			/*if (App->input->CheckImportedFileType(".fbx", PathName_C) != -1) {
				ImGui::ImageButton((void*)(intptr_t)App->textureImporter->MeshIcon.texture_id, { 50,50 });
				ImGui::SameLine();
				ImGui::Text(PathName_C);


			}
			else if (App->input->CheckImportedFileType(".FBX", PathName_C) != -1) {
				ImGui::ImageButton((void*)(intptr_t)App->textureImporter->MeshIcon.texture_id, { 50,50 });
				ImGui::SameLine();
				ImGui::Text(PathName_C);


			}
			else if (App->input->CheckImportedFileType(".png", PathName_C) != -1) {
				ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
				ImGui::SameLine();
				ImGui::Text(PathName_C);

			}
			else if (App->input->CheckImportedFileType(".PNG", PathName_C) != -1) {
				ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
				ImGui::SameLine();
				ImGui::Text(PathName_C);

			}
			else if (App->input->CheckImportedFileType(".dds", PathName_C) != -1) {
				ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
				ImGui::SameLine();
				ImGui::Text(PathName_C);

			}
			else if (App->input->CheckImportedFileType(".DDS", PathName_C) != -1) {
				ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
				ImGui::SameLine();
				ImGui::Text(PathName_C);

			}
			else {
				ImGui::ImageButton((void*)(intptr_t)App->textureImporter->FolderIcon.texture_id, { 50,50 });
				ImGui::SameLine();
				ImGui::Text(PathName_C);

			}*/

			//delete Item;
			ResourceEntryList.size();
			
		

		
		
		

		

		ImGui::End();
	}
}

void ResourceManager::CreateConsolelog(const char file[], int line, const char* format, ...)
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

