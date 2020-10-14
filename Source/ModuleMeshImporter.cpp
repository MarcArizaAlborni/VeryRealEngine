#include "Globals.h"
#include "Application.h"
#include "ModuleMeshImporter.h"

#include "libraries/Assimp/Assimp/include/cimport.h"
#include "libraries/Assimp/Assimp/include/scene.h"
#include "libraries/Assimp/Assimp/include/postprocess.h"
#pragma comment (lib, "libraries/Assimp/Assimp/libx86/assimp.lib")

ModuleMeshImporter::ModuleMeshImporter(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleMeshImporter::~ModuleMeshImporter()
{}

// -----------------------------------------------------------------
bool ModuleMeshImporter::Start()
{
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleMeshImporter::CleanUp()
{
	return true;
}

// -----------------------------------------------------------------
update_status ModuleMeshImporter::Update(float dt)
{
	return UPDATE_CONTINUE;
}

void ModuleMeshImporter::LoadMesh(char* file_path)
{
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr &&  scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		// copy vertices
		MeshInfo* ourMesh = new MeshInfo();

		for (int i = 0; i < scene->mNumMeshes; ++i)
		{
			ourMesh->num_vertex = scene->mMeshes[i]->mNumVertices;
			ourMesh->vertex = new float[ourMesh->num_vertex * 3];
			memcpy(ourMesh->vertex, scene->mMeshes[i]->mVertices, sizeof(float) * ourMesh->num_vertex * 3);
			LOG("New mesh with %d vertices", ourMesh->num_vertex);
		}

		aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene % s", file_path);
}

