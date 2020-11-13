
#pragma once
#include "glmath.h"
#include "Color.h"
#include <vector>
#include <cmath>

enum PrimitiveTypes
{
	Primitive_Point,
	Primitive_Line,
	Primitive_Plane,
	Primitive_Cube,
	Primitive_Sphere,
	Primitive_Cylinder,
	Primitive_Pyramid
};

class Primitive
{
public:
	Primitive();

	void Update();
	virtual void	Render() const;
	void			SetPos(float x, float y, float z);
	vec3			GetPos() const;
	void			SetRotation(float angle, const vec3 &u);
	void			Scale(float x, float y, float z);
	PrimitiveTypes	GetType() const;


	Color color;
	mat4x4 transform;
	bool axis,wire;


protected:
	virtual void InnerRender() const;
	PrimitiveTypes type;
};

// ============================================
class Cube : public Primitive
{
public :
	Cube(const vec3& size = vec3(1.f, 1.f, 1.f), float mass = 1.f);
	vec3 GetSize() const;

public:
	void InnerCubeRender() const;
	void RenderCube_Indices();

	void ApplyTransform(float* coordinates, int array_size);
	
	void ApplySize(float* coordinates, int array_size);
public:
	vec3 size;
	bool loaded_indices;
};

// ============================================
class Plane2 : public Primitive
{
public:
	Plane2();
	Plane2(float x, float y, float z, float d);

public:
	void InnerRender() const;
public:
	vec3 normal;
	float constant;
};