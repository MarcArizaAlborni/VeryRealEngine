#pragma once
#ifndef __ModuleImporters_H__
#define __ModuleImporters_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

// Class Mesh
struct MeshInfo
{
	uint id_index=0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex=nullptr;

	
};

struct GameObject {

	MeshInfo mesh_info;

	std::string mesh_name;

	bool is_Selected;

	bool is_Textured;

};

class ModuleMeshImporter : public Module
{
public:
	ModuleMeshImporter(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleMeshImporter();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	//Mesh Import functions 
	MeshInfo* LoadMesh(char* file_path);

	//Mesh Import variables 
	std::vector<MeshInfo*> MeshesOnScene;


	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
	
};

#endif