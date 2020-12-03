#pragma once
#ifndef __ComponentTransform_H__
#define __ComponentTransform_H__


#include "Component.h"
#include "ModuleGeometryManager.h"
#include "libraries/MathGeoLib/include/MathGeoLib.h"



class Component_Transform : public Component
{
public:


	float3 Translation = float3(0.f, 0.f, 0.f);
	float3 Scale = float3(0.f, 0.f, 0.f);
	Quat   Rotation = Quat::identity;

	
	float4x4 Local_Matrix;
	float4x4 Global_Matrix;


	float3 EulerRot = float3(0.f, 0.f, 0.f);
	float3 EulerRotTemp = float3(0.f, 0.f, 0.f);


	bool UpdateTransformations = false;

	void Enable()override;
	void Update()override;
	void Disable()override;
	void CleanUp()override;

	void UpdateTransformationsObjects(float3 translations, float3 scales, Quat rotations);

	
	void SetPosition(float3 position) { this->Translation = position; UpdateLocalTransform(); };
	void SetRotation(float3 position) { this->Rotation = Rotation; UpdateLocalTransform(); };
	void SetEulerRotation(float3 eulerAngle);
	void inline SetScale(float3 scale) { this->Scale = scale; UpdateLocalTransform(); };

	float3  GetPosition() const { return this->Translation; };
	Quat  GetRotation() const { return this->Rotation; };
	float3  GetScale() const { return this->Scale; };
	float4x4  GetLocalTransform() const { return this->Local_Matrix; };
	float4x4  GetGlobalTransform() const { return this->Global_Matrix; };

	void UpdateLocalTransform();
	void UpdateGlobalTransform();
	void UpdateTRS();
	void UpdateEulerAngles();

	Component_Transform(Game_Object* parent);
	Component_Transform(Game_Object* parent, float3 position, float3 scale, Quat rotation);
	~Component_Transform();

};

#endif