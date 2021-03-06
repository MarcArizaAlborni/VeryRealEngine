#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ResourceManager.h"
#include "ModuleTextureImporter.h"
#include "ModuleEditor.h"
#include <filesystem>
#include "FileSystem.h"
#include "ModuleMeshImporter.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentTexture.h"
#include "libraries/PhysFS/include/physfs.h"

#pragma comment( lib, "libraries/PhysFS/libx86/physfs.lib" )

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
	if (ResourceTimer.ReadSec() > Time + 120) {

		Time = ResourceTimer.ReadSec();
		ReadMainResourcesFolder();
	}


	




	if (ModificationHasBeen) {
		ModificationHasBeen = false;
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
			
		       ImGui::Begin("Assets", &App->editor->show_resources_window);
		       
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

						
						if (ImGui::Button(PathName_R, { 20,20 })) {
						}
						DragDropSetAsSource(ItemR);
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
						DragDropSetAsSource(ItemR);
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
						DragDropSetAsSource(ItemR);
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
						DragDropSetAsSource(ItemR);
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
						DragDropSetAsSource(ItemR);
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
						DragDropSetAsSource(ItemR);
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
						DragDropSetAsSource(ItemR);
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
						DragDropSetAsSource(ItemR);
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
						DragDropSetAsSource(ItemR);
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
						DragDropSetAsSource(ItemR);
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
	
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(60.0f, 0.0f));
	ImGui::SameLine();

	if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->AddFolderIcon.texture_id, { 30,30 })) {
		
		CreateNewFolder = true;


	}

	ImGui::SameLine();

	if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawReloadIcon.texture_id, { 30,30 })) {
		ModificationHasBeen = true;
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

			if (ImGui::InputText("Folder Name ", (char*)NewNameC, 100, ImGuiInputTextFlags_EnterReturnsTrue)) {

				std::string FinalName = NewNameC;
				if(FinalName !=""){

				    std::string Copy = FinalName;
				    std::string FinalCopy;
				    FinalCopy = Name + Copy;
				    
				    
				    fs::rename(Item->Name, FinalCopy);

					WantRenameFolder = false;
					Item->toBeRenamed = false;
					ModificationHasBeen = true;
				    Item->Name = FinalCopy;
				}
			}

			ImGui::End();
		}
	}
}

void ResourceManager::CreateWindowDeleteFolder(Resource* Item)
{
	if (WantDeleteFolder == true) {

		if (Item->toBeDeleted) {
			ImGui::Begin("DeleteFolder", &WantDeleteFolder, ImGuiWindowFlags_NoDocking |
				ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

			std::string PreName;
			std::string FileName;

			GetSplittedFile(Item->Name.c_str(), nullptr, &PreName, &FileName);

			const char* NewNameC = FileName.c_str();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 0.25f));
			if (ImGui::Button("YES"))
			{
				std::string FinalName = PreName + FileName;
				
				if (App->filemanager->Exists(FinalName.c_str())) {

					if (PHYSFS_delete(FinalName.c_str()) == 0) {

						LOG("[ERROR] Error deleting folder, make sure it is empty! ");
					}

				}
	
				WantDeleteFolder = false;
			    Item->toBeDeleted = false;
				ModificationHasBeen = true;
			}

			ImGui::PopStyleColor();

			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.25f));
			if (ImGui::Button("NO"))
			{
				WantDeleteFolder = false;

				Item->toBeDeleted = false;
				ModificationHasBeen = true;
				//ImGui::CloseCurrentPopup();
			}
			ImGui::PopStyleColor();

			ImGui::End();
		}
	}
}

