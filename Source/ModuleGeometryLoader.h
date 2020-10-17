#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#define MAX_LIGHTS 8

struct MeshInfo;

class ModuleGeometryLoader : public Module
{
public:
	ModuleGeometryLoader(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleGeometryLoader();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();


public:
	// Insert Primitives
	void DrawCube();
	void DrawPyramid();
	void DrawCylinder();

	void DrawMesh(const MeshInfo* mesh);

public:

	MeshInfo* warrior;
};