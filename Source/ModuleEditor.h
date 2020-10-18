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
	bool isActive_3D;
	bool isActive_AVX2;
	bool isActive_AVX;
	bool isActive_AltiVec;
	bool isActive_MMX;
	bool isActive_RDTSC;
	bool isActive_SSE;
	bool isActive_SSE2;
	bool isActive_SSE3;
	bool isActive_SSE41;
	bool isActive_SSE42;

};

struct Hardware_Status {

	GPU_Status GPU;
	CPU_Status CPU;
	

};


class Class1;

class ModuleEditor : public Module
{
public:

	ModuleEditor(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleEditor();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();


	Hardware_Status HardwareStat;

private:

	SDL_WindowFlags window_flags;
	SDL_GLContext gl_context;

	//Window Bools
	// ------------------Main Bar------------------
	void CreateMainMenuBar();
	void CreateMainMenuBar_File();
	void CreateInsertPrimitivesWindow();
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

	// ---------------Console Window---------------
	void CreateConsoleWindow();

	// ---------------About Window---------------
	void CreateAboutWindow();

	bool vSync = true;
	bool done = false;

	//Window Bools
	bool show_demo_window;
	bool show_configuration_window;

	float brightness;

	bool active_window;
	bool active_fullscreen;
	bool active_Resizable;
	bool active_Borderless;
	bool active_Full_Desktop;

	bool show_config_window;

	bool show_about_window;

	bool show_console_window;

	bool drawline;
	bool drawplane;
	bool drawcube;
	bool drawpyramid;
	bool drawcylinder;
	bool drawsphere;

	// Window Manager Bools
	bool OnInit;

	ImVec4 clear_color;


public:

	///---------------HARDWARE STUFF-------------
	
	 void GetHardwareStatus();

	///---------------CONSOLE STUFF-------------

	std::list<char*> ConsoleLogs;
	int LogsAmount;

   #define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);

	void CallLOG(char* text);

   
};