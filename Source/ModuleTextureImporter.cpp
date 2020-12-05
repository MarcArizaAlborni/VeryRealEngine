#include "Globals.h"
#include "Application.h"
#include "ModuleTextureImporter.h"
#include "ModuleMeshImporter.h"
#include "ModuleEditor.h"
#include "FileSystem.h"

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


bool ModuleTextureImporter::Start()
{
	ilInit();
	ilutInit();
	iluInit();
	return true;
}



TextureInfo ModuleTextureImporter::LoadTextureImage(const char* path)
{
	//LOGFIX("Importing Texture %s...", path);
	TextureInfo InfoTexture;
	TextureInfo* TextureInformation = new TextureInfo();
	ILuint temp_id = 0;

	if (path != nullptr)
	{
		ilGenImages(1, &temp_id);
		ilBindImage(temp_id);

		if (ilLoadImage(path))
		{
			ILinfo ImgInfo;
			iluGetImageInfo(&ImgInfo);

			TextureInformation->width = ImgInfo.Width;
			TextureInformation->height = ImgInfo.Height;
			TextureInformation->texture_path = path;

			if (ImgInfo.Origin == IL_ORIGIN_UPPER_LEFT)
				iluFlipImage();

			if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
			{
				//Create Texture
				TextureInformation->texture_id = SetUpTexture(ilGetData(), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_FORMAT));
			}	

			///////////////Adding to list of textures loaded
			bool is_loaded = false;
			TextureInfo* TexturePath ;
			if (App->meshimporter->LoadedTexturesList.size() > 0) {
				std::vector<TextureInfo*>::iterator TextIt = App->meshimporter->LoadedTexturesList.begin();
				for (int i = 0; i < App->meshimporter->LoadedTexturesList.size(); ++i) {

					TexturePath = *TextIt;


					if (TexturePath->texture_path.compare(TextureInformation->texture_path) == 0) {
						is_loaded = true;
						i = App->meshimporter->LoadedTexturesList.size();
					}
					else {
						++TextIt;
					}


					
				}
			}
			if (is_loaded == false) {

				App->meshimporter->LoadedTexturesList.push_back(TextureInformation);
			}

			/////////////////////////
		}
	}
	
	InfoTexture.height = TextureInformation->height;
	InfoTexture.width = TextureInformation->width;
	InfoTexture.texture_id = TextureInformation->texture_id;
	InfoTexture.texture_name = TextureInformation->texture_name;
	InfoTexture.texture_path = TextureInformation->texture_path;

	return InfoTexture;
}

TextureInfo ModuleTextureImporter::CreateTexturesNodeMap(NodeMap Node, const aiScene* scene, const char* file_path)
{
	TextureInfo Texture;

	std::string dir_path;

	std::string extension;
	std::string file_name;
	
	aiMaterial* material = scene->mMaterials[Node.MaterialPositionArray];

	

	std::string texName;
	std::string CompletePath;
	std::string	texExtension;

	aiColor4D colorMat = { 0,0,0,0 };


	



	aiString tex_path;

	if (Node.MaterialPath != "") {
		std::string Texture_Path = Node.MaterialPath;

		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &tex_path) == AI_SUCCESS)
		{
			std::string file = App->filemanager->GetFileAndExtension(tex_path.C_Str());
			App->filemanager->SplitFilePath(Texture_Path.c_str(), nullptr, &texName, &texExtension);

			CompletePath = "Assets/Textures/" + texName + "." + texExtension;


			Texture = App->textureImporter->LoadTextureImage(CompletePath.c_str());
			Texture.texture_path = CompletePath;
			Texture.texture_name = texName;
			

			
			
		}
	}
	
	if (material->Get(AI_MATKEY_COLOR_DIFFUSE, colorMat) == aiReturn_SUCCESS)
	{
		Texture.Colour.r = colorMat.r;
		Texture.Colour.g = colorMat.g;
		Texture.Colour.b = colorMat.b;
		Texture.Colour.a = colorMat.a;

	}
	

	return Texture;
}



uint ModuleTextureImporter::SetUpTexture(const void* texture, uint width, uint height, int format, uint format2)
{
	
	GLuint id_texture = 0;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &id_texture);
	glBindTexture(GL_TEXTURE_2D, id_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, texture);
	

	
	glBindTexture(GL_TEXTURE_2D, 0);

	return id_texture;
}

int ModuleTextureImporter::CheckTextureExistance(std::string TexturePath)
{
	int PositionFOUND=-1;

	std::vector<TextureInfo*>::iterator It = App->textureImporter->Textures_Resource_List.begin();

	for (int size = 0; size < App->textureImporter->Textures_Resource_List.size(); ++size) {


		TextureInfo* Texture = *It;

		if (Texture->texture_path == TexturePath) {
			return size;
		}
		++It;
	}

	

	return PositionFOUND;
}

bool ModuleTextureImporter::LoadTexture(const char* path)
{

	ilInit();
	iluInit();
	ilutInit();
	//Texture loading success
	bool textureLoaded = false;

	//Generate and set current image ID
	ILuint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	std::string PathStr;
	PathStr = path;
	

	//Load image
	ILboolean success = ilLoadImage(PathStr.c_str());

	//Image loaded successfully
	if (success == IL_TRUE)
	{
		//Convert image to RGBA
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		if (success == IL_TRUE)
		{
			//Create texture from file pixels
			textureLoaded = TextureBuffersLoad((GLuint*)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
		}

		//Delete file from memory
		ilDeleteImages(1, &imgID);
	}

	//Report error
	if (!textureLoaded)
	{
		printf("Unable to load %s\n", PathStr.c_str());
	}

	return textureLoaded;
	
}

bool ModuleTextureImporter::TextureBuffersLoad(GLuint* pixels, GLuint width, GLuint height)
{
	//Free texture if it exists
	freeTexture();

	//Get texture dimensions
	mTextureWidth = width;
	mTextureHeight = height;

	//Generate texture ID
	glGenTextures(1, &mTextureID);

	//Bind texture ID
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	//Generate texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//Unbind texture
	glBindTexture(GL_TEXTURE_2D, NULL);

	//Check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error loading texture from %p pixels! %s\n", pixels, gluErrorString(error));
		return false;
	}

	return true;
	
}


void ModuleTextureImporter::ImportTexture()
{
	
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

TextureInfo ModuleTextureImporter::LoadCheckersTexture()
{
	GLubyte checkImage[64][64][4];


	for (int i = 0; i < CHECKERS_WIDTH; i++)
	{
		for (int j = 0; j < CHECKERS_HEIGHT; j++)
		{
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;

			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &TextureCheckers.texture_id);
	glBindTexture(GL_TEXTURE_2D, TextureCheckers.texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

	glBindTexture(GL_TEXTURE_2D, 0);


	return TextureCheckers;
}

void ModuleTextureImporter::AddTextureToList(TextureInfo* texture,const char* name)
{
	App->textureImporter->TextureHouse.texture_name = name;
	App->textureImporter->AvailableTextures.push_back(&App->textureImporter->TextureHouse);
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


	App->editor->ConsoleLogs.push_back(tmp_string2);
}

