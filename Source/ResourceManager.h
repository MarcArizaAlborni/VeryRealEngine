#pragma once
#ifndef __ResourceManager_H__
#define __ResourceManager_H__
#include "Module.h"
#include "Globals.h"
#include <iomanip>
#include <fstream>

struct aiScene;

struct TextureInfo;

struct MeshInfo;
struct GameObject;
class Timer;
struct Resource {

	std::string Name = "Name";
	bool ChildsToBeDrawnResources = false;
	std::vector<Resource*> ResourceEntryChildsList;
	bool SelectedFolderHoverClick = false;
	bool toBeDeleted;
	bool toBeRenamed;

};
class ResourceManager : public Module
{
public:

	ResourceManager(Application* app, const char* name = "null", bool start_enabled = true);
	~ResourceManager();

	//bool Init();
	bool Start();
	//update_status PreUpdate(float dt);
	update_status Update(float dt);
	//update_status PostUpdate(float dt);
	bool CleanUp();


// Items for resource window

	void CreateResourcesWindow();

	bool resource_display_textures = true;
	bool resource_display_mesh = true;
	bool resource_display_folder = true;

	//folder config
	bool resource_remove_folder = false;
	bool resource_add_folder = false;
	bool resource_rename_folder = false;


	bool resource_remove_folder_window = false;
	bool resource_add_folder_window = false;
	bool resource_rename_folder_window = false;

	
	



	std::vector<Resource*> ResourceEntryList;
	
	void ReadMainResourcesFolder();
	
	void ResourceAddChildren(Resource* Parent);

	void DrawResourcesItems(Resource* Parent);

	void ClearResourceList(Resource* Parent);

	void CreateWindowDropFile();

private:
	char TextBuffer[256] = "";

	Timer ResourceTimer;
	int Time;


	void DrawFolderOptionIcons(std::string FolderName);
	void StoreCurrentOpenFolderUpdate(std::string FolderName);
	void SetOpenFolder();
	void SetOpenFolderChildren(Resource* Item);
	std::string StoredName=""; //^This function
	
	void DrawFolderOptionsButtons(Resource* Item);
	void GetSplittedFile(const char* full_path, std::string* path, std::string* file = nullptr, std::string* extension = nullptr) const;
	void NormalizedFolderPath(std::string& full_path) const;
	void CreateWindowRenameFolder(Resource* Item);
	void CreateWindowDeleteFolder(Resource* Item);
	bool WantDeleteFolder;
	bool WantRenameFolder;
	bool ModificationHasBeen=false;

	void SelectTypeOfFile(std::string Name);
	
	
public:
	Resource* CopyItemFileResource=nullptr;
	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
};

#endif