#pragma once
#ifndef __ModuleLoader_H__
#define __ModuleLoader_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Primitive.h"
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
	void DrawPlane();
	void DrawCube();
	void DrawPyramid();
	void DrawSphere();
	void DrawCylinder();

	//Meshes
	void DrawMesh(const MeshInfo* mesh);

	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
};

#endif