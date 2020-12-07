#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ResourceManager.h"
#include "ModuleTextureImporter.h"
#include "ModuleEditor.h"
#include <filesystem>
#include "FileSystem.h"

namespace fs = std::filesystem;

ResourceManager::ResourceManager(Application* app, const char* name, bool start_enabled) : Module(app, "ResourceManager", start_enabled)
{
}

ResourceManager::~ResourceManager()
{
}

bool ResourceManager::Start()
{
	ResourceTimer.Start();
	Time = 0;
	ReadMainResourcesFolder();

	return true;
}

update_status ResourceManager::Update(float dt)
{

	if (ResourceTimer.ReadSec() > Time + 20) {

		Time = ResourceTimer.ReadSec();
		ReadMainResourcesFolder();

	}

	

	return UPDATE_CONTINUE;
}

bool ResourceManager::CleanUp()
{
	return true;
}

void ResourceManager::CreateResourcesWindow()
{
	if (App->editor->show_resources_window) {

		bool DrawInitialParents = true;
		std::vector<Resource*>::iterator ResIt = ResourceEntryList.begin();
		for (int r = 0; r < ResourceEntryList.size(); ++r) {

			Resource* ItemR = *ResIt;

			if (ItemR->ChildsToBeDrawnResources == true) {
				DrawInitialParents = false;
				DrawResourcesItems(ItemR);
				r = ResourceEntryList.size();
			}
			
			++ResIt;
		}

		

		if (DrawInitialParents == true) {

			
			StoreCurrentOpenFolderUpdate(""); //This case is the general folder so no name
			
		       ImGui::Begin("Resouces", &App->editor->show_resources_window);
		       
		       ImGui::Checkbox("Show Textures", &resource_display_textures);
		       ImGui::SameLine();
		       ImGui::Checkbox("Show Meshes", &resource_display_mesh);
			   ImGui::SameLine();
			   ImGui::Checkbox("Show Folders", &resource_display_folder);

			   DrawFolderOptionIcons("");
		  
		    std::vector<Resource*>::iterator ResIt = ResourceEntryList.begin();
		    
		    for (int r = 0; r < ResourceEntryList.size(); ++r) {
				

				
		    	Resource* ItemR = *ResIt;
		    
		    	const char* PathName_R = ItemR->Name.c_str();
				
		    	if (App->input->CheckImportedFileType(".fbx", ItemR->Name) != -1) {
					if (resource_display_mesh) {
						//(ImGui::ImageButton((void*)(intptr_t)App->textureImporter->MeshIcon.texture_id, { 50,50 })) 
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();

						
						if (ImGui::Button(PathName_R, { 20,20 })) {}
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {

								ItemR->SelectedFolderHoverClick = true;

							}
						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}
		    
		    	}
		    	else if (App->input->CheckImportedFileType(".FBX", ItemR->Name) != -1) {
					if (resource_display_mesh) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->MeshIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						if (ImGui::Button(PathName_R, { 20,20 })) {}
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {

								ItemR->SelectedFolderHoverClick = true;

							}
						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}
		    	}
		    	else if (App->input->CheckImportedFileType(".png", ItemR->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						if (ImGui::Button(PathName_R, { 20,20 })) {}
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {

								ItemR->SelectedFolderHoverClick = true;

							}
						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}
		    
		    	}
		    	else if (App->input->CheckImportedFileType(".PNG", ItemR->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						if (ImGui::Button(PathName_R, { 20,20 })) {}
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {

								ItemR->SelectedFolderHoverClick = true;

							}
						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}
		    
		    	}
		    	else if (App->input->CheckImportedFileType(".dds", ItemR->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						if (ImGui::Button(PathName_R, { 20,20 })) {}
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {

								ItemR->SelectedFolderHoverClick = true;

							}
						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}
		    
		    	}
		    	else if (App->input->CheckImportedFileType(".DDS", ItemR->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						if (ImGui::Button(PathName_R, { 20,20 })) {}
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {

								ItemR->SelectedFolderHoverClick = true;

							}
						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}
		    
		    	}
				else if (App->input->CheckImportedFileType(".waf", ItemR->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						if (ImGui::Button(PathName_R, { 20,20 })) {}
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {

								ItemR->SelectedFolderHoverClick = true;

							}
						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else if (App->input->CheckImportedFileType(".meta", ItemR->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						if (ImGui::Button(PathName_R, { 20,20 })) {}
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {

								ItemR->SelectedFolderHoverClick = true;

							}
						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else if (App->input->CheckImportedFileType(".tga", ItemR->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						if (ImGui::Button(PathName_R, { 20,20 })) {}
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {

								ItemR->SelectedFolderHoverClick = true;

							}
						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else if (App->input->CheckImportedFileType(".TGA", ItemR->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						if (ImGui::Button(PathName_R, { 20,20 })) {}
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {

								ItemR->SelectedFolderHoverClick = true;

							}
						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
		    	else {
					if (resource_display_folder) {
						/*if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->FolderIcon.texture_id, { 50,50 })) {
							ItemR->ChildsToBeDrawnResources = true;
						}*/

						ImGui::Image((void*)(intptr_t)App->textureImporter->FolderIcon.texture_id, { 50,50 });
						ImGui::SameLine();
			
						if (ImGui::Button(PathName_R, { 150,20 })) {
							ItemR->ChildsToBeDrawnResources = true;
						}
						if (ImGui::IsItemHovered()) {
							
							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {

								ItemR->SelectedFolderHoverClick = true;
								
							}
						}
					}
		    	}

				DrawFolderOptionsButtons(ItemR);
				
		    	++ResIt;
		    }
		    ResourceEntryList.size();
		    
		    ImGui::End();
	        
		}
	
	}

	
}

void ResourceManager::DrawFolderOptionIcons(std::string FolderName)
{
	// ImGui::SameLine();
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(60.0f, 0.0f));
	ImGui::SameLine();

	
	if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->AddFolderIcon.texture_id, { 30,30 })) {
		//resource_add_folder = true;
	}
	ImGui::SameLine();

	if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawReloadIcon.texture_id, { 30,30 })) {
		ReadMainResourcesFolder();

		//resource_rename_folder = true;
	}
	ImGui::SameLine();

	//if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->RemoveFolderIcon.texture_id, { 30,30 })) {

	//	//fs::remove_all("//Assets"); 

	//	//resource_remove_folder = true;
	//}
	//ImGui::SameLine();

	if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->RenameFolderIcon.texture_id, { 30,30 })) {
		
		
		//resource_rename_folder = true;
	}
}

