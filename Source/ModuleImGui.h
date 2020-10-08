

#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include <vector>
#include "libraries/ImGUI/imgui.h"

class Primitive;

#define FPS_LOG_SIZE 100

class ModuleImGui : public Module
{
public:
	ModuleImGui(Application* app,bool start_enabled = true);
	~ModuleImGui();

	bool Start();
	update_status Update(float dt);
	
	bool CleanUp();

private:

	p2DynArray<Primitive*> primitives;

	
	SDL_WindowFlags window_flags;
	SDL_GLContext gl_context;
	
	// ------------------Main Bar------------------
	void CreateMainMenuBar();
	void CreateMainMenuBar_File();
	void CreateMainMenuBar_Edit();
	void CreateMainMenuBar_View();
	void CreateMainMenuBar_Help();

	// ---------------Config Window---------------
	void CreateConfigWindow();
	void CreateConfigWindow_Options();
	void CreateConfigWindow_Application();
	void CreateConfigWindow_Window();

	// ---------------Hardware Window---------------
	void CreateHardwareWindow();

	bool on = false;
	bool on_config = false;
	bool done = false;


	//Window Bools
	bool show_demo_window;
	bool show_window_2;
	bool exit_engine_window;
	bool show_configuration_window;

	bool active_window;
	bool active_fullscreen;
	bool active_Resizable;
	bool active_Borderless;
	bool active_Full_Desktop;

	bool show_config_window;

	// Window Manager Bools
	bool OnInit;
	bool vsync_active;

	ImVec4 clear_color;





};
