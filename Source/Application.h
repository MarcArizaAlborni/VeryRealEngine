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
#include "ModuleMeshImporter.h"
#include <vector>
#include "libraries/json/json.hpp"

#include "SaveAndLoad.h"




using json = nlohmann::json;



class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleImGui* ImGuiMod;
	ModuleEditor* editor;
	ModuleMeshImporter* meshimporter;
	LoadSaveMod* LoadSave;
	//SaveLoad* LoadSaveMod;
	

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
	uint GetFramerateLimit() const;
	void SetFramerateLimit(uint max_framerate);

	float GetDT();

public:

	std::vector<float>	ms_log;
	std::vector<float>	fps_log;

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

	int		capped_ms; 

	float dt;

	//SAVE & LOAD WITH JOTA SON


	////// FUNCTIONS ///////

	

	


	///// DEFINITIONS  ///////

	
	
	std::string SaveFileName;

};




