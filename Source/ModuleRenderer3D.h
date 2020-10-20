#pragma once
#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#define MAX_LIGHTS 8

struct MeshInfo;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);

	void GenerateVertexBuffer(uint& id_vertex, const int& size, const float* vertex);
	void GenerateIndexBuffer(uint& id_index, const int& size, const uint* index);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

};

#endif