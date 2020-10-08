
#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include <vector>
#include "libraries/ImGUI/imgui.h"

struct GPU_Status {

	char* model_name;
	char* renderer_name;
	char* version;

};

struct CPU_Status {

	int CPU_Count;
	int Cache_size;
	int System_Ram;

};

struct Hardware_Status {

	GPU_Status GPU;
	CPU_Status CPU;

};

class ModuleImGui : public Module
{
public:
	ModuleImGui(Application* app,bool start_enabled = true);
	~ModuleImGui();

	bool Start();
	update_status Update(float dt);
	
	bool CleanUp();

private:

	
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
	void CreateConfigWindow_FileSystem();
	void CreateConfigWindow_Input();
	void CreateConfigWindow_Hardware();
	



	// ---------------About Window---------------
	void CreateAboutWindow();

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

	std::vector<float> fps_log;
	std::vector<float> ms_log;

	Hardware_Status HardwareStat;


};