void ResourceManager::SelectTypeOfFile(std::string Name)
{
	std::string LastName;
	std::string StarterName;
	std::string Extension;
	App->filemanager->SplitFilePath(Name.c_str(), nullptr, &StarterName, &Extension);

	GetSplittedFile(Name.c_str(), nullptr, &StarterName, &LastName);

	std::string FullPath = StarterName + LastName;

	if (Extension == "fbx" || Extension == "FBX") {

		App->meshimporter->LoadFile_Mesh(FullPath.c_str());
	}

	else if (Extension == "PNG" || Extension == "png" || Extension == "tga" || Extension == "TGA" || Extension == "DDS" || Extension == "dds") {
		
		std::vector<Game_Object*>::iterator It = App->geometrymanager->ObjectsOnScene.begin();
		for (int i = 0; i < App->geometrymanager->ObjectsOnScene.size(); ++i) {

			Game_Object* Object = *It;

			if (Object->ToBeDrawInspector == true) {
				ModelSelected = true;
				ObjectToGiveTexture = Object;
			}

			CheckSelectedObjectsChild(Object);

			++It;
		}

		if (ModelSelected == true) {

			App->editor->ToVisualizeTexture = App->textureImporter->LoadTextureImage(FullPath.c_str());

			Component_Texture* MeshComp = (Component_Texture*)ObjectToGiveTexture->GetComponent(Component_Types::Texture);

			MeshComp->Texture = &App->editor->ToVisualizeTexture;

			ObjectToGiveTexture = nullptr;

			ModelSelected = false;

		}
		else {

			App->editor->ToVisualizeTexture=App->textureImporter->LoadTextureImage(FullPath.c_str());

			App->editor->VisualizeTextureWindow = true;

		}
	}
}

void ResourceManager::DragDropSetAsSource(Resource* ItemToDrag)
{
	if (ImGui::BeginDragDropSource()) {

		ImGui::SetDragDropPayload("Dragged_Folder_File", ItemToDrag, sizeof(Resource));
		CopyItemFileResource = ItemToDrag;
		ImGui::EndDragDropSource();
	}
}

void ResourceManager::CheckSelectedObjectsChild(Game_Object* ItemToCheck)
{
	std::vector<Game_Object*>::iterator It = ItemToCheck->Children_List.begin();
	for (int i = 0; i < ItemToCheck->Children_List.size(); ++i) {

		Game_Object* Object = *It;

		if (Object->ToBeDrawInspector == true) {
			ModelSelected = true;
			ObjectToGiveTexture = Object;
		}

		CheckSelectedObjectsChild(Object);

		++It;
	}
}

void ResourceManager::CreateWindowDropFile()
{
	if (CopyItemFileResource != nullptr) {

		ImGuiWindowFlags Flags=NULL;
		
		//Flags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
		ImGui::Begin("DropFileHere",nullptr,Flags);
		ImVec2 SizeW=ImGui::GetWindowSize();
		ImGui::BeginChild("DropFileHereChild", { 1071,714 }, false, Flags);
		ImGui::EndChild();

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Dragged_Folder_File"))
			{

				std::string FileToLoad = CopyItemFileResource->Name;

				SelectTypeOfFile(FileToLoad);
				CopyItemFileResource = nullptr;

			}
			ImGui::EndDragDropTarget();
		}
		ImGui::End();
	}
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
						
						ImGui::Image((void*)(intptr_t)App->textureImporter->MeshIcon.texture_id, { 50,50 });
						ImGui::SameLine();

						if (ImGui::Button(PathName_R, { 150,20 })) {}

						DragDropSetAsSource(ItemRC);

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
						DragDropSetAsSource(ItemRC);
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
						DragDropSetAsSource(ItemRC);
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

						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						ImGui::Button(PathName_R, { 150,20 });
						DragDropSetAsSource(ItemRC);
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
						DragDropSetAsSource(ItemRC);
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
						DragDropSetAsSource(ItemRC);
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

						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						ImGui::Button(PathName_R, { 150,20 });
						DragDropSetAsSource(ItemRC);
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

						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						ImGui::Button(PathName_R, { 150,20 });
						DragDropSetAsSource(ItemRC);
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

						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						ImGui::Button(PathName_R, { 150,20 });
						DragDropSetAsSource(ItemRC);
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

						ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
						ImGui::SameLine();
						ImGui::Button(PathName_R, { 150,20 });
						DragDropSetAsSource(ItemRC);
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

				   	ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
				   	ImGui::SameLine();
				   	ImGui::Button(PathName_R, { 150,20 });
					DragDropSetAsSource(ItemRC);
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

				  	ImGui::Image((void*)(intptr_t)App->textureImporter->TextureIcon.texture_id, { 50,50 });
				  	ImGui::SameLine();
				  	ImGui::Button(PathName_R, { 150,20 });
					DragDropSetAsSource(ItemRC);
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