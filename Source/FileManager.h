#pragma once
#ifndef __ModuleFileMana_H__
#define __ModuleFileMana_H__
#include "Module.h"
#include "Globals.h"
#include <iomanip>
#include <fstream>

struct aiScene;

struct SavedFiles {

	const aiScene* Information;
	bool is_loaded = false;
	int id_File;


};
class ModuleFileManager : public Module
{
public:

	ModuleFileManager(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleFileManager();

	bool Init();

	bool CleanUp();

	update_status Update(float dt);

	std::vector<GameObject*>ImportedFilesList;
	//std::vector<const aiScene*>ImportedFilesList;
	
	void StoreImportedFile(char* filepath);

	

public:

	
	

	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
	




	
};

#endif