void ResourceManager::StoreCurrentOpenFolderUpdate(std::string FolderName)
{
	StoredName = FolderName;
}

void ResourceManager::SetOpenFolder()
{
	std::vector<Resource*>::iterator It = ResourceEntryList.begin();

	for (int size = 0; size < ResourceEntryList.size(); ++size) {

		Resource* Item = *It;

		if (Item->Name == StoredName) {

			Item->ChildsToBeDrawnResources = true;

		}
		

		SetOpenFolderChildren(Item);


		++It;
	}



}

void ResourceManager::SetOpenFolderChildren(Resource* Item)
{
	std::vector<Resource*>::iterator It = Item->ResourceEntryChildsList.begin();

	for (int size = 0; size < Item->ResourceEntryChildsList.size(); ++size) {

		Resource* ItemC = *It;

		if (ItemC->Name == StoredName) {

			ItemC->ChildsToBeDrawnResources = true;

		}


		SetOpenFolderChildren(ItemC);


		++It;
	}
}

void ResourceManager::DrawFolderOptionsButtons(Resource* Item)
{
	if (Item->SelectedFolderHoverClick) {
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 0.25f));
		if (ImGui::Button("RENAME"))
		{
			WantRenameFolder = true;
			
			Item->toBeRenamed = true;
		

			//ImGui::CloseCurrentPopup();
		}
		ImGui::PopStyleColor();

		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.25f));
		if (ImGui::Button("DELETE"))
		{
			WantDeleteFolder = true;

			Item->toBeDeleted = true;
			//ImGui::CloseCurrentPopup();
		}
		ImGui::PopStyleColor();

		/*ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 1.0f, 1.0f, 0.5f));
		if (ImGui::Button("BACK"))
		{
			Item->SelectedFolderHoverClick = false;
			ImGui::CloseCurrentPopup();

		}
		ImGui::PopStyleColor();*/
	}


	CreateWindowRenameFolder(Item);
	CreateWindowDeleteFolder(Item);
	
}

void ResourceManager::GetSplittedFile(const char* full_path, std::string* path, std::string* file, std::string* NameF) const
{
	if (full_path != nullptr)
	{
		std::string full(full_path);
		NormalizedFolderPath(full);
		size_t pos_separator = full.find_last_of("\\/") + 1; //+ 1 maybe

		size_t pos_dot = full.find_last_of(".");

		*file = full.front();

		if (file != nullptr)
		{

			if (pos_separator < full.length()) {

				*file = full.substr(0, pos_separator);

				//*file = full.substr(pos_separator + 1);
			}
			else
				*file = full;
		}

		if (NameF != nullptr)
		{
			if (pos_separator < full.length())
			{
				*NameF = full.substr(pos_separator);
			
			}
			
		}
	}
}

