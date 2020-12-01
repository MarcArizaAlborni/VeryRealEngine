#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleGeometryManager.h"
#include "ModuleTextureImporter.h"
#include "ModuleEditor.h"
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

	UpdateGameObjectTransforms();


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

	
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
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

void ModuleGeometryManager::Transform_Mesh_Draw(GameObject* mesh)
{
	glPushMatrix();
	glMultMatrixf((GLfloat*)&mesh->Mesh_Transform_Modifiers.WorldMatrix.Transposed());

}



void ModuleGeometryManager::UpdateGameObjectTransforms()
{

	std::vector<GameObject*>::iterator It = App->meshimporter->MeshesOnScene.begin();
	for (int i = 0; i < App->meshimporter->MeshesOnScene.size(); ++i) {
		GameObject* Mesh = *It;

		if (Mesh->is_EmptyParent == false) {

			if (Mesh->Mesh_Transform_Modifiers.TransformsUpdated) {

				float3 Pos = { Mesh->Mesh_Transform_Modifiers.VectorTranslation.x,Mesh->Mesh_Transform_Modifiers.VectorTranslation.y,Mesh->Mesh_Transform_Modifiers.VectorTranslation.z };
				float3 Scal = { Mesh->Mesh_Transform_Modifiers.VectorScale.x,Mesh->Mesh_Transform_Modifiers.VectorScale.y,Mesh->Mesh_Transform_Modifiers.VectorScale.z };
				Quat Rot = { Mesh->Mesh_Transform_Modifiers.VectorRotation.x,Mesh->Mesh_Transform_Modifiers.VectorRotation.y,Mesh->Mesh_Transform_Modifiers.VectorRotation.z,Mesh->Mesh_Transform_Modifiers.VectorRotation.angle };

				//Rot.x = Mesh->Mesh_Transform_Modifiers.VectorRotation.x;
				//Rot.y = Mesh->Mesh_Transform_Modifiers.VectorRotation.y;
				//Rot.z = Mesh->Mesh_Transform_Modifiers.VectorRotation.z;
				//Rot.w = Mesh->Mesh_Transform_Modifiers.VectorRotation.angle;

				

				Mesh->Mesh_Transform_Modifiers.WorldMatrix = float4x4::FromTRS(Pos, Rot, Scal);

				Mesh->Mesh_Transform_Modifiers.LocalTranslation = Pos;
				Mesh->Mesh_Transform_Modifiers.LocalScale = Scal;
				Mesh->Mesh_Transform_Modifiers.LocalRotation = Rot;

				Mesh->Mesh_Transform_Modifiers.TransformsUpdated = false;

			}
		}
		else {


			if (Mesh->Mesh_Transform_Modifiers.TransformsUpdated) {

				float3 Pos;
				Pos=float3::zero;
				float3 Scal;
				Scal = float3::one;
				Quat Rot;
				
				if (Mesh->ChildObjects.size() == 33) {
					Rot = App->meshimporter->RotationValue;
				}
				else {
					Rot = Quat::identity;
				}

				Quat Rot2 = { Mesh->Mesh_Transform_Modifiers.VectorRotation.x,Mesh->Mesh_Transform_Modifiers.VectorRotation.y,Mesh->Mesh_Transform_Modifiers.VectorRotation.z,Mesh->Mesh_Transform_Modifiers.VectorRotation.angle };
				
				

				

				Mesh->Mesh_Transform_Modifiers.WorldMatrix = float4x4::FromTRS(Pos, Rot, Scal);

				Mesh->Mesh_Transform_Modifiers.WorldTranslation = Pos;
				Mesh->Mesh_Transform_Modifiers.WorldScale = Scal;
				Mesh->Mesh_Transform_Modifiers.WorldRotation = Rot;

				
				

				Mesh->Mesh_Transform_Modifiers.TransformsUpdated = false;

			}


		}
		std::vector<GameObject*>::iterator ItChild = Mesh->ChildObjects.begin();
		for (int a = 0; a < Mesh->ChildObjects.size();++a) {

			
		
			GameObject* MeshChild = *ItChild;

			if (MeshChild->Mesh_Transform_Modifiers.TransformsUpdated) {

				float3 Pos = { MeshChild->Mesh_Transform_Modifiers.VectorTranslation.x,MeshChild->Mesh_Transform_Modifiers.VectorTranslation.y,MeshChild->Mesh_Transform_Modifiers.VectorTranslation.z };
				float3 Scal = { MeshChild->Mesh_Transform_Modifiers.VectorScale.x,MeshChild->Mesh_Transform_Modifiers.VectorScale.y,MeshChild->Mesh_Transform_Modifiers.VectorScale.z };
				Quat Rot;

				Rot.x = MeshChild->Mesh_Transform_Modifiers.VectorRotation.x;
				Rot.y = MeshChild->Mesh_Transform_Modifiers.VectorRotation.y;
				Rot.z = MeshChild->Mesh_Transform_Modifiers.VectorRotation.z;
				Rot.w = MeshChild->Mesh_Transform_Modifiers.VectorRotation.angle;


				MeshChild->Mesh_Transform_Modifiers.LocalMatrix = float4x4::FromTRS(Pos, Rot, Scal);

				MeshChild->Mesh_Transform_Modifiers.LocalTranslation = Pos;
				MeshChild->Mesh_Transform_Modifiers.LocalScale = Scal;
				MeshChild->Mesh_Transform_Modifiers.LocalRotation = Rot;


				MeshChild->Mesh_Transform_Modifiers.WorldMatrix = Mesh->Mesh_Transform_Modifiers.WorldMatrix * MeshChild->Mesh_Transform_Modifiers.LocalMatrix;


				MeshChild->Mesh_Transform_Modifiers.TransformsUpdated = false;

			}

			++ItChild;

		}

		++It;

	}

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

	//glColor4f(0.49f, 0.74f, 0.24f, 1.0f);

	if (mesh->TextureData.Colour.r != NULL) {
		//glColor4f(0.49f, 0.74f, 0.24f, 1.0f);

		mesh->TextureData.Colour.r;
	    glColor4f(mesh->TextureData.Colour.r, mesh->TextureData.Colour.g, mesh->TextureData.Colour.b, mesh->TextureData.Colour.a);
	}



	Transform_Mesh_Draw(mesh);

	glEnableClientState(GL_VERTEX_ARRAY);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	if (mesh->is_Checkered == true) {

		glBindTexture(GL_TEXTURE_2D, App->textureImporter->TextureCheckers.texture_id);

		glBindBuffer(GL_ARRAY_BUFFER, mesh->MeshData.texcoords_id);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	}

	DrawVertexNormals(mesh);

	if (mesh->MeshData.texcoords != NULL) {
		if (mesh->is_Textured == true) {

			glBindTexture(GL_TEXTURE_2D, mesh->TextureData.texture_id);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->MeshData.texcoords_id);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		}
		else {
			
			
		}
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

	//glColor4f(mesh->TextureData.Colour.r, mesh->TextureData.Colour.g, mesh->TextureData.Colour.b, mesh->TextureData.Colour.a);
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
}

