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
	

	ReadMainResourcesFolder();

	
	
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

			 


		       ImGui::Begin("Resouces", &App->mainMenubar->show_resources_window);
		       
		       ImGui::Checkbox("Show Textures", &resource_display_textures);
		       ImGui::SameLine();
		       ImGui::Checkbox("Show Meshes", &resource_display_mesh);
			   ImGui::SameLine();
			   ImGui::Checkbox("Show Folders", &resource_display_folder);
		  
		  
		    std::vector<Resource*>::iterator ResIt = ResourceEntryList.begin();
		    
		    for (int r = 0; r < ResourceEntryList.size(); ++r) {
				
				
		    	Resource* ItemR = *ResIt;
		    
		    	const char* PathName_R = ItemR->Name.c_str();
				
		    	if (App->input->CheckImportedFileType(".fbx", ItemR->Name) != -1) {
					if (resource_display_mesh) {
						//(ImGui::ImageButton((void*)(intptr_t)App->textureImporter->MeshIcon.texture_id, { 50,50 })) 


						if (ImGui::Button(PathName_R, { 20,20 })) {}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}
		    
		    	}
		    	else if (App->input->CheckImportedFileType(".FBX", ItemR->Name) != -1) {
					if (resource_display_mesh) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->MeshIcon.texture_id, { 50,50 });
						if (ImGui::Button(PathName_R, { 20,20 })) {}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}
		    	}
		    	else if (App->input->CheckImportedFileType(".png", ItemR->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						if (ImGui::Button(PathName_R, { 20,20 })) {}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}
		    
		    	}
		    	else if (App->input->CheckImportedFileType(".PNG", ItemR->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						if (ImGui::Button(PathName_R, { 20,20 })) {}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}
		    
		    	}
		    	else if (App->input->CheckImportedFileType(".dds", ItemR->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						if (ImGui::Button(PathName_R, { 20,20 })) {}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}
		    
		    	}
		    	else if (App->input->CheckImportedFileType(".DDS", ItemR->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						if (ImGui::Button(PathName_R, { 20,20 })) {}
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
						//ImGui::SameLine();
						//ImGui::Text(PathName_R);
					}
		    
		    	}
				
				
		    	++ResIt;
		    }
		    
		    ResourceEntryList.size();
		    
		    ImGui::End();
	        
		}
	}
}

void ResourceManager::AddResourceChild(Resource* Parent, Resource* Child)
{




}

Resource* ResourceManager::CheckFolderChilds(Resource* child)
{

	std::string path = child->Name;
	Resource* Item = new Resource();
	for (const auto& entry : fs::directory_iterator(path)) {

		
		std::string PathName = entry.path().string();
		const char* PathName_C = PathName.c_str();
		Item->Name = PathName;
		CreateNewResourceWindowEntry(Item);
	}

	return Item;

}

void ResourceManager::ReadMainResourcesFolder()
{
	std::string path = "Assets";
	for (const auto& entry : fs::directory_iterator(path)) {

		Resource* Item = new Resource();
		
		std::string PathName = entry.path().string();
		const char* PathName_C = PathName.c_str();


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
			//CheckFolderChilds(Item);
			ResourceEntryList.push_back(Item);
		}

		std::vector<Resource*>::iterator IteratorRes = ResourceEntryList.begin();
		for (int pos = 0; pos < ResourceEntryList.size(); ++pos) {

			Resource* ResItem = *IteratorRes;
			ResourceAddChildren(ResItem);
			++IteratorRes;
		}


	}
}