void ResourceManager::NormalizedFolderPath(std::string& full_path) const
{
	for (std::string::iterator it = full_path.begin(); it != full_path.end(); ++it)
	{
		if (*it == '\\')
		{
			*it = '/';
		}

		else
		{
			//*it = tolower(*it);
		}
	}
}

void ResourceManager::CreateWindowRenameFolder(Resource* Item)
{
	
	if (WantRenameFolder == true) {

		if (Item->toBeRenamed) {
			ImGui::Begin("RenameFolder", &WantRenameFolder, ImGuiWindowFlags_NoDocking |
				ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);


			std::string Name;
			std::string Extension;

			GetSplittedFile(Item->Name.c_str(), nullptr, &Name, &Extension);

			const char* NewNameC = Extension.c_str();

			if (ImGui::InputText("New Folder Name ", (char*)NewNameC, 100, ImGuiInputTextFlags_EnterReturnsTrue)) {

				std::string FinalName = NewNameC;
				if(FinalName !=""){

				    std::string Copy = FinalName;
				    std::string FinalCopy;
				    FinalCopy = Name + Copy;
				    
				    
				    fs::rename(Item->Name, FinalCopy);

					WantRenameFolder = false;
					Item->toBeRenamed = false;
					//ReadMainResourcesFolder();
					//ModificationHasBeen = true;
				    Item->Name = FinalCopy;
				}
			}




			ImGui::End();
		}

	}

	

}

void ResourceManager::CreateWindowDeleteFolder(Resource* Item)
{
}


void ResourceManager::ReadMainResourcesFolder()
{
	std::vector<Resource*>::iterator It = ResourceEntryList.begin();
	for (int size = 0; size < ResourceEntryList.size(); ++size) {
		Resource* Object = *It;

		ClearResourceList(Object);

		++It;

		delete Object;
	}

	ResourceEntryList.clear();


	std::string path = "Assets";
	for (const auto& entry : fs::directory_iterator(path)) {

		Resource* Item = new Resource();
		
		std::string PathName = entry.path().string();
		const char* PathName_C = PathName.c_str();
		
		if(entry.is_directory()) {

			Item->Name = PathName;
			//CheckFolderChilds(Item);
			ResourceEntryList.push_back(Item);
		}
	}

	std::string path2 = "Library";
	for (const auto& entry : fs::directory_iterator(path2)) {

		Resource* Item = new Resource();

		std::string PathName = entry.path().string();
		const char* PathName_C = PathName.c_str();

		 if (entry.is_directory()) {

			Item->Name = PathName;
			//CheckFolderChilds(Item);
			ResourceEntryList.push_back(Item);
		 }
	}

	std::vector<Resource*>::iterator IteratorRes = ResourceEntryList.begin();
	for (int pos = 0; pos < ResourceEntryList.size(); ++pos) {

		Resource* ResItem = *IteratorRes;
		ResourceAddChildren(ResItem);
		++IteratorRes;
	}


	SetOpenFolder();
}

void ResourceManager::ResourceAddChildren(Resource* Parent)
{

	std::string path = Parent->Name;
	
	for (const auto& entry : fs::directory_iterator(path)) {
		Resource* Item = new Resource();

		std::string PathName = entry.path().string();
		const char* PathName_C = PathName.c_str();
		Item->Name = PathName;
		if (entry.is_directory()) {

			ResourceAddChildren(Item);
		}


		Parent->ResourceEntryChildsList.push_back(Item);
	}

}

