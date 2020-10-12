#pragma once
#include "Module.h"
#include "Globals.h"
#include <iomanip>
#include <fstream>
#include "libraries/json/json.hpp"


using json = nlohmann::json;

class LoadSaveMod : public Module
{
public:

	LoadSaveMod(Application* app, bool start_enabled = true);
	~LoadSaveMod();

	bool Init();

	bool CleanUp();

	
	bool Save(json& obj, const char* file) ;
	json Load(const char* file) ;
	
	void LoadFromFile(json& item);
	void SaveintoFileConfig();
	

public:

	
	std::string SaveFileName;
	




	
};