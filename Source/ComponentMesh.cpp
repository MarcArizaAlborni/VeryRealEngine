#include "ComponentMesh.h"
#include "Application.h"
#include "ModuleMeshImporter.h"
#include "Globals.h"
#include "GameObject.h"
#include "ComponentCamera.h"
#include "ComponentTexture.h"
#include "ComponentTransform.h"
#include "ModuleGeometryManager.h"
#include "libraries/Assimp/Assimp/include/cimport.h"
#include "libraries/Assimp/Assimp/include/scene.h"
#include "libraries/Assimp/Assimp/include/postprocess.h"
#pragma comment (lib, "libraries/Assimp/Assimp/libx86/assimp.lib")


Component_Mesh::Component_Mesh(Game_Object* ComponentOwner) :Component(ComponentOwner)
{
	Mesh = nullptr;
	File_Path = "none";
	type = Component_Types::Mesh;
	local_AABB.SetNegativeInfinity();
	global_AABB.SetNegativeInfinity();

}

Component_Mesh::Component_Mesh(Game_Object* ComponentOwner, const char* file_path, MeshInfo* meshInfo) : Component(ComponentOwner)
{
	Mesh = meshInfo;
	File_Path = file_path;
	type = Component_Types::Mesh;

	local_AABB.SetNegativeInfinity();
	global_AABB.SetNegativeInfinity();
}

void Component_Mesh::Enable()
{
}

void Component_Mesh::Disable()
{
}

void Component_Mesh::Update()
{
	Component_Mesh* MeshDraw = (Component_Mesh*)owner->GetComponent(Component_Types::Mesh);
	if (MeshDraw->is_Drawn) {
		App->geometrymanager->DrawMeshTextured(owner);

		DrawAABB();

		DrawOBB();
	}

	

}

void Component_Mesh::CleanUp()
{
}

MeshInfo* Component_Mesh::GetMesh() const
{
	return this->Mesh;
}

std::string Component_Mesh::GetPath() const
{
	return File_Path; 
}

void Component_Mesh::CreateMesh(MeshInfo* mesh)
{
	this->Mesh = mesh;
}

void Component_Mesh::CreatePath(std::string path)
{
	this->File_Path = path;
}

//------------ Bounding Boxes -------------------------//


void Component_Mesh::GenerateBBBufers()
{
	//Global AABB vertices
	glGenBuffers(1, &id_vertexAABB);
	glBindBuffer(GL_ARRAY_BUFFER, id_vertexAABB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float3) *vertices_AABB.size(), &vertices_AABB[0], GL_STATIC_DRAW);

	//Global AABB vertices index
	glGenBuffers(1, &id_indexAABB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indexAABB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * index_AABB.size(), &index_AABB[0], GL_STATIC_DRAW);

	//Global OBB vertices
	glGenBuffers(1, &id_vertexOBB);
	glBindBuffer(GL_ARRAY_BUFFER, id_vertexOBB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float3) * vertices_OBB.size(), &vertices_OBB[0], GL_STATIC_DRAW);

	//Global OBB vertices index
	glGenBuffers(1, &id_indexOBB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indexOBB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * index_OBB.size(), &index_OBB[0], GL_STATIC_DRAW);
}

AABB Component_Mesh::CreateLocalAABB()
{
	std::vector<float3> Vertices;

	for (int size = 0; size < Mesh->num_vertex; ++size) {

		Vertices.push_back(Mesh->vertex[size]);
	}

	//local_AABB.Enclose(Mesh->vertex, Mesh->num_vertex); // Falta arreglar vertex sub

	local_AABB.Enclose(Vertices.data(), Vertices.size());
	
	
	
	return local_AABB;
}

OBB Component_Mesh::GetOBB()
{
	global_OBB = local_AABB;
	/*mesh->global_OBB.Transform(transform->GetGlobalTransform());*/

	//Get Vertex and Index
	float3* aux_vertices = new float3[8];
	global_OBB.GetCornerPoints(aux_vertices);
	for (int i = 0; i < 8; i++)
	{
		vertices_OBB.push_back(aux_vertices[i]);
	}
	index_OBB = { 0,1, 0,4, 4,5, 5,1,	//Front
	3,2, 2,0, 0,1, 1,3,
	7,6, 6,2, 2,3, 3,7,
	6,4, 2,0,
	7,5, 3,1 };

	return global_OBB;
}

AABB Component_Mesh::GetGlobalAABB()
{
	global_AABB.Enclose(GetOBB());

	//Get Vertex and Index
	float3* aux_vertices = new float3[8];
	global_AABB.GetCornerPoints(aux_vertices);
	for (int i = 0; i < 8; i++)
	{
		vertices_AABB.push_back(aux_vertices[i]);
	}
	index_AABB = { 0,1, 0,4, 4,5, 5,1,	//Front
	3,2, 2,0, 0,1, 1,3,
	7,6, 6,2, 2,3, 3,7,
	6,4, 2,0,
	7,5, 3,1 };

	return global_AABB;
}

void Component_Mesh::DrawAABB()
{
	glColor3f(125, 125, 0);
	glLineWidth(2.0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, id_vertexAABB);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indexAABB);

	glDrawElements(GL_LINES,index_AABB.size(), GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);

	glLineWidth(1);
}

void Component_Mesh::DrawOBB()
{
	glColor3f(0, 200, 150);
	glLineWidth(2.0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, id_vertexOBB);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indexOBB);

	glDrawElements(GL_LINES, index_OBB.size(), GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);

	glLineWidth(1);
}

