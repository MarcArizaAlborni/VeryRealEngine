
#include "Globals.h"
#include "libraries/Glew/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Primitive.h"

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

	// VERTICAL LINE

	glBegin(GL_LINES);

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

	glLineWidth(10.0f);

	glVertex3f(20.0f, 0.0f, 0.0f);
	glVertex3f(20.0f, 100.0f, 0.0f);

	glLineWidth(10.0f);

	glEnd();

	// TRIANGLE

	/*glBegin(GL_TRIANGLES);

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

	glLineWidth(10.0f);

	glVertex3f(0.0f, 0.0f, 50.0f);
	glVertex3f(10.0f, 50.0f, 50.0f);
	glVertex3f(20.0f, 25.0f, 50.0f);

	glLineWidth(10.0f);

	glEnd();*/

	// TRIANGLE STRIP

	//glBegin(GL_TRIANGLE_STRIP);

	//glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

	//glLineWidth(10.0f);

	//glVertex3f(0.0f, 0.0f, 0.0f); //1
	//glVertex3f(10.0f, 50.0f, 0.0f);//2
	//glVertex3f(20.0f, 25.0f, 0.0f);//3
	//glVertex3f(10.0f, 50.0f, 0.0f);//4
	//glVertex3f(20.0f, 25.0f, 0.0f);//5
	//glVertex3f(20.0f, 30.0f, 0.0f);//6
	//glVertex3f(30.0f, 40.0f, 0.0f);//7


	//glLineWidth(10.0f);

	//glEnd();

	// QUAD WITH TRIANGLES

	//glBegin(GL_TRIANGLES);

	//glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

	//glLineWidth(10.0f);

	//glVertex3f(1.0f, 1.0f, 1.0f); //1 eeste
	//glVertex3f(-1.0f, 1.0f, 1.0f);//2
	//glVertex3f(-1.0f, -1.0f, 1.0f);//3

	//glVertex3f(-1.0f, -1.0f, 1.0f); //1
	//glVertex3f(1.0f, -1.0f, 1.0f);//2
	//glVertex3f(1.0f, 1.0f, 1.0f);//3

	//glRotatef(0.1f, 1.0f, 1.0f, 0.0f);

	//glLineWidth(10.0f);

	//glEnd();

	// QUAD WITH TRIANGLES

	//glBegin(GL_TRIANGLES);

	//glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

	//glLineWidth(10.0f);

	////FRONT
	//glVertex3f(1.0f, 1.0f, 1.0f  ); //1 eeste
	//glVertex3f(-1.0f, 1.0f, 1.0f );//2
	//glVertex3f(-1.0f, -1.0f, 1.0f);//3

	//glVertex3f(-1.0f, -1.0f, 1.0f); //4
	//glVertex3f(1.0f, -1.0f, 1.0f );//5
	//glVertex3f(1.0f, 1.0f, 1.0f  );//6
	////DERECHA
	//glVertex3f(1.0f, 1.0f, 1.0f  ); //1 
	//glVertex3f(1.0f, -1.0f, 1.0f );//2
	//glVertex3f(1.0f, -1.0f, -1.0f);//3

	//glVertex3f(1.0f, -1.0f, -1.0f); //4
	//glVertex3f(1.0f, 1.0f, -1.0f );//5
	//glVertex3f(1.0f, 1.0f, 1.0f  );//6
	////ARRIBA
	//glVertex3f(1.0f, 1.0f, 1.0f  ); //1 
	//glVertex3f(1.0f, 1.0f, -1.0f );//2
	//glVertex3f(-1.0f, 1.0f, -1.0f);//3

	//glVertex3f(-1.0f, 1.0f, -1.0f); //4
	//glVertex3f(-1.0f, 1.0f, 1.0f );//5
	//glVertex3f(1.0f, 1.0f, 1.0f  );//6
	////IZQUIERDA
	//glVertex3f(-1.0f, 1.0f, 1.0f ); //1 
	//glVertex3f(-1.0f, 1.0f, -1.0f);//2
	//glVertex3f(-1.0f, -1.0f,-1.0f);//3

	//glVertex3f(-1.0f, -1.0f,-1.0f); //4
	//glVertex3f(-1.0f, -1.0f, 1.0f);//5
	//glVertex3f(-1.0f, 1.0f, 1.0f );//6
	////ABAJO
	//glVertex3f(-1.0f, -1.0f,-1.0f); //1 
	//glVertex3f(1.0f, -1.0f, -1.0f);//2
	//glVertex3f(1.0f, -1.0f, 1.0f );//3

	//glVertex3f(1.0f, -1.0f, 1.0f ); //4
	//glVertex3f(-1.0f, -1.0f, 1.0f);//5
	//glVertex3f(-1.0f, -1.0f,-1.0f);//6
	////DETRAS
	//glVertex3f(1.0f, -1.0f, -1.0f); //1 
	//glVertex3f(-1.0f, -1.0f,-1.0f);//2
	//glVertex3f(-1.0f, 1.0f, -1.0f);//3

	//glVertex3f(-1.0f, 1.0f, -1.0f); //4
	//glVertex3f(1.0f, 1.0f, -1.0f );//5
	//glVertex3f(1.0f, -1.0f, -1.0f);//6


    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	
	 GLfloat Vertices[108] = { 1.0f, 1.0f, 1.0f ,- 1.0f, 1.0f, 1.0f ,- 1.0f, -1.0f, 1.0f,-1.0f, -1.0f, 1.0f,1.0f, -1.0f, 1.0f,1.0f, 1.0f, 1.0f,

						1.0f, 1.0f, 1.0f,
						1.0f, -1.0f, 1.0f,
						1.0f, -1.0f, -1.0f,

						1.0f, -1.0f, -1.0f,
						1.0f, 1.0f, -1.0f,
						1.0f, 1.0f, 1.0f,

						1.0f, 1.0f, 1.0f,
						1.0f, 1.0f, -1.0f,
						-1.0f, 1.0f, -1.0f,

						-1.0f, 1.0f, -1.0f,
						-1.0f, 1.0f, 1.0f,
						1.0f, 1.0f, 1.0f,

						-1.0f, 1.0f, 1.0f,
						-1.0f, 1.0f, -1.0f,
						-1.0f, -1.0f,-1.0f,

						-1.0f, -1.0f,-1.0f,
						-1.0f, -1.0f, 1.0f,
						-1.0f, 1.0f, 1.0f,

						-1.0f, -1.0f,-1.0f,
						1.0f, -1.0f, -1.0f,
						1.0f, -1.0f, 1.0f,

						1.0f, -1.0f, 1.0f,
						-1.0f, -1.0f, 1.0f,
						-1.0f, -1.0f,-1.0f,

						1.0f, -1.0f, -1.0f,
						-1.0f, -1.0f,-1.0f,
						-1.0f, 1.0f, -1.0f,

						-1.0f, 1.0f, -1.0f,
						1.0f, 1.0f, -1.0f,
						1.0f, -1.0f, -1.0f 
	};

	////BUFFER ARRAY
	//uint my_id = 0;
	//glGenBuffers(1, (GLuint*)&(my_id));
	//glBindBuffer(GL_ARRAY_BUFFER, my_id);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36 * 3, Vertices, GL_STATIC_DRAW);



	//glEnableClientState(GL_VERTEX_ARRAY);
	//glBindBuffer(GL_ARRAY_BUFFER, my_id);
	//glVertexPointer(3, GL_FLOAT, 0, NULL);

	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//glDisableClientState(GL_VERTEX_ARRAY);

	GLubyte indices[36] = {

		     0,1,2, 2,3,0,   // 36 of indices
			 0,3,4, 4,5,0,
			 0,5,6, 6,1,0,
			 1,6,7, 7,2,1,
			 7,4,3, 3,2,7,
			 4,7,6, 6,5,4 
		              
	};

	//INDICES


	uint my_indices = 0;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)* 36, indices, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, Vertices);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_VERTEX_ARRAY);

	

	


	glColor3f(color.r, color.g, color.b);

	if(wire)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

