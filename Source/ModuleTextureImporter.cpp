#include "Globals.h"
#include "Application.h"
#include "ModuleTextureImporter.h"

#include "libraries/Assimp/Assimp/include/cimport.h"
#include "libraries/Assimp/Assimp/include/scene.h"
#include "libraries/Assimp/Assimp/include/postprocess.h"
#pragma comment (lib, "libraries/Assimp/Assimp/libx86/assimp.lib")
#include "libraries/Glew/include/GL/glew.h"

#include <gl/GLU.h>

#define CHECKERS_WIDTH 64
#define CHECKERS_HEIGHT 64

ModuleTextureImporter::ModuleTextureImporter(Application* app, const char* name, bool start_enabled) : Module(app, "Texture Importer", start_enabled)
{

}

ModuleTextureImporter::~ModuleTextureImporter()
{}

TextureInfo::TextureInfo(uint id, uint w, uint h)
{
	texture_id = id;
	width = w;
	height = h;
}
TextureInfo::TextureInfo(uint id, uint w, uint h, std::string name_)
{
	texture_id = id;
	width = w;
	height = h;
	tex_name = name_;
}

bool ModuleTextureImporter::LoadTextureCheckers()
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

	/*TextureValue = SetUpTexture(checkerImage, CHECKERS_WIDTH, CHECKERS_HEIGHT, GL_RGBA, GL_RGBA, GL_TEXTURE_2D, GL_NEAREST, GL_REPEAT, true);*/
	uint TextureValue = 0;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &TextureValue);
	glBindTexture(GL_TEXTURE_2D, TextureValue);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT,
		0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);

	checkers_texture = new TextureInfo(TextureValue, CHECKERS_WIDTH, CHECKERS_HEIGHT, "Checkers");

	return true;
}

void ModuleTextureImporter::ImportTexture()
{
}

uint ModuleTextureImporter::SetUpTexture(const void* ImageInfo, int TexWidth, int TexHeight, int Border, int intFormat, uint format, uint Target, int FilterTypus, int WrapType)
{
	GLuint Texture_Id;
	std::string FilterType; // GL_NEAREST and GL_LINEAR no implementation for mipmaps yet so these two are the only choices
	std::string TextureType = "2D";

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &Texture_Id);
	glBindTexture(Target, Texture_Id);
	glTexParameteri(Target, GL_TEXTURE_WRAP_S, FilterTypus);
	glTexParameteri(Target, GL_TEXTURE_WRAP_T, FilterTypus);

	if (FilterTypus == GL_LINEAR) {
		FilterType.assign("Linear");
		glTexParameteri(Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	}
	else if (FilterTypus == GL_NEAREST) {
		FilterType.assign("Nearest");
        glTexParameteri(Target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		
	}
	glTexImage2D(Target, 0, intFormat, TexWidth, TexHeight, 0, format, GL_UNSIGNED_BYTE, ImageInfo);
	glBindTexture(Target, 0);
	return Texture_Id;
}


void ModuleTextureImporter::CreateConsolelog(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
	OutputDebugString(tmp_string2);


	App->console->ConsoleLogs.push_back(tmp_string2);
}

