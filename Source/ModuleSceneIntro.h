//#pragma once
//#include "Module.h"
//#include "p2DynArray.h"
//#include "Globals.h"
//
//
//
//
//class Primitive;
//
//class ModuleSceneIntro : public Module
//{
//public:
//	ModuleSceneIntro(Application* app, bool start_enabled = true);
//	~ModuleSceneIntro();
//
//	bool Init();
//	bool Start();
//	update_status Update();
//	bool CleanUp();
//
//public:
//
//	SDL_Window* window;
//	SDL_WindowFlags window_flags;
//	SDL_GLContext gl_context;
//	//ImGuiIO* io = nullptr;
//
//	bool show_demo_window;
//	bool show_another_window;
//
//	bool done = false;
//
//private:
//	ImGuiIO* io = nullptr;
//	ImVec4 clear_color;
//
//};


#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"

class Primitive;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app,bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	

	bool CleanUp();

private:

	p2DynArray<Primitive*> primitives;


	
	SDL_WindowFlags window_flags;
	SDL_GLContext gl_context;
	


	bool on = false;
	bool done = false;


	//Window Bools

	bool show_demo_window;
	bool show_another_window;
	bool exit_engine_window;



};
