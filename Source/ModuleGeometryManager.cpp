#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleGeometryManager.h"
#include "libraries/Glew/include/GL/glew.h"
#include "libraries/SDL/include/SDL_opengl.h"
#include "Primitive.h"
#include "ModuleMeshImporter.h"
#include <gl/GL.h>
#include <gl/GLU.h>


#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleGeometryManager::ModuleGeometryManager(Application* app, const char* name, bool start_enabled) : Module(app, "Render3D", start_enabled)
{
}

// Destructor
ModuleGeometryManager::~ModuleGeometryManager()
{}

// Called before render is available
bool ModuleGeometryManager::Init()
{
	LOGFIX("Creating geometrymanager context");
	bool ret = true;


	return ret;
}

bool ModuleGeometryManager::Start()
{
	return true;
}

// PreUpdate: clear buffer
update_status ModuleGeometryManager::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleGeometryManager::Update(float dt)
{
	glColor4f(0.5f, 0.5, 0.5f, 1.0f);

	std::vector<GameObject*>::iterator IteratorLoaded = App->meshimporter->MeshesOnScene.begin();
	for (int a = 0; a < App->meshimporter->MeshesOnScene.size(); ++a) {
		GameObject* Item = *IteratorLoaded;
		//right now we only load the house texture
		if (Item->is_Drawn == true) {
			DrawTextureOnMesh(*IteratorLoaded, App->textureImporter->mTextureID);
		}
		//DrawMesh(*IteratorLoaded);

		IteratorLoaded++;
	}

	return UPDATE_CONTINUE;
}


// PostUpdate present buffer to screen
update_status ModuleGeometryManager::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleGeometryManager::CleanUp()
{
	LOGFIX("Destroying geometrymanager");

	return true;
}


// Draws a cube
void ModuleGeometryManager::DrawCube()
{
	App->meshimporter->LoadMesh("Assets/Models/Primitives/Cube.FBX");
}

void ModuleGeometryManager::DrawPyramid()
{
	App->meshimporter->LoadMesh("Assets/Models/Primitives/Pyramid.FBX");
}

void ModuleGeometryManager::DrawSphere()
{
	App->meshimporter->LoadMesh("Assets/Models/Primitives/Sphere.FBX");
}

void ModuleGeometryManager::DrawCylinder()
{
	App->meshimporter->LoadMesh("Assets/Models/Primitives/Cylinder.FBX");
}

void ModuleGeometryManager::Transform_Mesh_Translation(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glPopMatrix();
}

void ModuleGeometryManager::Transform_Mesh_Scale(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	glScalef(x, y, z);
	glPopMatrix();
}

void ModuleGeometryManager::Transform_Mesh_Rotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	glRotatef(angle, x, y, z);
	glPopMatrix();
}

void ModuleGeometryManager::DrawPlane()
{
	App->meshimporter->LoadMesh("Assets/Models/Primitives/Plane.FBX");
}

// Draw mesh with vertex and index
void ModuleGeometryManager::DrawMesh(const GameObject* mesh)
{
	
	Transform_Mesh_Translation(mesh->Mesh_Transform_Modifiers.Translation_Vec3[0],mesh->Mesh_Transform_Modifiers.Translation_Vec3[1], mesh->Mesh_Transform_Modifiers.Translation_Vec3[2]);
	Transform_Mesh_Scale(mesh->Mesh_Transform_Modifiers.Scale_Vec3[0], mesh->Mesh_Transform_Modifiers.Scale_Vec3[1], mesh->Mesh_Transform_Modifiers.Scale_Vec3[2]);
	Transform_Mesh_Rotation(mesh->Mesh_Transform_Modifiers.Rotation_Vec3[0], mesh->Mesh_Transform_Modifiers.Scale_Vec3[1],mesh->Mesh_Transform_Modifiers.Scale_Vec3[2], mesh->Mesh_Transform_Modifiers.Scale_Vec3[3]);
	
	
	glEnableClientState(GL_VERTEX_ARRAY);

	//Bind buffers
	glBindBuffer(GL_ARRAY_BUFFER, mesh->MeshData.id_vertex);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->MeshData.id_index);

	//Draw
	glDrawElements(GL_TRIANGLES, mesh->MeshData.num_index, GL_UNSIGNED_INT, nullptr);

	//Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();

 
}

void ModuleGeometryManager::DrawTextureOnMesh(const GameObject* mesh, const uint texture_id)
{
	if (mesh->is_Wireframed == true) {
		glLineWidth(3);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	//CAREFULL IF THERE ISNT A TEXTURE LOADED IT CAN CRASH
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Bind Buffers
	glBindTexture(GL_TEXTURE_2D, texture_id); // Texture
	glActiveTexture(GL_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->MeshData.texcoords_id); // Texture Coordinates
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	

	DrawMesh(mesh); 

	//Unbind Buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ModuleGeometryManager::CreateConsolelog(const char file[], int line, const char* format, ...)
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