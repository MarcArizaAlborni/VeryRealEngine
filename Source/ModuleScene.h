#ifndef __ModuleScene_H__
#define __ModuleScene_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#include "JScene.h"

#include "libraries/imGuizmo/ImGuizmo.h"

class Game_Object;
class Component;
class Component_Transform;
class Component_Camera;

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

	bool camera_culling = false;
	
	Game_Object* ROOT_SCENE_OBJECT = nullptr;
	Game_Object* object_scene_camera = nullptr;

	//Guizmos
	void GuizmoDrawn();

	ImGuizmo::OPERATION gizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
	ImGuizmo::MODE gizmoMode = ImGuizmo::MODE::WORLD;

private:
	Game_Object* LookForSelectedChild(Game_Object* obj);

public:
	//------------ CONSOLE STUFF

};

#endif // __ModuleScene_H__