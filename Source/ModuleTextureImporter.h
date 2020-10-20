#pragma once
#ifndef __ModuleTextureImporters_H__
#define __ModuleTextureImporters_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class ModuleTextureImporter : public Module
{
public:
	ModuleTextureImporter(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleTextureImporter();

	bool LoadTexturesCheckers();

};

#endif