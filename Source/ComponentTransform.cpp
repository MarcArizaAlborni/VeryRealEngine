#include "Application.h"
#include "Component.h"
#include "GameObject.h"
#include "ComponentTransform.h"
#include "libraries/MathGeoLib/include/MathGeoLib.h"

Component_Transform::Component_Transform(Game_Object* owner) : Component(owner), Translation(float3(0.0f, 0.0f, 0.0f)), Rotation(Quat::identity), Scale(float3(1.0f, 1.0f, 1.0f))
{
	Local_Matrix = float4x4::FromTRS(Translation, Rotation, Scale);
	Global_Matrix = Quat::identity;
	type = Component_Types::Transform;
	//UpdateEulerAngles();
};

Component_Transform::Component_Transform(Game_Object* owner, float3 position, float3 scale, Quat rotation) : Component(owner), Scale(scale), Rotation(rotation), Translation(position)
{
	Local_Matrix = float4x4::FromTRS(position, rotation, scale);
	Global_Matrix = Quat::identity;
	type = Component_Types::Transform;
	//UpdateEulerAngles();
};


Component_Transform::~Component_Transform()
{
}

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
	Local_Matrix = float4x4::FromTRS(translations, rotations, scales);

	UpdateGlobalTransform();

}

void Component_Transform::SetEulerRotation(float3 Angle)
{
	float3 vector = Angle * DEGTORAD;
	Quat quaternion = Quat::FromEulerXYZ(vector.x, vector.y, vector.z);
    Rotation = quaternion;
	EulerRot = vector;
	UpdateLocalTransform();
}

void Component_Transform::UpdateLocalTransform()
{
	Local_Matrix = float4x4::FromTRS(Translation, Rotation, Scale);
	UpdateEulerAngles();
	UpdateGlobalTransform();
}

void Component_Transform::UpdateGlobalTransform()
{
	Game_Object* ObjectOwner = owner->Parent;

	if (ObjectOwner != nullptr) //THIS IS THE ERROR??? IT DOESNT HAVE A PARENT
	{
		Global_Matrix = ObjectOwner->Transformations->Global_Matrix * Local_Matrix;
	}

	UpdateTRS();

	for (uint i = 0; i < owner->Children_List.size(); i++)
	{
		owner->Children_List.at(i)->Transformations->UpdateGlobalTransform();
	}
}

void Component_Transform::UpdateTRS()
{
	Local_Matrix.Decompose(Translation, Rotation, Scale);
	UpdateEulerAngles();
}

void Component_Transform::UpdateEulerAngles()
{
	EulerRot = Rotation.ToEulerXYZ();
	EulerRot *= RADTODEG;
}

//float4x4 Component_Transform::GetGlobalTransformMatrix()
//{
//	Rotation = Quat::FromEulerXYZ(EulerRot.x * DEGTORAD, EulerRot.y * DEGTORAD, EulerRot.z * DEGTORAD);
//	Local_Matrix = float4x4::FromTRS(Translation, Rotation, Scale);
//
//	if (owner->GetParent())
//	{
//		Global_Matrix = my_go->GetParent()->GetComponentTransform()->GetGlobalTransformMatrix() * local_matrix;
//	}
//		
//	else
//	{
//		Global_Matrix = Local_Matrix;
//	}
//		
//	Global_Matrix.Decompose(position, rotation, scale);
//
//	return global_matrix;
//}