// ------------------------------------------------------------
void Primitive::SetRotation(float angle, const vec3 &u)
{
	transform.rotate(angle, u);
	//TODO 6: Set the body rotation to the new rotation too!
}

// ------------------------------------------------------------
void Primitive::Scale(float x, float y, float z)
{
	transform.scale(x, y, z);
	//TODO 6: Set the body scale to the new scale too!
}

// CUBE ============================================
Cube::Cube() : Primitive(), size(1.0f, 1.0f, 1.0f)
{
	type = PrimitiveTypes::Primitive_Cube;
}

Cube::Cube(float sizeX, float sizeY, float sizeZ) : Primitive(), size(sizeX, sizeY, sizeZ)
{
	type = PrimitiveTypes::Primitive_Cube;
}

void Cube::InnerRender() const
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

// SPHERE ============================================

Sphere::Sphere(float _radius, float mass) : Primitive(), radius(_radius)
{
	type = PrimitiveTypes::Primitive_Sphere;
	//TODO 4: Initialize the PhysBody to be a Sphere
}

void Sphere::InnerRender() const
{

}


// CYLINDER ============================================
Cylinder::Cylinder() : Primitive(), radius(1.0f), height(1.0f)
{
	type = PrimitiveTypes::Primitive_Cylinder;
}

Cylinder::Cylinder(float radius, float height) : Primitive(), radius(radius), height(height)
{
	type = PrimitiveTypes::Primitive_Cylinder;
}

void Cylinder::InnerRender() const
{
	int n = 30;

	// Cylinder Bottom
	glBegin(GL_POLYGON);
	
	for(int i = 360; i >= 0; i -= (360 / n))
	{
		float a = i * M_PI / 180; // degrees to radians
		glVertex3f(-height*0.5f, radius * cos(a), radius * sin(a));
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