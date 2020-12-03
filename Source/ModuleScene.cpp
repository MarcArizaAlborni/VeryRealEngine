#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "Definitions.h"
#include "ModuleRenderer3D.h"
#include "FileSystem.h"
#include "ModuleScene.h"
#include "ModuleCamera3D.h"
#include "ModuleTextureImporter.h"
#include "ModuleEditor.h"
#include "libraries/Glew/include/GL/glew.h"
#include "libraries/SDL/include/SDL_opengl.h"
#include "Primitive.h"
#include "GameObject.h"
#include "ModuleMeshImporter.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ModuleTextureImporter.h"



#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleScene::ModuleScene(Application* app, const char* name, bool start_enabled) : Module(app, "Scene", start_enabled)
{
	ROOT_SCENE_OBJECT = new Game_Object("ROOT SCENE");
	App->geometrymanager->ObjectsOnScene.push_back(ROOT_SCENE_OBJECT);
	ROOT_SCENE_OBJECT->Parent = nullptr;

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
	//THIS MUST ALWAYS BE THE FIRST THING IN THE OBJECT LIST
	//Game_Object* Item = new Game_Object("Scene Object");
	//App->geometrymanager->ObjectsOnScene.push_back(Item);



	App->textureImporter->TextureCheckers = App->textureImporter->LoadTextureImage("Assets/Models/Checkers/checkers.png");

	// BAKER HOUSE FOR DRAW W/TEXTURES ON START

	App->textureImporter->TextureHouse = App->textureImporter->LoadTextureImage("Assets/Models/House/Baker_house.png");
	

	
	


	//This
	//App->meshimporter->LoadFile_Mesh("Assets/Models/House/BakerHouse.fbx");
	//this
	App->meshimporter->LoadFile_Mesh("Assets/Models/Street/Street_environment_V01.FBX");
	//App->meshimporter->LoadFile_Mesh("Assets/Models/Street/Street_environment_V01.FBX");
	//App->meshimporter->LoadFile_Mesh("Assets/Models/Street/Street_environment.FBX");

	
	


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

bool ModuleScene::ResetScene()
{
	App->meshimporter->MeshesOnScene.clear();
	//SHOULD WE DELETE BUFFERS

	return true;
}

bool ModuleScene::LoadScene()
{
	ResetScene();

	return true;
}

void ModuleScene::SaveScene()
{

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
