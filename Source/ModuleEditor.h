#pragma once
#ifndef __ModuleEditor_H__
#define __ModuleEditor_H__
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include <vector>
#include "libraries/ImGUI/imgui.h"

class ModuleEditor : public Module
{
public:

	ModuleEditor(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleEditor();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

private:

	SDL_WindowFlags window_flags;
	SDL_GLContext gl_context;

	// ---------------About Window---------------
	void CreateAboutWindow();

	
	bool done = false;

	//Window Bools
	bool show_demo_window;
	bool show_main_window;

	// Window Manager Bools
	bool OnInit;

	ImVec4 clear_color;



	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
   
};

#endif