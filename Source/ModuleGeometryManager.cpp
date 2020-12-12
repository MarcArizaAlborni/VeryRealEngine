#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleGeometryManager.h"
#include "ModuleTextureImporter.h"
#include "ModuleEditor.h"
#include "libraries/Glew/include/GL/glew.h"
#include "libraries/SDL/include/SDL_opengl.h"
#include "Primitive.h"
#include "ModuleScene.h"
#include "ModuleCamera3D.h"
#include "ComponentCamera.h"
#include "ModuleMeshImporter.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "libraries/MathGeoLib/include/MathGeoLib.h"
#include "libraries/MathGeoLib/include/MathBuildConfig.h"
#include "ModuleMeshImporter.h"

#include "GameObject.h"
#include "Component.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"
#include "ComponentTransform.h"

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
	LOG("Creating geometrymanager context");
	bool ret = true;

	return ret;
}

bool ModuleGeometryManager::Start()
{
	 ObjectsOnScene.size();

	
	
	return true;
}

// PreUpdate: clear buffer
update_status ModuleGeometryManager::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleGeometryManager::Update(float dt)
{

	std::vector<Game_Object*>::iterator GameObjectIt = App->geometrymanager->ObjectsOnScene.begin();

	for (int i = 0; i < App->geometrymanager->ObjectsOnScene.size(); ++i) {

		Game_Object* Object = *GameObjectIt;
		Object->Update();

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
	LOG("Destroying geometrymanager");
	return true;
}

// Draws a cube
void ModuleGeometryManager::DrawCube()
{
	App->meshimporter->LoadFile_Mesh("Assets/Models/Primitives/Cube.FBX");
}

void ModuleGeometryManager::DrawPyramid()
{
	
}

void ModuleGeometryManager::DrawSphere()
{
	App->meshimporter->LoadFile_Mesh("Assets/Models/Primitives/Sphere.FBX");
}

void ModuleGeometryManager::DrawCylinder()
{
	App->meshimporter->LoadFile_Mesh("Assets/Models/Primitives/Cylinder.FBX");
}



void ModuleGeometryManager::Transform_Mesh_Draw(Component_Transform* Transform)
{
	glPushMatrix();
	glMultMatrixf((GLfloat*)&Transform->Global_Matrix.Transposed()); // sHOULDNT THIS BE THE GLOBAL???

}



void ModuleGeometryManager::UpdateGameObjectTransforms()
{




}


void ModuleGeometryManager::DrawPlane()
{
	App->meshimporter->LoadFile_Mesh("Assets/Models/Primitives/Plane.FBX");
}

void ModuleGeometryManager::DrawMeshTextured(Game_Object* Object) //ESTO DIBUJA
{
	Component_Mesh* MeshVals = Object->Mesh;
	Component_Texture* TextVals = Object->Textures;
	Component_Transform* TransVals = Object->Transformations;

	if (App->scene->camera_culling == true)
	{
		if (!ContainsAABB(Object->Mesh->global_AABB))
		{
			return;
		}
	}

	if (MeshVals!=nullptr) {


		if (Object->is_Wireframed) {
			glLineWidth(3);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}



		if (TransVals != nullptr) {
			Transform_Mesh_Draw(TransVals);
		}

		glEnableClientState(GL_VERTEX_ARRAY);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);


		if (Object->is_Checkered == true) {

			glBindTexture(GL_TEXTURE_2D, App->textureImporter->TextureCheckers.texture_id);

			glBindBuffer(GL_ARRAY_BUFFER, MeshVals->Mesh->texcoords_id);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		}

		DrawVertexNormals(Object);
	

			if (TextVals != nullptr) {

				glColor4f(0.5f, 0.5f, 0.5f, 1.0f);

				if (TextVals->Texture->Colour.r != NULL) {
					


					glColor4f(TextVals->Texture->Colour.r, TextVals->Texture->Colour.g, TextVals->Texture->Colour.b, TextVals->Texture->Colour.a);
				}
				if (Object->Textures->is_Textured ) {

					glBindTexture(GL_TEXTURE_2D, TextVals->Texture->texture_id);
					glBindBuffer(GL_ARRAY_BUFFER, MeshVals->Mesh->texcoords_id);
					glTexCoordPointer(2, GL_FLOAT, 0, NULL);
				}
				
			}

		

		

		glBindBuffer(GL_ARRAY_BUFFER, MeshVals->Mesh->id_vertex);
		glVertexPointer(3, GL_FLOAT, 0, NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshVals->Mesh->id_index);
		glDrawElements(GL_TRIANGLES, MeshVals->Mesh->num_index, GL_UNSIGNED_INT, NULL);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


		glBindTexture(GL_TEXTURE_2D, 0);

		glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
		glPopMatrix();
		

	}
}

void ModuleGeometryManager::DrawVertexNormals(Game_Object* object)
{
	if (object->showVertexNormals == true)
	{
		float3 mid;
		float3 normal;

		for (int i = 0; i < object->Mesh->Mesh->num_index; i += 3)
		{
			float3 vert1 = object->Mesh->Mesh->vertex[object->Mesh->Mesh->index[i]];
			float3 vert2 = object->Mesh->Mesh->vertex[object->Mesh->Mesh->index[i + 1]];
			float3 vert3 = object->Mesh->Mesh->vertex[object->Mesh->Mesh->index[i + 2]];

			float3 vert1F = { vert1.x,vert1.y,vert1.z };
			float3 vert2F = { vert2.x,vert2.y,vert2.z };
			float3 vert3F = { vert3.x,vert3.y,vert3.z };


			mid = (vert1F + vert1F + vert1F) / 3;

			normal = Cross((vert2F - vert1F), (vert3F - vert1F));
			normal.Normalize();

			glLineWidth(1.5f);
			glBegin(GL_LINES);
			glVertex3f(mid.x, mid.y, mid.z);
			glVertex3f(mid.x + normal.x, mid.y + normal.y, mid.z + normal.z);
		}
		glEnd();
	}
}

//Cull
bool ModuleGeometryManager::ContainsAABB(const AABB& aabb) const
{
	vec corners[8];
	int corner_in = 0;
	aabb.GetCornerPoints(corners);

	Plane fru_planes[6];
	App->camera->scene_camera->frustum.GetPlanes(fru_planes);

	for (int p = 0; p < 6; ++p) {

		int in_count = 8;
		int iPtIn = 1;

		for (int i = 0; i < 8; ++i) {

			if (App->camera->scene_camera->frustum.GetPlane(p).IsOnPositiveSide(corners[i])) {

				iPtIn = 0;
				--in_count;
			}
		}

		if (in_count == 0)
			return false;

	}

	return true;
}


