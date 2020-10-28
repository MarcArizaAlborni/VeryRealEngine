#pragma once
#ifndef __ModuleTextureImporter_H__
#define __ModuleTextureImporter_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "libraries/Glew/include/GL/glew.h"

struct TextureInfo
{
	uint id;
	uint width;
	uint height;
	std::string path;
};

class ModuleTextureImporter : public Module
{
public:
	ModuleTextureImporter(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleTextureImporter();

	bool LoadTextureCheckers();
	
	TextureInfo LoadTexture(const char* path) const;
	uint CreateTexture(const void* texture, uint width, uint height, int format, uint format2) const;
	void ImportTexture();
	uint SetUpTexture(const void* ImageInfo, int TexWidth, int TexHeight,int Border, int intFormat, uint format, uint Target, int FilterTypus, int WrapType);
	void freeTexture();


	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);

public:

	TextureInfo new_texture;
	//Texture name
	GLuint mTextureID;

	//Texture dimensions
	GLuint mTextureWidth;
	GLuint mTextureHeight;

};

#endif