void ResourceManager::DrawResourcesItems(Resource* Parent)
{
	if (App->editor->show_resources_window) {

		bool DrawInitialParents = true;
		std::vector<Resource*>::iterator ResIt = Parent->ResourceEntryChildsList.begin();
		for (int x = 0; x <Parent->ResourceEntryChildsList.size(); ++x) {

			Resource* ItemR = *ResIt;

			if (ItemR->ChildsToBeDrawnResources == true) {
				DrawInitialParents = false;
				DrawResourcesItems(ItemR);
				x= Parent->ResourceEntryChildsList.size();
			}
			++ResIt;
		}

		if (DrawInitialParents == true) {

			StoreCurrentOpenFolderUpdate(Parent->Name);  ///

			ImGui::Begin("Resouces", &App->editor->show_resources_window);

			ImGui::Checkbox("Show Textures", &resource_display_textures);
			ImGui::SameLine();
			ImGui::Checkbox("Show Meshes", &resource_display_mesh);
			ImGui::SameLine();
			ImGui::Checkbox("Show Folders", &resource_display_folder);

			DrawFolderOptionIcons("");

			std::vector<Resource*>::iterator ResItChild = Parent->ResourceEntryChildsList.begin();

			if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->BackIcon.texture_id, { 30,30 })) {
				Parent->ChildsToBeDrawnResources = false;
			}

			for (int r = 0; r < Parent->ResourceEntryChildsList.size(); ++r) {


				Resource* ItemRC = *ResItChild;

				const char* PathName_R = ItemRC->Name.c_str();

				
				
				if (App->input->CheckImportedFileType(".fbx", ItemRC->Name) != -1) {
					if (resource_display_mesh) {
						/*if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->MeshIcon.texture_id, { 50,50 })) {
							ItemRC->ChildsToBeDrawnResources = true;
						}*/
						ImGui::Image((void*)(intptr_t)App->textureImporter->MeshIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						ImGui::Button(PathName_R, { 150,20 });
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {



								ItemRC->SelectedFolderHoverClick = true;

							}

						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else if (App->input->CheckImportedFileType(".FBX", ItemRC->Name) != -1) {
					if (resource_display_mesh) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->MeshIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->MeshIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						ImGui::Button(PathName_R, { 150,20 });
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {



								ItemRC->SelectedFolderHoverClick = true;

							}

						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}
				}
				else if (App->input->CheckImportedFileType(".png", ItemRC->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						ImGui::Button(PathName_R, { 150,20 });
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {



								ItemRC->SelectedFolderHoverClick = true;

							}

						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else if (App->input->CheckImportedFileType(".PNG", ItemRC->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						ImGui::Button(PathName_R, { 150,20 });
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {



								ItemRC->SelectedFolderHoverClick = true;

							}

						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else if (App->input->CheckImportedFileType(".dds", ItemRC->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						ImGui::Button(PathName_R, { 150,20 });
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {



								ItemRC->SelectedFolderHoverClick = true;

							}

						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else if (App->input->CheckImportedFileType(".DDS", ItemRC->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						ImGui::Button(PathName_R, { 150,20 });
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {



								ItemRC->SelectedFolderHoverClick = true;

							}

						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else if (App->input->CheckImportedFileType(".waf", ItemRC->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						ImGui::Button(PathName_R, { 150,20 });
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {



								ItemRC->SelectedFolderHoverClick = true;

							}

						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else if (App->input->CheckImportedFileType(".meta", ItemRC->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						ImGui::Button(PathName_R, { 150,20 });
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {



								ItemRC->SelectedFolderHoverClick = true;

							}

						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else if (App->input->CheckImportedFileType(".TGA", ItemRC->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						ImGui::Button(PathName_R, { 150,20 });
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {



								ItemRC->SelectedFolderHoverClick = true;

							}

						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else if (App->input->CheckImportedFileType(".tga", ItemRC->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						ImGui::Button(PathName_R, { 150,20 });
						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {



								ItemRC->SelectedFolderHoverClick = true;

							}

						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else if (App->input->CheckImportedFileType(".jpg", ItemRC->Name) != -1) {
				   if (resource_display_textures) {
				   	//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
				   	ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
				   	ImGui::SameLine();
				   	ImGui::Button(PathName_R, { 150,20 });
					if (ImGui::IsItemHovered()) {

						if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {



							ItemRC->SelectedFolderHoverClick = true;

						}

					}
				   	ImGui::SameLine();
				   	ImGui::Text(PathName_R);
				   }

				}
				else if (App->input->CheckImportedFileType(".JPG", ItemRC->Name) != -1) {
				  if (resource_display_textures) {
				  	//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
				  	ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
				  	ImGui::SameLine();
				  	ImGui::Button(PathName_R, { 150,20 });
					if (ImGui::IsItemHovered()) {

						if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {



							ItemRC->SelectedFolderHoverClick = true;

						}

					}
				  	ImGui::SameLine();
				  	ImGui::Text(PathName_R);
				  }

				}
				else {
					if (resource_display_folder) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->FolderIcon.texture_id, { 50,50 });
						ImGui::Image((void*)(intptr_t)App->textureImporter->FolderIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						if (ImGui::Button(PathName_R, { 150,20 })) {
							ItemRC->ChildsToBeDrawnResources = true;
						}

						if (ImGui::IsItemHovered()) {

							if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {



								ItemRC->SelectedFolderHoverClick = true;

							}

						}

						ImGui::SameLine();
						ImGui::Text(PathName_R);


					}
				}
				DrawFolderOptionsButtons(ItemRC);
				++ResItChild;
			}

			ImGui::End();

		}
		
	}
}

void ResourceManager::ClearResourceList(Resource* Parent)
{

	std::vector<Resource*>::iterator It = Parent->ResourceEntryChildsList.begin();

	int size = 0;
	for (;size < Parent->ResourceEntryChildsList.size(); ++size) {

		Resource* Item = *It;
		
		ClearResourceList(Item);
		delete Item;
		++It;
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

	App->editor->ConsoleLogs.push_back(tmp_string2);
}


