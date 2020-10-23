#pragma once
#ifndef __Hierarchy_H__
#define __Hierarchy_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class ModuleHierarchyGameObject : public Module
{
public:
	ModuleHierarchyGameObject(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleHierarchyGameObject();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	//Hierarchy Window Functions

	void CreateHierarchyWindow();
	
	void InspectorInfo(GameObject* Object, int uid);
	//Hierarchy Window Bools

	bool ShowHierarchyWindow;

	

	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
};

#endif