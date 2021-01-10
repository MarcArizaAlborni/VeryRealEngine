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
class Component_Listener;
class Component_Source;
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
	void DrawObjectInfo(Game_Object* item, Component_Mesh* MeshInfo, Component_Texture* TextureInfo, Component_Transform* TransInfo, Component_Camera* CameraInfo, Component_Listener* ListenerInfo, Component_Source* SourceInfo);
	bool LookForChildrenToBeDrawn(Game_Object* item);

	float testoa;

private:
	void EqualizeSpatialObjScale(Game_Object* Object, Component_Transform* TransCMP);
	//Combo Stuff
	const char* SelectedComboItem="none";

	bool isSpatial = false;
};

#endif