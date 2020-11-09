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

//struct ResourceType {
//
//	GameObject Mesh;
//	TextureInfo Texture;
//	bool is_texture = false;
//	bool is_mesh = false;
//
//};
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


	void CreateResourcesWindow();

	/*std::vector<ResourceType*> ResourcesList;*/

public:

	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
};

#endif