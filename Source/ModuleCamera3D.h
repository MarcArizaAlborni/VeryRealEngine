#pragma once
#ifndef __ModuleCamera3D_H__
#define __ModuleCamera3D_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"


class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const vec3& Position, const vec3& Reference, bool RotateAroundReference = false);
	void LookAt(const vec3& Spot);
	void Move(const vec3& Movement);

	void CenterToObject(GameObject* object);
	void Orbit();

	float* GetViewMatrix();

private:

	void CalculateViewMatrix();

public:

	vec3 X, Y, Z, Position, Reference;

	float wheelSpeedValue = 0.8f; // sensitivity left click 
	float zoomValue = 0.5f; //sensitivity of the zoom

	bool ResetRotation = false;

private:

	mat4x4 ViewMatrix, ViewMatrixInverse;



	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
};

#endif