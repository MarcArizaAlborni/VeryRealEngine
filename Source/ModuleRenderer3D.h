#pragma once
#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#define MAX_LIGHTS 8

struct MeshInfo;
struct Vertex_Sub;
struct GameObject;
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

	void GenerateVertexBuffer(Vertex_Sub* vertex, uint& size, uint& id_vertex);
	void GenerateIndexBuffer(uint* index, uint& size, uint& id_index);
	void GenerateTextBuffer(float* text_coords, uint& num_text_coords, uint& id_text_coords);
	void GenerateNormalBuffer(GameObject* mesh, Vertex_Sub* normals);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;



#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);


private:

	void LoadIconsTextures();

};

#endif