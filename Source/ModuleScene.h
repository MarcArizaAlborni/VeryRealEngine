#ifndef __ModuleScene_H__
#define __ModuleScene_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#include "JScene.h"
class Game_Object;

class ModuleScene : public Module
{
public:

	ModuleScene(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleScene();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	bool ResetScene();
	void SaveScene();
	/*bool SaveGameObject(JScene go_scene, GameObject* obj, int* i);*/
	bool LoadScene();
	
	Game_Object* ROOT_SCENE_OBJECT = nullptr;
	Game_Object* scene_camera = nullptr;
public:
	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
};

#endif // __ModuleScene_H__