#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"


class ModuleEditor : public Module
{
public:
	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

private:

	SDL_WindowFlags window_flags;
	SDL_GLContext gl_context;

	//Window Bools

	bool show_config_window;

	
};