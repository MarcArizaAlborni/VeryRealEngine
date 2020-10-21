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
	LOGFIX("Creating GeometryLoader context");
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

	std::vector<GameObject*>::iterator IteratorLoaded = App->meshimporter->MeshesOnScene.begin();
	for (int a = 0; a < App->meshimporter->MeshesOnScene.size(); ++a) {

		//GameObject* MeshT;
		
		/*MeshInfo* MeshToDraw = *IteratorLoaded;
		MeshToDraw->MeshData.mesh_name;*/
		//DrawMesh(MeshToDraw);

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
	LOGFIX("Destroying GeometryLoader");

	return true;
}


// Draws a cube
void ModuleGeometryLoader::DrawCube()
{
	App->meshimporter->LoadMesh("Assets/Models/Primitives/Cube.FBX");
}

void ModuleGeometryLoader::DrawPyramid()
{
	App->meshimporter->LoadMesh("Assets/Models/Primitives/Pyramid.FBX");
	
}

void ModuleGeometryLoader::DrawSphere()
{
	App->meshimporter->LoadMesh("Assets/Models/Primitives/Sphere.FBX");
}

void ModuleGeometryLoader::DrawCylinder()
{
	App->meshimporter->LoadMesh("Assets/Models/Primitives/Cylinder.FBX");
}

void ModuleGeometryLoader::DrawPlane()
{
	App->meshimporter->LoadMesh("Assets/Models/Primitives/Plane.FBX");
}

// Draw mesh with vertex and index
void ModuleGeometryLoader::DrawMesh(const GameObject* mesh)
{
	
	if (mesh->MeshData.index != nullptr) {

		/*glPushMatrix();
		glScalef(0.5,0.5,0.5);
		glRotatef(90, -1.0, 0.0, 0.0);
		glRotatef(45, 0.0, 0.0, 1.0);

		if (App->input->keyboard[SDL_SCANCODE_LEFT]) {

			glTranslatef(-5.0, 0.0, 0.0);
		}*/
		
		//Bind buffers
		glEnableClientState(GL_VERTEX_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, mesh->MeshData.id_vertex);



		glVertexPointer(3, GL_FLOAT, 0, NULL);



		glBindTexture(GL_TEXTURE_2D, App->renderer3D->CheckerTexture);
		//glActiveTexture(GL_TEXTURE0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->MeshData.id_index);

		glDrawElements(GL_TRIANGLES, mesh->MeshData.num_index, GL_UNSIGNED_INT, nullptr);

		//TURN OFF
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDisableClientState(GL_VERTEX_ARRAY);

		/*glPopMatrix();*/
	}
}

void ModuleGeometryLoader::CreateConsolelog(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
	OutputDebugString(tmp_string2);


	App->console->ConsoleLogs.push_back(tmp_string2);
}
