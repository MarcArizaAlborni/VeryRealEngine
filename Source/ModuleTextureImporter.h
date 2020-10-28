#pragma once
#ifndef __ModuleTextureImporters_H__
#define __ModuleTextureImporters_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "libraries/Glew/include/GL/glew.h"


class ModuleTextureImporter : public Module
{
public:
	ModuleTextureImporter(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleTextureImporter();

	bool LoadTextureCheckers();
	
	bool LoadTexture(const char* path);
	bool TextureBuffersLoad(GLuint* pixels, GLuint width, GLuint height);
	void ImportTexture();
	uint SetUpTexture(const void* ImageInfo, int TexWidth, int TexHeight,int Border, int intFormat, uint format, uint Target, int FilterTypus, int WrapType);
	void freeTexture();


	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);

public:

	//Texture name
	GLuint mTextureID;

	//Texture dimensions
	GLuint mTextureWidth;
	GLuint mTextureHeight;

};

#endif