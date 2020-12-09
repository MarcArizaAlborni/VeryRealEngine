#include "Application.h"
#include "ComponentCamera.h"
#include "Component.h"
#include "ModuleWindow.h"
#include "Globals.h"


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

void Component_Camera::DrawFrustum(const float3* corners, Color color)
{
	glColor4f(color.r, color.g, color.b, color.a);
	
	glBegin(GL_LINES);

	//Between-planes right
	glVertex3fv((GLfloat*)&corners[1]);
	glVertex3fv((GLfloat*)&corners[5]);
	glVertex3fv((GLfloat*)&corners[7]);
	glVertex3fv((GLfloat*)&corners[3]);

	//Between-planes left
	glVertex3fv((GLfloat*)&corners[4]);
	glVertex3fv((GLfloat*)&corners[0]);
	glVertex3fv((GLfloat*)&corners[2]);
	glVertex3fv((GLfloat*)&corners[6]);

	//Far plane horizontal
	glVertex3fv((GLfloat*)&corners[5]);
	glVertex3fv((GLfloat*)&corners[4]);
	glVertex3fv((GLfloat*)&corners[6]);
	glVertex3fv((GLfloat*)&corners[7]);

	//Near plane horizontal
	glVertex3fv((GLfloat*)&corners[0]);
	glVertex3fv((GLfloat*)&corners[1]);
	glVertex3fv((GLfloat*)&corners[3]);
	glVertex3fv((GLfloat*)&corners[2]);

	//Near plane vertical
	glVertex3fv((GLfloat*)&corners[1]);
	glVertex3fv((GLfloat*)&corners[3]);
	glVertex3fv((GLfloat*)&corners[0]);
	glVertex3fv((GLfloat*)&corners[2]);

	//Far plane vertical
	glVertex3fv((GLfloat*)&corners[5]);
	glVertex3fv((GLfloat*)&corners[7]);
	glVertex3fv((GLfloat*)&corners[4]);
	glVertex3fv((GLfloat*)&corners[6]);

	glEnd();

	glColor4f(1.0, 1.0, 1.0, 1.0);
}

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

float* Component_Camera::GetViewMatrix()
{
	return &ViewMatrix;
}

void Component_Camera::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}

update_status Component_Camera::Load()
{

	return UPDATE_CONTINUE;
}