#pragma once
#ifndef __Inspector_H__
#define __Inspector_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class ModuleInspectorGameObject : public Module
{
public:
	ModuleInspectorGameObject(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleInspectorGameObject();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	//Hierarchy Window Functions

	void CreateInspectorWindow();
	//Hierarchy Window Bools

	bool ShowInspectorWindow;



	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
};

#endif