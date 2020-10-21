#pragma once
#ifndef __Hierarchy_H__
#define __Hierarchy_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class ModuleHierarchy : public Module
{
public:
	ModuleHierarchy(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleHierarchy();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	//Hierarchy Window Functions

	void HierarchyWindow();
	//Hierarchy Window Bools

	bool ShowHierarchyWindow;



	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
};

#endif