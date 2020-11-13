
#pragma once

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include <list>
#include "ModuleEditorMainMenuBar.h"
#include "ModuleEditorConfiguration.h"
#include "ModuleEditorConsole.h"
#include "ModuleRenderer3D.h"
#include "ModuleGeometryManager.h"
#include "ModuleCamera3D.h"
#include "ModuleEditor.h"
#include "ModuleTextureImporter.h"
#include "ModuleMeshImporter.h"
#include <vector>
#include "libraries/json/json.hpp"
#include "ModuleHierarchy.h"
#include "ModuleInspector.h"
#include "ResourceManager.h"
#include "FileSystem.h"
#include "ComponentCamera.h"



using json = nlohmann::json;

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleEditor* editor;
	ModuleTextureImporter* textureImporter;
	ModuleMeshImporter* meshimporter;
	
	ModuleGeometryManager* geometrymanager;
	ModuleFileSystem* filemanager;
	ComponentCamera* componentcamera;

	//Windows & Menus
	ModuleEditorMainMenuBar* mainMenubar;
	ModuleEditorConfiguration* configWindow;
	ModuleEditorConsole* console;
	ModuleHierarchyGameObject* hierarchy;
	ModuleInspectorGameObject* inspector;
	ResourceManager* resources;

	//SaveLoad* LoadSaveMod;
	
	bool					debug;
	bool					renderPrimitives;


private:

	std::vector<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

	void RequestBrowser(const char* url) const;

	float GetDT();

public:

	Timer					last_sec_frame_time;
	Timer					frame_time;

	std::vector<float>			fps_log;
	std::vector<float>			ms_log;

	uint					frame_count = 0;
	uint					prev_last_sec_frame_count = 0;
	uint					last_sec_frame_count = 0;

	int						capped_ms = -1;
	int						max_framerateCap = 120;
	int						Bars = 100; // Histogram bars

	std::string name;


	int GiveRandomNum_Undefined();
	int GiveRandomNum_Defined(int Max, int Min);

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

	float dt;

	//SAVE & LOAD WITH JOTA SON


	////// FUNCTIONS ///////

	

	


	///// DEFINITIONS  ///////

	
	
	std::string SaveFileName;

	int GenerateRandomIntRange(int first, int last);
	int GenerateRandomInt();
	int GetNumber() const;


};


#endif