void ModuleGeometryManager::DrawVertexNormals(GameObject* object)
{
	if (object->showVertexNormals == true)
	{
		float3 mid;
		float3 normal;

		for (int i = 0; i < object->MeshData.num_index; i += 3)
		{
			Vertex_Sub vert1 = object->MeshData.vertex[object->MeshData.index[i]];
			Vertex_Sub vert2 = object->MeshData.vertex[object->MeshData.index[i + 1]];
			Vertex_Sub vert3 = object->MeshData.vertex[object->MeshData.index[i + 2]];

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

	App->editor->ConsoleLogs.push_back(tmp_string2);
}



//TRANSFORMS



// 1. TENEMOS LOS 3 VECTORES

// 2. Float4x4:: FromTRS-> we get a 4x4 matrix and we set the local transforms

// 3. Update worlds transforms using world from parent

// 4.glPushpatrix & GLmultMatrix.transposed(); (USE THE ONE WITH FINAL D) USE MATRIX FROM WORLD 






//IMPORT VECTORS

//FROM TRS

//PASAR MATRIX 4X4 A LOCAL TRANSFORM DEL OBJETO

//GENERAR WORLD TRANSFORM CON WORLD TRANSFORM DEL PARENT * LOCAL DEL MESH

//MULTIMATRIX.TRANSPOSED();