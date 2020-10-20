#include "Globals.h"
#include "Application.h"
#include "ModuleTextureImporter.h"

#include "libraries/Assimp/Assimp/include/cimport.h"
#include "libraries/Assimp/Assimp/include/scene.h"
#include "libraries/Assimp/Assimp/include/postprocess.h"
#pragma comment (lib, "libraries/Assimp/Assimp/libx86/assimp.lib")

#include <gl/GLU.h>

#define CHECKERS_WIDTH 64
#define CHECKERS_HEIGHT 64

ModuleTextureImporter::ModuleTextureImporter(Application* app, const char* name, bool start_enabled) : Module(app, "Texture Importer", start_enabled)
{

}

ModuleTextureImporter::~ModuleTextureImporter()
{}

bool LoadTexturesCheckers()
{
	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	for (int i = 0; i < CHECKERS_HEIGHT; i++) {
		for (int j = 0; j < CHECKERS_WIDTH; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkerImage[i][j][0] = (GLubyte)c;
			checkerImage[i][j][1] = (GLubyte)c;
			checkerImage[i][j][2] = (GLubyte)c;
			checkerImage[i][j][3] = (GLubyte)255;
		}
	}

	return true;
}

