#include "Application.h"
#include "ComponentCamera.h"
#include "Component.h"
#include "GameObject.h"
#include "ModuleCamera3D.h"
#include "ComponentTransform.h"
#include "ModuleWindow.h"
#include "ModuleScene.h"
#include "Globals.h"
#include "libraries/MathGeoLib/include/Math/MathFunc.h"


Component_Camera::Component_Camera(Game_Object* obj) : Component(obj)
{
	type = Component_Types::Camera;

	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);

	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetPos(float3(0, 10, 0));
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);
	frustum.SetViewPlaneDistances(0.1f, 100.0f);
	frustum.SetPerspective(1.0f, 1.0f);
	SetFOV(50.0f);

	frustum_corners = new vec[8];


	
}

// Frustum
void Component_Camera::DrawFrustum(const float3* corners, Color color)
{
	if (camera_drawn)
	{
		glColor4f(color.r, color.g, color.b, color.a);

		Component_Transform* Cam_Trans = (Component_Transform*)App->scene->object_scene_camera->GetComponent(Component_Types::Transform);

		glPushMatrix();
		glMultMatrixf((GLfloat*)&Cam_Trans->Global_Matrix.Transposed());

		glBegin(GL_LINES);

		glVertex3fv((GLfloat*)&corners[1]);
		glVertex3fv((GLfloat*)&corners[5]);
		glVertex3fv((GLfloat*)&corners[7]);
		glVertex3fv((GLfloat*)&corners[3]);

		glVertex3fv((GLfloat*)&corners[4]);
		glVertex3fv((GLfloat*)&corners[0]);
		glVertex3fv((GLfloat*)&corners[2]);
		glVertex3fv((GLfloat*)&corners[6]);

		glVertex3fv((GLfloat*)&corners[5]);
		glVertex3fv((GLfloat*)&corners[4]);
		glVertex3fv((GLfloat*)&corners[6]);
		glVertex3fv((GLfloat*)&corners[7]);

		glVertex3fv((GLfloat*)&corners[0]);
		glVertex3fv((GLfloat*)&corners[1]);
		glVertex3fv((GLfloat*)&corners[3]);
		glVertex3fv((GLfloat*)&corners[2]);

		glVertex3fv((GLfloat*)&corners[1]);
		glVertex3fv((GLfloat*)&corners[3]);
		glVertex3fv((GLfloat*)&corners[0]);
		glVertex3fv((GLfloat*)&corners[2]);

		glVertex3fv((GLfloat*)&corners[5]);
		glVertex3fv((GLfloat*)&corners[7]);
		glVertex3fv((GLfloat*)&corners[4]);
		glVertex3fv((GLfloat*)&corners[6]);

		glEnd();

		glPopMatrix();

		glColor4f(1.0, 1.0, 1.0, 1.0);
	}
}

void Component_Camera::FrustumUpdateTransform(const float4x4& global)
{
	frustum.SetFront(global.WorldZ());
	frustum.SetUp(global.WorldY());

	float3 position = float3::zero;
	float3 scale = float3::one;
	Quat   rotation = Quat::identity;

	global.Decompose(position, rotation, scale);

	frustum.SetPos(position);
}

// Frustum settings
float Component_Camera::GetFOV()
{
	return frustum.VerticalFov() * RADTODEG;
}

float Component_Camera::GetAspectRatio()
{
	return frustum.AspectRatio();
}

void Component_Camera::SetFOV(float fov)
{
	frustum.SetVerticalFovAndAspectRatio(fov * DEGTORAD, ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT));
}

void Component_Camera::SetAspectRatio(float aspectratio) {

	frustum.SetHorizontalFovAndAspectRatio(frustum.HorizontalFov(), aspectratio);
}

float Component_Camera::GetNearPlane()
{
	return frustum.NearPlaneDistance();
}

void Component_Camera::SetNearPlane(float distance)
{
	frustum.SetViewPlaneDistances(distance, frustum.FarPlaneDistance());
}

float Component_Camera::GetFarPlane()
{
	return frustum.FarPlaneDistance();
}

void Component_Camera::SetFarPlane(float distance)
{
	frustum.SetViewPlaneDistances(frustum.NearPlaneDistance(), distance);
}

vec* Component_Camera::GetFrustumPoints()
{
	frustum.GetCornerPoints(frustum_corners);

	return frustum_corners;
}

//Camera Settings
float* Component_Camera::GetViewMatrix()
{
	return &ViewMatrix;
}

void Component_Camera::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}

// Camera settings
float Component_Camera::GetCameraSpeed()
{
	return camera_speed;
}

void Component_Camera::SetCameraSpeed(float speed)
{
	camera_speed = speed;
}

float Component_Camera::GetWheelSpeed()
{
	return wheelSpeedValue;
}

void Component_Camera::SetWheelSpeed(float speed)
{
	wheelSpeedValue = speed;
}

float Component_Camera::GetZoomValue()
{
	return zoomValue;
}

void Component_Camera::SetZoomValue(float zoom)
{
	zoomValue = zoom;
}


update_status Component_Camera::Load()
{

	return UPDATE_CONTINUE;
}
