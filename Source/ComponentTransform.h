#pragma once
#ifndef __ComponentTransform_H__
#define __ComponentTransform_H__


#include "Component.h"
#include "ModuleGeometryManager.h"
#include "libraries/MathGeoLib/include/MathGeoLib.h"


struct TransformsInfo {


	float3 Translation = float3(0.f, 0.f, 0.f);
	float3 Scale = float3(0.f, 0.f, 0.f);
	Quat   Rotation = Quat::identity;

	float3 EulerRot = float3(0.f, 0.f, 0.f);
	float3 EulerRotTemp = float3(0.f, 0.f, 0.f);

	float4x4 Local_Matrix;
	float4x4 Global_Matrix;



};


class Component_Transform : public Component
{
public:



	TransformsInfo* Transformations;
	
	bool UpdateTransformations = false;

	void Enable()override;
	void Update()override;
	void Disable()override;
	void CleanUp()override;

	void UpdateTransformationsObjects(float3 translations, float3 scales, Quat rotations);

	
	void SetPosition(float3 position) { this->Transformations->Translation = position; UpdateLocalTransform(); };
	void SetRotation(float3 position) { this->Transformations->Rotation = Transformations->Rotation; UpdateLocalTransform(); };
	void SetEulerRotation(float3 eulerAngle);
	void inline SetScale(float3 scale) { this->Transformations->Scale = scale; UpdateLocalTransform(); };

	float3  GetPosition() const { return this->Transformations->Translation; };
	Quat  GetRotation() const { return this->Transformations->Rotation; };
	float3  GetScale() const { return this->Transformations->Scale; };
	float4x4  GetLocalTransform() const { return this->Transformations->Local_Matrix; };
	float4x4  GetGlobalTransform() const { return this->Transformations->Global_Matrix; };

	void UpdateLocalTransform();
	void UpdateGlobalTransform();
	void UpdateTRS();
	void UpdateEulerAngles();

	Component_Transform(Game_Object* parent); //DEFAULTS TO 0,0
	Component_Transform(Game_Object* parent, float3 position, float3 scale, Quat rotation);
	~Component_Transform();

};

#endif