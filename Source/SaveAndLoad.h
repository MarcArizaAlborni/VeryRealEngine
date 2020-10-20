#pragma once
#ifndef __ModuleSaveLoad_H__
#define __ModuleSaveLoad_H__
#include "Module.h"
#include "Globals.h"
#include <iomanip>
#include <fstream>
#include "libraries/json/json.hpp"


using json = nlohmann::json;

class LoadSaveMod : public Module
{
public:

	LoadSaveMod(Application* app, const char* name = "null", bool start_enabled = true);
	~LoadSaveMod();

	bool Init();

	bool CleanUp();

	
	bool Save(json& obj, const char* file) ;
	json Load(const char* file) ;
	
	void LoadFromFile(json& item);
	void SaveintoFileConfig();
	

public:

	
	std::string SaveFileName;

	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
	




	
};

#endif