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
class ModuleFileSystem : public Module
{
public:

	ModuleFileSystem(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleFileSystem();

public:

	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
};

#endif