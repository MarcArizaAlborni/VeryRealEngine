#include "Globals.h"
#include "Application.h"
#include "ModuleTextureImporter.h"

#include "libraries/Assimp/Assimp/include/cimport.h"
#include "libraries/Assimp/Assimp/include/scene.h"
#include "libraries/Assimp/Assimp/include/postprocess.h"
#pragma comment (lib, "libraries/Assimp/Assimp/libx86/assimp.lib")
#include "libraries/Glew/include/GL/glew.h"

#include <gl/GLU.h>

#include "libraries/DevIL/include/il.h"
#include "libraries/DevIL/include/ilu.h"
#include "libraries/DevIL/include/ilut.h"

// Include DevIL libs
#pragma comment (lib, "libraries/DevIL/libx86/DevIL.lib")
#pragma comment (lib, "libraries/DevIL/libx86/ILU.lib")
#pragma comment (lib, "libraries/DevIL/libx86/ILUT.lib")

#define CHECKERS_WIDTH 64
#define CHECKERS_HEIGHT 64

ModuleTextureImporter::ModuleTextureImporter(Application* app, const char* name, bool start_enabled) : Module(app, "Texture Importer", start_enabled)
{

}

ModuleTextureImporter::~ModuleTextureImporter()
{}


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

	return true;
}

TextureInfo ModuleTextureImporter::LoadTexture(const char* path) const
{

	ilInit();
	iluInit();
	ilutInit();

	TextureInfo id_texture;
	uint id_img = 0;

	if (path != nullptr)
	{
		ilGenImages(1, (ILuint*)&id_img);
		ilBindImage(id_img);

		if (ilLoadImage(path))
		{
			ILinfo ImgInfo;
			iluGetImageInfo(&ImgInfo);

			if (ImgInfo.Origin == IL_ORIGIN_UPPER_LEFT)
				iluFlipImage();

			if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
			{
				//Create Texture
				id_texture.id = CreateTexture(ilGetData(), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_FORMAT));
			}	
		}
	}
	
	return id_texture;
	
}

uint ModuleTextureImporter::CreateTexture(const void* text, uint width, uint height, int format, uint format2) const
{
	uint id_texture = 0;

	glGenTextures(1, (GLuint*)&id_texture);
	glBindTexture(GL_TEXTURE_2D, id_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//Enabling anisotropic filtering
	if (glewIsSupported("GL_EXT_texture_filter_anisotropic"))
	{
		float max_anisotropy;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, text);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Unbind Texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return id_texture;
}

void ModuleTextureImporter::ImportTexture()
{
	
}

uint ModuleTextureImporter::SetUpTexture(const void* ImageInfo, int TexWidth, int TexHeight, int Border, int intFormat, uint format, uint Target, int FilterTypus, int WrapType)
{
	//GLuint Texture_Id;
	//std::string FilterType; // GL_NEAREST and GL_LINEAR no implementation for mipmaps yet so these two are the only choices
	//std::string TextureType = "2D";

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glGenTextures(1, &Texture_Id);
	//glBindTexture(Target, Texture_Id);
	//glTexParameteri(Target, GL_TEXTURE_WRAP_S, FilterTypus);
	//glTexParameteri(Target, GL_TEXTURE_WRAP_T, FilterTypus);

	//if (FilterTypus == GL_LINEAR) {
	//	FilterType.assign("Linear");
	//	glTexParameteri(Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//}
	//else if (FilterTypus == GL_NEAREST) {
	//	FilterType.assign("Nearest");
 //       glTexParameteri(Target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 //       glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//	
	//}
	//glTexImage2D(Target, 0, intFormat, TexWidth, TexHeight, 0, format, GL_UNSIGNED_BYTE, ImageInfo);
	//glBindTexture(Target, 0);
	//return Texture_Id;
	return 1;
}

void ModuleTextureImporter::freeTexture()
{
	//Delete texture
	if (mTextureID != 0)
	{
		glDeleteTextures(1, &mTextureID);
		mTextureID = 0;
	}

	mTextureWidth = 0;
	mTextureHeight = 0;
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

