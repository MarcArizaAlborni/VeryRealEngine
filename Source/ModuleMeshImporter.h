#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

struct MeshInfo
{
	uint id_index; // index in VRAM
	uint num_index;
	uint* index;
	uint id_vertex; // unique vertex in VRAM
	uint num_vertex;
	float* vertex;
};

class ModuleMeshImporter : public Module
{
public:
	ModuleMeshImporter(Application* app, bool start_enabled = true);
	~ModuleMeshImporter();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	MeshInfo* LoadMesh(char* file_path);
	

private:

	
	
};