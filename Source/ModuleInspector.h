#pragma once
#ifndef __Inspector_H__
#define __Inspector_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"


struct TextureInfo;
class Game_Object;
class Component_Mesh;
class Component_Texture;
class Component_Transform;
class ModuleInspectorGameObject : public Module
{
public:
	ModuleInspectorGameObject(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleInspectorGameObject();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	//Inspector Window Functions


	
	
	void DrawInspectorWindowInfo();
	void DrawObjectInfo(Game_Object* item, Component_Mesh* MeshInfo, Component_Texture* TextureInfo, Component_Transform* TransInfo);
	bool LookForChildrenToBeDrawn(Game_Object* item);
	//Inspector Window Bools

	//bool ShowInspectorWindow;
	float testoa;

	// For bounding boxes
	


	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
};

#endif