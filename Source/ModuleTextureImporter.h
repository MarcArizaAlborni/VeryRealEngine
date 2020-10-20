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

	uint LoadTextureCheckers();
	void ImportTexture();
	uint SetUpTexture(const void* ImageInfo, int TexWidth, int TexHeight,int Border, int intFormat, uint format, uint Target, int FilterTypus, int WrapType);


	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);

};

#endif