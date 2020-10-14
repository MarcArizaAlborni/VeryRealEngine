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

MeshInfo* ModuleMeshImporter::LoadMesh(char* file_path)
{
	MeshInfo* ourMesh = new MeshInfo();

	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr &&  scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		// copy vertices
		
		for (int i = 0; i < scene->mNumMeshes; ++i)
		{
			ourMesh->num_vertex = scene->mMeshes[i]->mNumVertices;
			ourMesh->vertex = new float[ourMesh->num_vertex * 3.0f];
			memcpy(ourMesh->vertex, scene->mMeshes[i]->mVertices, sizeof(float) * ourMesh->num_vertex * 3);
			LOG("New mesh with %d vertices", ourMesh->num_vertex);

			if (scene->mMeshes[i]->HasFaces())
			{
				ourMesh->num_index = scene->mMeshes[i]->mNumFaces * 3;
				ourMesh->index = new uint[ourMesh->num_index];

				for (uint s = 0; s < scene->mMeshes[i]->mNumFaces; s++)
				{
					if (scene->mMeshes[i]->mFaces[s].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else
						memcpy(&ourMesh->index[s*3], scene->mMeshes[i]->mFaces[s].mIndices, 3 * sizeof(uint));
				}
			}
		}

		aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene % s", file_path);

	return ourMesh;
}

