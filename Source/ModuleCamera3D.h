#pragma once
#ifndef __ModuleCamera3D_H__
#define __ModuleCamera3D_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class Game_Time;
class Component_Camera;

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Load();
	update_status Save() { return UPDATE_CONTINUE; };
	update_status Update(float dt);
	bool CleanUp();

	void Look(const vec3& Position, const vec3& Reference, bool RotateAroundReference = false);
	void LookAt(const vec3& Spot);
	void Move(const vec3& Movement);
	void Zoom(float dt);

	void CenterToObject(Game_Object* object);
	void Orbit();

	//Settings
	Component_Camera* GetSceneCamera() const;
	Component_Camera* scene_camera = nullptr;

	bool reset_camera = false;

	//------------ CONSOLE STUFF

};

#endif