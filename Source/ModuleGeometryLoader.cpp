#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleGeometryLoader.h"
#include "libraries/Glew/include/GL/glew.h"
#include "libraries/SDL/include/SDL_opengl.h"
#include "Primitive.h"
#include "ModuleMeshImporter.h"
#include <gl/GL.h>
#include <gl/GLU.h>


#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleGeometryLoader::ModuleGeometryLoader(Application* app, const char* name, bool start_enabled) : Module(app, "Render3D", start_enabled)
{
}

// Destructor
ModuleGeometryLoader::~ModuleGeometryLoader()
{}

// Called before render is available
bool ModuleGeometryLoader::Init()
{
	LOG("Creating GeometryLoader context");
	bool ret = true;


	return ret;
}

bool ModuleGeometryLoader::Start()
{

	return true;
}

// PreUpdate: clear buffer
update_status ModuleGeometryLoader::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

update_status ModuleGeometryLoader::Update(float dt)
{
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

	std::list<MeshInfo*>::iterator IteratorLoaded = App->meshimporter->LoadedMeshes.begin();
	for (int a = 0; a < App->meshimporter->LoadedMeshes.size(); ++a) {

		DrawMesh(*IteratorLoaded);
		IteratorLoaded++;
	}

	return UPDATE_CONTINUE;
}


// PostUpdate present buffer to screen
update_status ModuleGeometryLoader::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleGeometryLoader::CleanUp()
{
	LOG("Destroying GeometryLoader");


	return true;
}


// Draws a cube
void ModuleGeometryLoader::DrawCube()
{
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

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


void ModuleGeometryLoader::DrawPyramid()
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

void ModuleGeometryLoader::DrawCylinder()
{

}

// Draw mesh with vertex and index
void ModuleGeometryLoader::DrawMesh(const MeshInfo* mesh)
{
	if (mesh->index != nullptr) {
		//Bind buffers
		glEnableClientState(GL_VERTEX_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, mesh->id_vertex);

		glVertexPointer(3, GL_FLOAT, 0, NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->id_index);

		glDrawElements(GL_TRIANGLES, mesh->num_index, GL_UNSIGNED_INT, nullptr);

		//TURN OFF
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDisableClientState(GL_VERTEX_ARRAY);

	}
}