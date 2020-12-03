#include "ComponentMesh.h"
#include "Application.h"
#include "ModuleMeshImporter.h"

#include "GameObject.h"
#include "ComponentCamera.h"
#include "ComponentTexture.h"
#include "ComponentTransform.h"
#include "ModuleGeometryManager.h"
#include "libraries/Assimp/Assimp/include/cimport.h"
#include "libraries/Assimp/Assimp/include/scene.h"
#include "libraries/Assimp/Assimp/include/postprocess.h"
#pragma comment (lib, "libraries/Assimp/Assimp/libx86/assimp.lib")

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

Component_Mesh::Component_Mesh(Game_Object* ComponentOwner) :Component(ComponentOwner)
{
	Mesh = nullptr;
	File_Path = "none";
	type = Component_Types::Mesh;
	//owner = ComponentOwner;

}

Component_Mesh::Component_Mesh(Game_Object* ComponentOwner, const char* file_path, MeshInfo* meshInfo): Component(ComponentOwner)
{
	Mesh = meshInfo;
	File_Path = file_path;
	type = Component_Types::Mesh;
}
