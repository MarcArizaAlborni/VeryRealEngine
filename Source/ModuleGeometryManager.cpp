#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleGeometryManager.h"
#include "ModuleTextureImporter.h"
#include "ModuleEditorConsole.h"
#include "libraries/Glew/include/GL/glew.h"
#include "libraries/SDL/include/SDL_opengl.h"
#include "Primitive.h"
#include "ModuleMeshImporter.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "libraries/MathGeoLib/include/MathGeoLib.h"
#include "libraries/MathGeoLib/include/MathBuildConfig.h"


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
	App->meshimporter->LoadedTexturesList.size();


	GameObject* MoveAsFamily;
	GameObject* MoveAsFamilyChild;
	std::vector<GameObject*>::iterator IteratorPositionModifierFamily = App->meshimporter->MeshesOnScene.begin();
	for (int t = 0; t < App->meshimporter->MeshesOnScene.size(); ++t) {
	
		MoveAsFamily = *IteratorPositionModifierFamily;

		if (MoveAsFamily->is_FamilyMove){

			std::vector<GameObject*>::iterator IteratorModifierFamilyChild = MoveAsFamily->ChildObjects.begin();
			for (int u = 0; u < MoveAsFamily->ChildObjects.size(); ++u) {

				MoveAsFamilyChild = *IteratorModifierFamilyChild;

				MoveAsFamilyChild->Mesh_Transform_Modifiers.VectorRotation = MoveAsFamily->Mesh_Transform_Modifiers.VectorRotation;
				MoveAsFamilyChild->Mesh_Transform_Modifiers.VectorScale = MoveAsFamily->Mesh_Transform_Modifiers.VectorScale;
				MoveAsFamilyChild->Mesh_Transform_Modifiers.VectorTranslation = MoveAsFamily->Mesh_Transform_Modifiers.VectorTranslation;

				++IteratorModifierFamilyChild;
			}
		}
		++IteratorPositionModifierFamily;
	}

	glColor4f(0.5f, 0.5, 0.5f, 1.0f);
	GameObject* Item;
	GameObject* Item2;
	std::vector<GameObject*>::iterator IteratorLoaded = App->meshimporter->MeshesOnScene.begin();
	for (int a = 0; a < App->meshimporter->MeshesOnScene.size(); ++a) {
		Item=*IteratorLoaded;

		if (Item->ChildObjects.empty()) {

			if (Item->is_Drawn == true) {
				DrawMeshTextured(*IteratorLoaded);
			}
		}
		else {
			std::vector<GameObject*>::iterator IteratorChild = Item->ChildObjects.begin();
			for (int b = 0; b < Item->ChildObjects.size(); ++b) {
				Item2 = *IteratorChild;
				if (Item2->is_Drawn == true) {

					DrawMeshTextured(*IteratorChild);
				}
			
				++IteratorChild;
			}
		}
		++IteratorLoaded;
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
	//App->meshimporter->LoadMesh("Assets/Models/Primitives/Pyramid.FBX");
}

void ModuleGeometryManager::DrawSphere()
{
	App->meshimporter->LoadMesh("Assets/Models/Primitives/Sphere.FBX");
}

void ModuleGeometryManager::DrawCylinder()
{
	App->meshimporter->LoadMesh("Assets/Models/Primitives/Cylinder.FBX");
}



void ModuleGeometryManager::Transform_Mesh_Translation(GameObject* mesh, VectorTransformations Current, VectorTransformations New)
{
	glPushMatrix();
	glTranslatef( Current.x + New.x, Current.y + New.y, Current.z + New.z);
	
}

void ModuleGeometryManager::Transform_Mesh_Scale(GameObject* mesh, VectorTransformations Current, VectorTransformations New)
{
	glPushMatrix();
	glScalef(Current.x + New.x, Current.y + New.y, Current.z + New.z);
	
}

void ModuleGeometryManager::Transform_Mesh_Rotation(GameObject* mesh, VectorTransformations Current, VectorTransformations New)
{
	
	glPushMatrix();
	glRotatef(Current.angle + New.angle, Current.x + New.x, Current.y + New.y, Current.z + New.z);

}


void ModuleGeometryManager::DrawPlane()
{
	App->meshimporter->LoadMesh("Assets/Models/Primitives/Plane.FBX");
}

void ModuleGeometryManager::DrawMeshTextured(GameObject* mesh)
{

	GLfloat Null_Array[] = { 0,0,0,0 };

	VectorTransformations ZeroArray;
	VectorTransformations OneArray;

	OneArray = { 1,1,1,1 };
	ZeroArray = { 0,0,0,0 };

	if (mesh->is_Wireframed == true) {
		glLineWidth(3);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	Transform_Mesh_Translation(mesh, mesh->Mesh_Transform_Modifiers.VectorTranslation, ZeroArray);
	Transform_Mesh_Scale(mesh, mesh->Mesh_Transform_Modifiers.VectorScale, OneArray);
	Transform_Mesh_Rotation(mesh, mesh->Mesh_Transform_Modifiers.VectorRotation, ZeroArray);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	if (mesh->is_Checkered == true) {

		glBindTexture(GL_TEXTURE_2D,App->textureImporter->TextureCheckers.texture_id);

		glBindBuffer(GL_ARRAY_BUFFER, mesh->MeshData.texcoords_id);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	}
	
	DrawFaceNormals(mesh);
	DrawVertexNormals(mesh);

	if (mesh->is_Textured == true) {
		

		glBindTexture(GL_TEXTURE_2D, mesh->TextureData.texture_id);

		glBindBuffer(GL_ARRAY_BUFFER, mesh->MeshData.texcoords_id);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	}

	glBindBuffer(GL_ARRAY_BUFFER, mesh->MeshData.id_vertex);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mesh->MeshData.id_index);
	glDrawElements(GL_TRIANGLES,mesh->MeshData.num_index, GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();
	
}

void ModuleGeometryManager::DrawVertexNormals(GameObject* object)
{
	/*if (object->showVertexNormals == true)
	{
		for (int j = 0; j < object->MeshData.num_vertex; ++j)
		{
			float3 vert = object->MeshData.vertex[j];
			float3 norm = object->MeshData.normals[j];

			glLineWidth(1.5f);
			glBegin(GL_LINES);

			glVertex3f(vert.x, vert.y, vert.z);
			glVertex3f(vert.x + norm.x, vert.y + norm.y, vert.z + norm.z);
		}

		glEnd();
	}*/
}

// Draw normals with faces and triangles
void ModuleGeometryManager::DrawFaceNormals(GameObject* object)
{

	/*if (object->showFaceNormals == true)
	{
		float3 mid;
		float3 normal;

		for (int i = 0; i < object->MeshData.num_index; i += 3)
		{
			float3 vert1 = object->MeshData.vertex[object->MeshData.index[i]];
			float3 vert2 = object->MeshData.vertex[object->MeshData.index[i + 1]];
			float3 vert3 = object->MeshData.vertex[object->MeshData.index[i + 2]];


			mid = (vert1 + vert2 + vert3) / 3;

			normal = Cross((vert2 - vert1), (vert3 - vert1));
			normal.Normalize();

			glLineWidth(1.5f);
			glBegin(GL_LINES);
			glVertex3f(mid.x, mid.y, mid.z);
			glVertex3f(mid.x + normal.x, mid.y + normal.y, mid.z + normal.z );
			

		}

		glEnd();
	}*/

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