void ResourceManager::CreateNewResourceWindowEntry(Resource* ResourceToAdd)
{
	if (App->input->CheckImportedFileType(".fbx", ResourceToAdd->Name) != -1) {
		//Item->Name = PathName;
		ResourceToAdd->ResourceEntryChildsList.push_back(ResourceToAdd);
	}
	else if (App->input->CheckImportedFileType(".FBX", ResourceToAdd->Name) != -1) {
		//Item->Name = PathName;
		ResourceToAdd->ResourceEntryChildsList.push_back(ResourceToAdd);
	}
	else if (App->input->CheckImportedFileType(".png", ResourceToAdd->Name) != -1) {
		//Item->Name = PathName;
		ResourceToAdd->ResourceEntryChildsList.push_back(ResourceToAdd);
	}
	else if (App->input->CheckImportedFileType(".PNG", ResourceToAdd->Name) != -1) {
		//Item->Name = PathName;
		ResourceToAdd->ResourceEntryChildsList.push_back(ResourceToAdd);
	}
	else if (App->input->CheckImportedFileType(".dds", ResourceToAdd->Name) != -1) {
		//Item->Name = PathName;
		ResourceToAdd->ResourceEntryChildsList.push_back(ResourceToAdd);
	}
	else if (App->input->CheckImportedFileType(".DDS", ResourceToAdd->Name) != -1) {
		//Item->Name = PathName;
		ResourceToAdd->ResourceEntryChildsList.push_back(ResourceToAdd);
	}
	else {
		ResourceToAdd=CheckFolderChilds(ResourceToAdd);
		ResourceToAdd->ResourceEntryChildsList.push_back(ResourceToAdd);
	}

}

void ResourceManager::ResourceAddChildren(Resource* Parent)
{

	std::string path = Parent->Name;
	
	for (const auto& entry : fs::directory_iterator(path)) {
		Resource* Item = new Resource();

		std::string PathName = entry.path().string();
		const char* PathName_C = PathName.c_str();
		Item->Name = PathName;
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

			ResourceAddChildren(Item);
		}
		Parent->ResourceEntryChildsList.push_back(Item);
		
	}

}

void ResourceManager::DrawResourcesItems(Resource* Parent)
{

	if (App->mainMenubar->show_resources_window) {

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

			ImGui::Begin("Resouces", &App->mainMenubar->show_resources_window);

			ImGui::Checkbox("Show Textures", &resource_display_textures);
			ImGui::SameLine();
			ImGui::Checkbox("Show Meshes", &resource_display_mesh);
			ImGui::SameLine();
			ImGui::Checkbox("Show Folders", &resource_display_folder);


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

						ImGui::Button(PathName_R, { 150,20 });
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else if (App->input->CheckImportedFileType(".FBX", ItemRC->Name) != -1) {
					if (resource_display_mesh) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->MeshIcon.texture_id, { 50,50 });
						ImGui::Button(PathName_R, { 150,20 });
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}
				}
				else if (App->input->CheckImportedFileType(".png", ItemRC->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Button(PathName_R, { 150,20 });
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else if (App->input->CheckImportedFileType(".PNG", ItemRC->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Button(PathName_R, { 150,20 });
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else if (App->input->CheckImportedFileType(".dds", ItemRC->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Button(PathName_R, { 150,20 });
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else if (App->input->CheckImportedFileType(".DDS", ItemRC->Name) != -1) {
					if (resource_display_textures) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::Button(PathName_R, { 150,20 });
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}
				else {
					if (resource_display_folder) {
						//ImGui::ImageButton((void*)(intptr_t)App->textureImporter->FolderIcon.texture_id, { 50,50 });
						if (ImGui::Button(PathName_R, { 150,20 })) {
							ItemRC->ChildsToBeDrawnResources = true;
						}
						ImGui::SameLine();
						ImGui::Text(PathName_R);
					}

				}

				++ResItChild;
			}

			ResourceEntryList.size();

			ImGui::End();

		}
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


/*if (App->mainMenubar->show_resources_window) {


		ImGui::Begin("Resouces", &App->mainMenubar->show_resources_window);

		ImGui::Checkbox("Show Textures", &resource_display_textures);
		ImGui::SameLine();
		ImGui::Checkbox("Show Meshes", &resource_display_mesh);


		std::vector<Resource*>::iterator ResIt = ResourceEntryList.begin();

		for (int r = 0; r < ResourceEntryList.size(); ++r) {

			Resource* ItemR = *ResIt;

			const char* PathName_R = ItemR->Name.c_str();

			if (App->input->CheckImportedFileType(".fbx", ItemR->Name) != -1) {
				if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->MeshIcon.texture_id, { 50,50 })) {
					ItemR->ChildsToBeDrawnResources = true;
				}
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

			ResourceEntryList.size();

		ImGui::End();
	}*/