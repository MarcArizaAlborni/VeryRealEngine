#pragma once
#ifndef __Inspector_H__
#define __Inspector_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

struct GameObject;
class ModuleInspectorGameObject : public Module
{
public:
	ModuleInspectorGameObject(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleInspectorGameObject();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	//Inspector Window Functions

	void CreateInspectorWindow();
	void ShowSelectedObjectInfo(GameObject* object);
	GameObject* ObjectToBeShownInspector = NULL;
	//Inspector Window Bools

	bool ShowInspectorWindow;
	float testoa;


	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
};

#endif