#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include <vector>
#include "libraries/ImGUI/imgui.h"


class ModuleEditorMainMenuBar : public Module
{
public:

	ModuleEditorMainMenuBar(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleEditorMainMenuBar();

	bool Start();

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

	bool show_hierarchy_window;

	bool show_inspector_window;

	bool show_popup_want_close;
	bool show_popup_want_close2;

	

	bool drawplane;
	bool drawcube;
	bool drawpyramid;
	bool drawcylinder;
	bool drawsphere;


	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
};