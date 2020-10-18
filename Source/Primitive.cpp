
#include "Globals.h"
#include "libraries/Glew/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Primitive.h"
#include "Application.h"



// ------------------------------------------------------------
Primitive::Primitive() : transform(IdentityMatrix), color(White), wire(false), axis(false), type(PrimitiveTypes::Primitive_Point)
{}

// ------------------------------------------------------------
PrimitiveTypes Primitive::GetType() const
{
	return type;
}

void Primitive::Update()
{
	//TODO 5: Set the primitive position and rotation to the PhysBody position and rotation
}

// ------------------------------------------------------------
void Primitive::Render() const
{
	glPushMatrix();
	glMultMatrixf(transform.M);

	if(axis == true)
	{
		// Draw Axis Grid
		glLineWidth(2.0f);

		glBegin(GL_LINES);

		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.1f, 0.0f); glVertex3f(1.1f, -0.1f, 0.0f);
		glVertex3f(1.1f, 0.1f, 0.0f); glVertex3f(1.0f, -0.1f, 0.0f);

		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
		glVertex3f(0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
		glVertex3f(0.0f, 1.15f, 0.0f); glVertex3f(0.0f, 1.05f, 0.0f);

		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.05f, 0.1f, 1.05f); glVertex3f(0.05f, 0.1f, 1.05f);
		glVertex3f(0.05f, 0.1f, 1.05f); glVertex3f(-0.05f, -0.1f, 1.05f);
		glVertex3f(-0.05f, -0.1f, 1.05f); glVertex3f(0.05f, -0.1f, 1.05f);

		glEnd();

		glLineWidth(1.0f);
	}

	glColor3f(color.r, color.g, color.b);

	/*if (wire || App->renderPrimitives == false)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
		
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}*/
		

	InnerRender();

	glPopMatrix();
}

// ------------------------------------------------------------
void Primitive::InnerRender() const
{
	glPointSize(5.0f);

	glBegin(GL_POINTS);

	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();

	glPointSize(1.0f);
}

// ------------------------------------------------------------
void Primitive::SetPos(float x, float y, float z)
{
	transform.translate(x, y, z);
	//TODO 6: Set the body position to the new position too!
}

vec3 Primitive::GetPos() const
{
	vec3 position = { 0.0f, 0.0f, 0.0f };

	position.x = transform.M[12];				
	position.y = transform.M[13];
	position.z = transform.M[14];

	return position;
}

// ------------------------------------------------------------
void Primitive::SetRotation(float angle, const vec3 &u)
{
	transform.rotate(angle, u);
}

// ------------------------------------------------------------
void Primitive::Scale(float x, float y, float z)
{
	transform.scale(x, y, z);
}


// CUBE ============================================
Cube::Cube(const vec3& _size, float mass) : Primitive(), size(_size), loaded_indices(false)
{
	type = PrimitiveTypes::Primitive_Cube;
}

vec3 Cube::GetSize() const
{
	return size;
}

void Cube::InnerCubeRender() const
{	
	float sx = size.x * 0.5f;
	float sy = size.y * 0.5f;
	float sz = size.z * 0.5f;

	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-sx, -sy, sz);
	glVertex3f( sx, -sy, sz);
	glVertex3f( sx,  sy, sz);
	glVertex3f(-sx,  sy, sz);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f( sx, -sy, -sz);
	glVertex3f(-sx, -sy, -sz);
	glVertex3f(-sx,  sy, -sz);
	glVertex3f( sx,  sy, -sz);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(sx, -sy,  sz);
	glVertex3f(sx, -sy, -sz);
	glVertex3f(sx,  sy, -sz);
	glVertex3f(sx,  sy,  sz);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-sx, -sy, -sz);
	glVertex3f(-sx, -sy,  sz);
	glVertex3f(-sx,  sy,  sz);
	glVertex3f(-sx,  sy, -sz);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-sx, sy,  sz);
	glVertex3f( sx, sy,  sz);
	glVertex3f( sx, sy, -sz);
	glVertex3f(-sx, sy, -sz);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-sx, -sy, -sz);
	glVertex3f( sx, -sy, -sz);
	glVertex3f( sx, -sy,  sz);
	glVertex3f(-sx, -sy,  sz);

	glEnd();
}

void Cube::RenderCube_Indices()
{
	GLfloat Vertices2[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,   1,-1, 1,   // v0,v1,v2,v3 (front)
							 1, 1, 1,   1,-1, 1,   1,-1,-1,   1, 1,-1,   // v0,v3,v4,v5 (right)
							 1, 1, 1,   1, 1,-1,  -1, 1,-1,  -1, 1, 1,   // v0,v5,v6,v1 (top)
							-1, 1, 1,  -1, 1,-1,  -1,-1,-1,  -1,-1, 1,   // v1,v6,v7,v2 (left)
							-1,-1,-1,   1,-1,-1,   1,-1, 1,  -1,-1, 1,   // v7,v4,v3,v2 (bottom)
							 1,-1,-1,  -1,-1,-1,  -1, 1,-1,   1, 1,-1
		};

		GLubyte indices[] = { 0, 1, 2,   2, 3, 0,
						   4, 5, 6,   6, 7, 4,
						   8, 9,10,  10,11, 8,
						  12,13,14,  14,15,12,
						  16,17,18,  18,19,16,
						  20,21,22,  22,23,20
		};

		uint my_indices = 0;



		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, indices, GL_STATIC_DRAW);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, Vertices2);


		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);

		glDisableClientState(GL_VERTEX_ARRAY);
}

