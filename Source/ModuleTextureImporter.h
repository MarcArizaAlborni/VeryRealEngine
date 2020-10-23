#pragma once
#ifndef __ModuleTextureImporters_H__
#define __ModuleTextureImporters_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include <string>

class TextureInfo
{
public:
	TextureInfo(uint id, uint w, uint h); // Checker constructor
	TextureInfo(uint id, uint w, uint h, std::string name_); // Path text constructor

	uint texture_id;
	uint width;
	uint height;
	std::string tex_name = "";
	std::string tex_path = "";
};

class ModuleTextureImporter : public Module
{
public:
	ModuleTextureImporter(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleTextureImporter();

	bool LoadTextureCheckers();
	void ImportTexture();
	uint SetUpTexture(const void* ImageInfo, int TexWidth, int TexHeight,int Border, int intFormat, uint format, uint Target, int FilterTypus, int WrapType);

public:
	TextureInfo* checkers_texture = nullptr;


	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);

};

#endif