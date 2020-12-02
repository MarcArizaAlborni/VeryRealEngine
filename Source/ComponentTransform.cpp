



#include "ComponentTransform.h"

void Component_Transform::Enable()
{
}

void Component_Transform::Update()
{
}

void Component_Transform::Disable()
{
}

void Component_Transform::CleanUp()
{
}

void Component_Transform::UpdateTransformationsObjects(float3 translations, float3 scales, Quat rotations)
{

}

void Component_Transform::SetEulerRotation(float3 eulerAngle)
{
}

void Component_Transform::UpdateLocalTransform()
{
}

void Component_Transform::UpdateGlobalTransform()
{
}

void Component_Transform::UpdateTRS()
{
}

void Component_Transform::UpdateEulerAngles()
{
}

Component_Transform::Component_Transform(Game_Object* parent) :Component(parent)
{
}

Component_Transform::Component_Transform(Game_Object* parent, float3 position, float3 scale, Quat rotation) : Component(parent)
{
}

Component_Transform::~Component_Transform()
{
}
