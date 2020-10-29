#pragma once
#ifndef __ModuleTextureImporters_H__
#define __ModuleTextureImporters_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "libraries/Glew/include/GL/glew.h"

struct TextureInfo {

	
	uint width=0;
	uint height = 0;
	uint texture_id = 0;
	std::string texture_name="";


};

class ModuleTextureImporter : public Module
{
public:
	ModuleTextureImporter(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleTextureImporter();

	bool Start();
	TextureInfo LoadTextureImage(const char* path);
	uint SetUpTexture(const void* texture, uint width, uint height, int format, uint format2);
	
	bool LoadTexture(const char* path);
	bool TextureBuffersLoad(GLuint* pixels, GLuint width, GLuint height);
	void ImportTexture();
	uint SetUpTexture(const void* ImageInfo, int TexWidth, int TexHeight,int Border, int intFormat, uint format, uint Target, int FilterTypus, int WrapType);
	void freeTexture();
	TextureInfo LoadCheckersTexture();

	void AddTextureToList(TextureInfo* texture,const char* name);

	std::vector<TextureInfo*> AvailableTextures;

	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);

public:
	TextureInfo TextureCheckers;
	TextureInfo TextureEarth;
	TextureInfo TextureHouse;
	TextureInfo TextureHousita;

	//Texture name
	GLuint mTextureID=0;

	//Texture dimensions
	GLuint mTextureWidth=0;
	GLuint mTextureHeight=0;

};

#endif