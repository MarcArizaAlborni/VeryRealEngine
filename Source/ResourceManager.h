#pragma once
#ifndef __ResourceManager_H__
#define __ResourceManager_H__
#include "Module.h"
#include "Globals.h"
#include <iomanip>
#include <fstream>

struct aiScene;

struct TextureInfo;
struct MeshTransformation;
struct Vertex_Sub;
struct MeshInfo;
struct GameObject;

struct Resource {

	std::string Name = "Name";
	bool ChildsToBeDrawnResources = false;
	std::vector<Resource*> ResourceEntryChildsList;

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

	std::vector<Resource*> ResourceEntryList;
	
	void AddResourceChild(Resource* Parent, Resource* Child);
	Resource* CheckFolderChilds(Resource* childtofind);
	void ReadMainResourcesFolder();
	void CreateNewResourceWindowEntry(Resource* ResourceToAdd);



	void ResourceAddChildren(Resource* Parent);

	void DrawResourcesItems(Resource* Parent);
	
public:

	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
};

#endif