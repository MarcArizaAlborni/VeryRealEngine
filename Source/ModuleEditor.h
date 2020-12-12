#pragma once
#ifndef __ModuleEditor_H__
#define __ModuleEditor_H__
#include "Module.h"

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
class ImportSettings;
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

	//------------------ Main Docking--------------
	bool MainWindow(char* id, bool dock = true, ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None);

	// ---------------About Window---------------
	void CreateAboutWindow();

	
	bool done = false;

	//Window Bools
	bool show_demo_window;
	bool show_main_dockSpace = true;

	// Window Manager Bools
	bool OnInit;

	ImVec4 clear_color;


public:

	// MAIN MENU BAR--------------------------------------------------------------------------------
	// ------------------Main Bar------------------
	void CreateMainMenuBar();
	void CreateMainMenuBar_File();
	void CreateInsertPrimitivesWindow();
	void CreateMainMenuBar_Edit();
	void CreateMainMenuBar_View();
	void CreateMainMenuBar_Help();
	

	void CreateBar_Play();

	//Main Menu Bar Bools
	bool show_config_window;

	bool show_about_window;

	bool show_console_window;

	bool show_resources_window;

	bool show_hierarchy_window;

	bool show_inspector_window;

	bool show_popup_want_close;
	bool show_popup_want_close2;

	bool delete_object;

	//Editor Play
	bool show_play_window;
	bool show_config_window_mode;

	bool editor_mode;
	bool play_mode;
	bool pause_mode;

	bool drawplane;
	bool drawcube;
	bool drawpyramid;
	bool drawcylinder;
	bool drawsphere;

	//Drag Drop

	

	
	Game_Object* DragedItem=nullptr;

	// CONFIG---------------------------------------------------------------------------------

	Hardware_Status HardwareStat;

	// ---------------Config Window---------------
	void CreateConfigWindow();
	void CreateConfigWindow_Options();
	void CreateConfigWindow_Application();
	void CreateConfigWindow_Window();
	void CreateConfigWindow_FileSystem();
	void CreateConfigWindow_Input();
	void CreateConfigWindow_Hardware();
	void CreateConfigWindow_ImportSettings();
	void GetHardwareStatus();
	void CreateConfigWindow_Resource();
	void CreateTextureVisualizer();

	bool vSync = true;

	float brightness;

	bool active_window;
	bool active_fullscreen;
	bool active_Resizable;
	bool active_Borderless;
	bool active_Full_Desktop;

	bool show_grid;
	bool show_ui;

	//Imports

	ImportSettings* Importer_Settings;

	//texture visualizer window
	bool VisualizeTextureWindow = false;
	TextureInfo ToVisualizeTexture;

	// CONSOLE--------------------------------------------------------------------------------

	// ---------------Console Window---------------
	void CreateConsoleWindow();

	///---------------CONSOLE STUFF-------------

	
	std::vector<std::string> ConsoleLogs_List;
	int LogsAmount;

	Timer scene_timer;

	bool guizmos = false;

	//SCENE STUFF

	void LoadScene(std::string SceneFileName);
	void SaveScene();
	Scene_Manager* SceneElement = nullptr;
	void SaveGameObjectsChilds(Scene_Manager Scene, Game_Object* Object, int* iterator);
	void LoadGameObject(Scene_Manager Scene);

private:

		void ItChildrenObjTextCount(Game_Object* Object,TextureInfo* Text);
		void ItChildrenObjMeshCount(Game_Object* Object, MeshInfo* Mesh);
		int AmountOfUsesTexture;
		int AmountOfUsesMesh;
   
};

#endif