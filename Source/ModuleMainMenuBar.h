#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include <vector>
#include "libraries/ImGUI/imgui.h"


class ModuleMainMenuBar : public Module
{
public:

	ModuleMainMenuBar(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleMainMenuBar();

	// ------------------Main Bar------------------
	void CreateMainMenuBar();
	void CreateMainMenuBar_File();
	void CreateInsertPrimitivesWindow();
	void CreateMainMenuBar_Edit();
	void CreateMainMenuBar_View();
	void CreateMainMenuBar_Help();

	//Main Menu Bar Bools
	bool show_config_window;

	bool show_about_window;

	bool show_console_window;

	bool drawline;
	bool drawplane;
	bool drawcube;
	bool drawpyramid;
	bool drawcylinder;
	bool drawsphere;
};