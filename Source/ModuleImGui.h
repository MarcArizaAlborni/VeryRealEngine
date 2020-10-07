

#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"

class Primitive;

class ModuleImGui : public Module
{
public:
	ModuleImGui(Application* app,bool start_enabled = true);
	~ModuleImGui();

	bool Start();
	update_status Update();
	

	bool CleanUp();

private:

	p2DynArray<Primitive*> primitives;


	
	SDL_WindowFlags window_flags;
	SDL_GLContext gl_context;
	


	bool on = false;
	bool on_config = false;
	bool done = false;


	//Window Bools

	bool show_demo_window;
	bool show_window_2;
	bool exit_engine_window;
	bool show_configuration_window;

	bool show_config_window;



	// Window Manager Bools

	bool OnInit;
	
	bool vsync_active;




};
