
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
#include "ModuleGeometryLoader.h"
#include "ModuleCamera3D.h"
#include "ModuleEditor.h"
#include "ModuleTextureImporter.h"
#include "ModuleMeshImporter.h"
#include <vector>
#include "libraries/json/json.hpp"
#include "SaveAndLoad.h"
#include "ModuleHierarchy.h"




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
	LoadSaveMod* LoadSave;
	ModuleGeometryLoader* geometryloader;

	//Windows & Menus
	ModuleEditorMainMenuBar* mainMenubar;
	ModuleEditorConfiguration* configWindow;
	ModuleEditorConsole* console;
	ModuleHierarchyGameObject* hierarchy;

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

	std::vector<float>			ms_log;
	std::vector<float>			fps_log;
	int							max_FPS = 0;

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

	float dt;

	//SAVE & LOAD WITH JOTA SON


	////// FUNCTIONS ///////

	

	


	///// DEFINITIONS  ///////

	
	
	std::string SaveFileName;

};


#endif

