#pragma once
#ifndef __ModuleTextureImporters_H__
#define __ModuleTextureImporters_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "libraries/Glew/include/GL/glew.h"

struct NodeMap;
struct aiScene;
struct aiMaterial;
struct TextureInfo {

	
	uint width=0; // width of the texture
	uint height = 0; // height of the texture
	uint texture_id = 0; // id of the texture in opengl
	std::string texture_name=""; // name of the texture
	std::string texture_path = ""; // path to the texture file
	Color Colour;

};

class ModuleTextureImporter : public Module
{
public:
	ModuleTextureImporter(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleTextureImporter();

	bool Start();
	TextureInfo LoadTextureImage(const char* path);
	TextureInfo CreateTexturesNodeMap(NodeMap Node,const aiScene* scene,const char* file_path);
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
	//Textures
	TextureInfo TextureCheckers;
	TextureInfo TextureEarth;
	TextureInfo TextureHouse;
	TextureInfo TextureHousita;
	
	
	TextureInfo GwynAccessories;
	TextureInfo GwynClothes;
	TextureInfo GwynClothesB;
	TextureInfo GwynClothesC;
	TextureInfo GwynCrown;
	TextureInfo GwynHair;
	TextureInfo GwynMantle;
	TextureInfo GwynSkin;
	TextureInfo GwynSword;

	//Icons
	TextureInfo DrawIconHierarchyOpen;
	TextureInfo DrawIconHierarchyClosed;
	TextureInfo DrawTrashCanIcon;

	TextureInfo DrawTickIcon;
	TextureInfo DrawPlayIcon;
	TextureInfo DrawPauseIcon;
	TextureInfo DrawStopIcon;
	TextureInfo DrawResumeIcon;

	
	//Resources
	TextureInfo MeshIcon;
	TextureInfo TextureIcon;
	TextureInfo FolderIcon;
	TextureInfo BackIcon;
	TextureInfo RemoveFolderIcon;
	TextureInfo AddFolderIcon;
	TextureInfo RenameFolderIcon;

	//Images Imgui
	TextureInfo cat_crying;
	//Texture name
	GLuint mTextureID=0;

	//Texture dimensions
	GLuint mTextureWidth=0;
	GLuint mTextureHeight=0;



	std::vector<TextureInfo*> Textures_Resource_List;

};

#endif