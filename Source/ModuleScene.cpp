#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleScene.h"
#include "ModuleCamera3D.h"
#include "ModuleTextureImporter.h"
#include "ModuleEditor.h"
#include "libraries/Glew/include/GL/glew.h"
#include "libraries/SDL/include/SDL_opengl.h"
#include "Primitive.h"
#include "ModuleMeshImporter.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ModuleTextureImporter.h"



#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleScene::ModuleScene(Application* app, const char* name, bool start_enabled) : Module(app, "Scene", start_enabled)
{
}

// Destructor
ModuleScene::~ModuleScene()
{}

// Called before render is available
bool ModuleScene::Init()
{
	LOGFIX("Creating Scene context");
	bool ret = true;


	return ret;
}

bool ModuleScene::Start()
{
	App->textureImporter->TextureCheckers = App->textureImporter->LoadTextureImage("Assets/Models/Checkers/checkers.png");

	// BAKER HOUSE FOR DRAW W/TEXTURES ON START

	App->textureImporter->TextureHouse = App->textureImporter->LoadTextureImage("Assets/Models/House/Baker_house.png");
	//App->textureImporter->AddTextureToList(&App->textureImporter->TextureHouse, "Baker House");

	App->meshimporter->LoadMesh("Assets/Models/House/BakerHouse.fbx");
	/*App->meshimporter->LoadFile_Mesh("Assets/Models/House/BakerHouse.fbx");*/
	App->meshimporter->LoadFile_Mesh("Assets/Models/Street/Street environment_V01.FBX");
	/*App->meshimporter->LoadMesh("", true);*/
	App->meshimporter->MeshesOnScene.at(0)->ChildObjects.at(0)->TextureData = App->textureImporter->TextureHouse;
	App->meshimporter->MeshesOnScene.at(0)->ChildObjects.at(1)->TextureData = App->textureImporter->TextureHouse;


	// STREET FOR DRAW W/TEXTURES ON START

	//App->meshimporter->LoadMesh("Assets/Models/Street/Street environment_V01.FBX");

	// GWYN FOR DRAW W/TEXTURES ON START

	//App->textureImporter->GwynAccessories = App->textureImporter->LoadTextureImage("Assets/Textures/Gwyn/Accessories.dds");
	//App->textureImporter->GwynClothes = App->textureImporter->LoadTextureImage("Assets/Textures/Gwyn/Clothing.dds");
	//App->textureImporter->GwynClothesB = App->textureImporter->LoadTextureImage("Assets/Textures/Gwyn/ClothingB.dds");
	//App->textureImporter->GwynClothesC = App->textureImporter->LoadTextureImage("Assets/Textures/Gwyn/ClothingC.dds");
	//App->textureImporter->GwynCrown = App->textureImporter->LoadTextureImage("Assets/Textures/Gwyn/Crown.dds");
	//App->textureImporter->GwynHair = App->textureImporter->LoadTextureImage("Assets/Textures/Gwyn/Hair.dds");
	//App->textureImporter->GwynMantle = App->textureImporter->LoadTextureImage("Assets/Textures/Gwyn/Mantle.dds");
	//App->textureImporter->GwynSkin = App->textureImporter->LoadTextureImage("Assets/Textures/Gwyn/Skin.dds");
	//App->textureImporter->GwynSword = App->textureImporter->LoadTextureImage("Assets/Textures/Gwyn/Sword.dds");

	//App->meshimporter->LoadMesh("Assets/Models/Gwyn.fbx");
	////-1 TO THE POSITION OF THE ITEM IN LIST
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(0)->TextureData = App->textureImporter->GwynSword;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(1)->TextureData = App->textureImporter->GwynAccessories;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(2)->TextureData = App->textureImporter->GwynSword;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(3)->TextureData = App->textureImporter->GwynClothesB;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(4)->TextureData = App->textureImporter->GwynClothes;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(5)->TextureData = App->textureImporter->GwynAccessories; 
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(6)->TextureData = App->textureImporter->GwynClothesB;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(7)->TextureData = App->textureImporter->GwynClothes;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(8)->TextureData = App->textureImporter->GwynClothes;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(9)->TextureData = App->textureImporter->GwynClothesB;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(10)->TextureData = App->textureImporter->GwynAccessories; 
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(11)->TextureData = App->textureImporter->GwynSkin;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(12)->TextureData = App->textureImporter->GwynAccessories; 
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(13)->TextureData = App->textureImporter->GwynCrown;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(14)->TextureData = App->textureImporter->GwynCrown;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(15)->TextureData = App->textureImporter->GwynClothesC;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(16)->TextureData = App->textureImporter->GwynAccessories;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(17)->TextureData = App->textureImporter->GwynClothesC;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(18)->TextureData = App->textureImporter->GwynClothesB;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(19)->TextureData = App->textureImporter->GwynClothesC;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(20)->TextureData = App->textureImporter->GwynHair;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(21)->TextureData = App->textureImporter->GwynHair;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(22)->TextureData = App->textureImporter->GwynHair;
	//App->meshimporter->MeshesOnScene.at(1)->ChildObjects.at(23)->TextureData = App->textureImporter->GwynHair;



	//App->meshimporter->MeshesOnScene.at(1)->TextureData = App->textureImporter->TextureHouse;
	//App->meshimporter->MeshesOnScene.at(2)->TextureData = App->textureImporter->TextureHousita;
	//App->meshimporter->MeshesOnScene.at(3)->TextureData = App->textureImporter->TextureEarth;


	/*for (int a = 0; a < 10; ++a) {
		std::string value = std::to_string(a);
		const char* value_C = value.c_str();
		LOGFIX(value_C);
	}*/

	return true;
}


// PreUpdate: clear buffer
update_status ModuleScene::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt)
{

	Plane2 p(0, 1, 0, 0);
	p.axis = true;

	if (App->editor->show_grid)
	{
		p.Render();
	}

	return UPDATE_CONTINUE;
}


// PostUpdate present buffer to screen
update_status ModuleScene::PostUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleScene::CleanUp()
{
	LOGFIX("Destroying Scene");


	return true;
}


void ModuleScene::CreateConsolelog(const char file[], int line, const char* format, ...)
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