void Cube::ApplyTransform(float* coordinates, int array_size)
{
	vec3 position = GetPos();

	for (int i = 0; i < array_size; ++i)
	{
		coordinates[i] += position.x;
		coordinates[++i] += position.y;
		coordinates[++i] += position.z;
	}
}

void Cube::ApplySize(float* coordinates, int array_size)
{
	for (uint i = 0; i < array_size; ++i)				
	{
		coordinates[i] *= size.x * 0.5f;
		coordinates[++i] *= size.y * 0.5f;
		coordinates[++i] *= size.z * 0.5f;
	}
}


// SPHERE ============================================

Sphere::Sphere(float radius, uint rings, uint divisions) : Primitive(), radius(radius), rings(rings), divisions(divisions), loaded_indices(false)
{
	type = PrimitiveTypes::Primitive_Sphere;
}

float Sphere::GetRadius() const
{
	return radius;
}

uint Sphere::GetRings() const
{
	return rings;
}

uint Sphere::GetDivisions() const
{
	return divisions;
}

void Sphere::SetRings(uint rings)
{
	this->rings = rings;

	loaded_indices = false;
}

void Sphere::SetDivisions(uint sectors)
{
	this->divisions = sectors;

	loaded_indices = false;
}

void Sphere::RenderSphere_Indices()
{

}


// CYLINDER ============================================
Cylinder::Cylinder(float radius, float height, float mass) : Primitive(), radius(radius), height(height)
{
	type = PrimitiveTypes::Primitive_Cylinder;
}

float Cylinder::GetRadius() const
{
	return radius;
}

float Cylinder::GetHeight() const
{
	return height;
}


void Cylinder::InnerCylinderRender() const
{
	glPushMatrix();
	mat4x4 rotateMat = IdentityMatrix;
	rotateMat.rotate(90.f, vec3(0, 0, 1));
	glMultMatrixf(&rotateMat);

	int n = 30;

	// Cylinder Bottom
	glBegin(GL_POLYGON);
	
	for(int i = 360; i >= 0; i -= (360 / n))
	{
		float a = i * M_PI / 180; // degrees to radians
		glVertex3f(-height * 0.5f, radius * cos(a), radius * sin(a));
	}
	glEnd();

	// Cylinder Top
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	for(int i = 0; i <= 360; i += (360 / n))
	{
		float a = i * M_PI / 180; // degrees to radians
		glVertex3f(height * 0.5f, radius * cos(a), radius * sin(a));
	}
	glEnd();

	// Cylinder "Cover"
	glBegin(GL_QUAD_STRIP);
	for(int i = 0; i < 480; i += (360 / n))
	{
		float a = i * M_PI / 180; // degrees to radians

		glVertex3f(height*0.5f,  radius * cos(a), radius * sin(a) );
		glVertex3f(-height*0.5f, radius * cos(a), radius * sin(a) );
	}
	glEnd();

	glPopMatrix();
}

void RenderCylinder_Indices()
{

}


// PYRAMID ============================================
Pyramid::Pyramid(vec3 size) : Primitive(), size(size), loaded_indices(false)
{
	type = PrimitiveTypes::Primitive_Pyramid;
}

void Pyramid::RenderPyramid_Indices()
{
	// Draw the base square
	glBegin(GL_QUADS);
	glVertex3f(-1, 0, -1);
	glVertex3f(-1, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, -1);
	glEnd();

	// Draw four side triangles
	glBegin(GL_TRIANGLE_FAN);

	// the commond point of the four triangles
	glVertex3f(0, 1.4, 0);

	// Base points of each triangle
	glVertex3f(-1, 0, -1);
	glVertex3f(-1, 0, 1);

	glVertex3f(-1, 0, 1);
	glVertex3f(1, 0, 1);

	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, -1);

	glVertex3f(1, 0, -1);
	glVertex3f(-1, 0, -1);

	glEnd();
}


// LINE ==================================================
Line::Line() : Primitive(), origin(0, 0, 0), destination(1, 1, 1)
{
	type = PrimitiveTypes::Primitive_Line;
}

Line::Line(float x, float y, float z) : Primitive(), origin(0, 0, 0), destination(x, y, z)
{
	type = PrimitiveTypes::Primitive_Line;
}

void Line::InnerRender() const
{
	glLineWidth(2.0f);

	glBegin(GL_LINES);

	glVertex3f(origin.x, origin.y, origin.z);
	glVertex3f(destination.x, destination.y, destination.z);

	glEnd();

	glLineWidth(1.0f);
}

// PLANE ==================================================
Plane::Plane() : Primitive(), normal(0, 1, 0), constant(1)
{
	type = PrimitiveTypes::Primitive_Plane;
}

Plane::Plane(float x, float y, float z, float d) : Primitive(), normal(x, y, z), constant(d)
{
	type = PrimitiveTypes::Primitive_Plane;
}

void Plane::InnerRender() const
{
	glLineWidth(1.0f);

	glBegin(GL_LINES);

	float d = 200.0f;

	for(float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}

	glEnd();
}