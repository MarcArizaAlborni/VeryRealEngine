#include "Application.h"
#include "ComponentCamera.h"
#include "Component.h"

#include "libraries/MathGeoLib/include/Geometry/Frustum.h"

ComponentCamera::ComponentCamera(Component_Types comp_type, bool act, Game_Object* obj) : Component(obj)
{
	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);
}

void ComponentCamera::CreateFrustum()
{

}

float* ComponentCamera::GetViewMatrix()
{
	return &ViewMatrix;
}

void ComponentCamera::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}

update_status ComponentCamera::Load()
{

	return UPDATE_CONTINUE;
}
