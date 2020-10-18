
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
class Sphere : public Primitive
{
public:
	Sphere(float radius = 1.f, uint rings = 12, uint divisions = 24);

public:
	float GetRadius() const;
	uint GetRings() const;
	uint GetDivisions() const;

	void SetRings(uint rings);
	void SetDivisions(uint sectors);

	void RenderSphere_Indices();

public:

	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> tex_coords;
	std::vector<uint> indices;

	bool loaded_indices;

	float radius;
	uint rings;
	uint divisions;
};

// ============================================
class Cylinder : public Primitive
{
public:
	Cylinder(float radius = 1.f, float height = 2.f, float mass = 1.f);

	float GetRadius() const;
	float GetHeight() const;

	void InnerCylinderRender() const;
	void RenderCylinder_Indices();


public:
	float radius;
	float height;
};

// ============================================
class Pyramid : public Primitive
{
public:
	Pyramid(vec3 size = vec3(1.0f, 1.0f, 1.0f));

	void RenderPyramid_Indices();

public:
	std::vector<float> vertices;
	std::vector<uint> indices;

public:
	vec3 size;

	bool loaded_indices;
};

// ============================================
class Line : public Primitive
{
public:
	Line();
	Line(float x, float y, float z);

public:
	void InnerRender() const;
public:
	vec3 origin;
	vec3 destination;
};

// ============================================
class Plane : public Primitive
{
public:
	Plane();
	Plane(float x, float y, float z, float d);

public:
	void InnerRender() const;
public:
	vec3 normal;
	float constant;
};