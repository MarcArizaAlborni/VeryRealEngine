#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"


#include "libraries/ImGui/imgui.h"
#include "libraries/ImGui/imgui_internal.h"
#include "libraries/ImGui/imgui_impl_sdl.h"
#include "libraries/ImGui/imgui_impl_opengl3.h"
		  
#include "libraries/Glew/include/GL/glew.h" // extension lib
#include "libraries/SDL/include/SDL_opengl.h"

class Primitive;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Window* window;
	SDL_WindowFlags window_flags;
	SDL_GLContext gl_context;
	//ImGuiIO* io = nullptr;

	bool show_demo_window;
	bool show_another_window;

	bool done = false;

};
