#pragma once


#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include <list>
#include "ModuleImGui.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleEditor.h"

// JOTA-HIJO

#include "libraries/json/json.hpp"
using json = nlohmann::json;

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleImGui* ImGui;
	ModuleEditor* editor;

private:

	std::list<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

	void RequestBrowser(const char* url) const;

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();



	//SAVE & LOAD WITH JOTA SON


	////// FUNCTIONS ///////

	bool LoadSaveFile();
	bool SaveSaveFile();


	///// DEFINITIONS  ///////



	
};


// Class for save and load

class SaveLoad {

public:

	SaveLoad() {};



	bool Save(SaveLoad item, const char* file);

	SaveLoad Load(const char* file);


};