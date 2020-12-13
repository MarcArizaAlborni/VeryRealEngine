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
class Component_Camera;
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
	void DrawObjectInfo(Game_Object* item, Component_Mesh* MeshInfo, Component_Texture* TextureInfo, Component_Transform* TransInfo, Component_Camera* CameraInfo);
	bool LookForChildrenToBeDrawn(Game_Object* item);
	//Inspector Window Bools

	//bool ShowInspectorWindow;
	float testoa;


};

#endif