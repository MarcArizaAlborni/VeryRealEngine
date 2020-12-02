#include "ComponentMesh.h"
#include "Application.h"
#include "ModuleMeshImporter.h"

#include "GameObject.h"
#include "ComponentCamera.h"
#include "ComponentTexture.h"
#include "ComponentTransform.h"

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
}

void Component_Mesh::CleanUp()
{
}

void Component_Mesh::CreateMesh(MeshData* mesh)
{
	this->Mesh = mesh;
}

void Component_Mesh::CreatePath(std::string path)
{
	this->File_Path = path;
}

Component_Mesh::Component_Mesh(GameObject* owner_) : Component(owner)
{
	Mesh = nullptr;
	File_Path = "none";
	type = Component_Types::Mesh;


}

Component_Mesh::Component_Mesh(GameObject* owner_, const char* file_path, MeshData* meshInfo): Component(owner)
{
	Mesh = meshInfo;
	File_Path = file_path;
	type = Component_Types::Mesh;
}
