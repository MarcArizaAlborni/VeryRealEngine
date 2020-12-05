#ifndef _COMPONENT_CAMERA_H_
#define _COMPONENT_CAMERA_H_

#include "Component.h"
#include "Globals.h"
#include "glmath.h"

#include "libraries/MathGeoLib/include/Geometry/Frustum.h"

class Component_Camera : public Component
{
public:
	Component_Camera(Game_Object* obj);
	~Component_Camera() {};

	void CreateFrustum(const float3* corners, Color color);

	float* GetViewMatrix();
	void CalculateViewMatrix();

	update_status Load();
	update_status Save() { return UPDATE_CONTINUE; };

public:
	vec3 X, Y, Z, Position, Reference;
	float camera_speed = 0.015f;

	float wheelSpeedValue = 0.8f; // sensitivity left click 
	float zoomValue = 0.5f; //sensitivity of the zoom

	bool ResetRotation = false;

private:
	mat4x4 ViewMatrix;
	mat4x4 ViewMatrixInverse;
};

#endif // !_COMPONENT_CAMERA_H_