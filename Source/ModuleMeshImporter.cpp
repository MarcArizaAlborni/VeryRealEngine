#include "Globals.h"
#include "Application.h"
#include "ModuleMeshImporter.h"

#include "libraries/Assimp/Assimp/include/cimport.h"
#include "libraries/Assimp/Assimp/include/scene.h"
#include "libraries/Assimp/Assimp/include/postprocess.h"
#pragma comment (lib, "libraries/Assimp/Assimp/libx86/assimp.lib")

#include "libraries/Glew/include/GL/glew.h"

#include <gl/GLU.h>

ModuleMeshImporter::ModuleMeshImporter(Application* app, const char* name, bool start_enabled) : Module(app,"Importer", start_enabled)
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

// Load a mesh with index and vertex
void ModuleMeshImporter::LoadMesh(char* file_path)
{
	LOGFIX("Importing Model...");	

	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes()) {

		//MeshInfo* ourMesh = new MeshInfo();
		GameObject* ourGameObject = new GameObject();
		
		for (int i = 0; i < scene->mNumMeshes; ++i) {

			aiMesh* MeshToLoad = scene->mMeshes[i];

			ourGameObject->MeshData.num_vertex = MeshToLoad->mNumVertices;
			ourGameObject->MeshData.vertex = new Vertex_Sub[ourGameObject->MeshData.num_vertex * 3];
			//memcpy(ourGameObject->MeshData.vertex, MeshToLoad->mVertices, sizeof(float) * ourGameObject->MeshData.num_vertex * 3);

			for (uint X = 0; X < MeshToLoad->mNumVertices; ++X)
			{
				ourGameObject->MeshData.vertex[X].x = MeshToLoad->mVertices[X].x;
				ourGameObject->MeshData.vertex[X].y = MeshToLoad->mVertices[X].y;
				ourGameObject->MeshData.vertex[X].z = MeshToLoad->mVertices[X].z;
			}

		
			if (MeshToLoad->HasFaces()) {

				ourGameObject->MeshData.num_index = MeshToLoad->mNumFaces * 3;
				ourGameObject->MeshData.index = new uint[ourGameObject->MeshData.num_index];

				for (int c = 0; c < MeshToLoad->mNumFaces; ++c) {

					//IF MESHES HAVE TRIS
					if (MeshToLoad->mFaces[c].mNumIndices == 3) {

						memcpy(&ourGameObject->MeshData.index[c * 3], MeshToLoad->mFaces[c].mIndices, 3 * sizeof(uint));
					}

				}

			}

			if (MeshToLoad->HasTextureCoords(0))
			{
				ourGameObject->MeshData.num_texcoords = MeshToLoad->mNumVertices;
				ourGameObject->MeshData.texcoords = new float[ourGameObject->MeshData.num_texcoords * 2];

				for (int Z = 0; Z< ourGameObject->MeshData.num_texcoords; ++Z) {

					ourGameObject->MeshData.texcoords[Z * 2] = MeshToLoad->mTextureCoords[0][Z].x;
					ourGameObject->MeshData.texcoords[(Z * 2)+1] = MeshToLoad->mTextureCoords[0][Z].y;

				}
				//memcpy(ourGameObject->MeshData.texcoords, MeshToLoad->mTextureCoords[0], sizeof(float) * ourGameObject->MeshData.num_texcoords * 2);

				/*glGenBuffers(1, (GLuint*)&ourGameObject->MeshData.texcoords_id);
				glBindBuffer(GL_ARRAY_BUFFER, ourGameObject->MeshData.texcoords_id);
				glBufferData(GL_ARRAY_BUFFER, sizeof(uint) * ourGameObject->MeshData.num_texcoords * 2, ourGameObject->MeshData.texcoords, GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);*/
			}
			//CALLED TO CREATE A VERTEX BUFFER SO WE CAN DRAW MULTIPLE OBJECTS
			//App->renderer3D->GenerateVertexBuffer(ourGameObject->MeshData.id_vertex, ourGameObject->MeshData.num_vertex, ourGameObject->MeshData.vertex);

			//App->renderer3D->GenerateVertexTexBuffer(ourGameObject->MeshData.id_index, ourGameObject->MeshData.num_index, ourGameObject->MeshData.vertex);

			//if (ourGameObject->MeshData.index != nullptr) {
			//	//siCalled to create an Index Buffer so we can draw multiple objects
			//	App->renderer3D->GenerateIndexBuffer(ourGameObject->MeshData.id_index, ourGameObject->MeshData.num_index, ourGameObject->MeshData.index);
			//}

			//App->renderer3D->GenerateVertexBuffer(ourGameObject->MeshData.texcoords_id, ourGameObject->MeshData.num_texcoords * 2, ourGameObject->MeshData.texcoords);

			App->renderer3D->GenerateVertexBuffer(ourGameObject->MeshData.vertex, ourGameObject->MeshData.num_vertex, ourGameObject->MeshData.id_vertex);
			App->renderer3D->GenerateIndexBuffer(ourGameObject->MeshData.index, ourGameObject->MeshData.num_index, ourGameObject->MeshData.id_index);
			App->renderer3D->GenerateTextBuffer(ourGameObject->MeshData.texcoords, ourGameObject->MeshData.num_texcoords, ourGameObject->MeshData.texcoords_id);

			
			//Add to mesh list for when we draw each mesh
			bool ParentFound = false;
			std::vector<GameObject*>::iterator IteratorToAddMesh = App->meshimporter->MeshesOnScene.begin();
			for (int count = 0; count < MeshesOnScene.size(); ++count) {

				
				GameObject* meshParent = *IteratorToAddMesh;

				if (meshParent->is_Selected == true) {
					ParentFound = true;
					AddMeshToListMeshesOnScene(ourGameObject, true, meshParent);
					count = App->meshimporter->MeshesOnScene.size();
				}
				else {
					ParentFound = false;
					++IteratorToAddMesh;

				}
			}

			
			if (ParentFound == false) {
				AddMeshToListMeshesOnScene(ourGameObject, false, NULL);
			}
		}

		//Free memory
		aiReleaseImport(scene);
	}

	
}



void ModuleMeshImporter::AddMeshToListMeshesOnScene(GameObject* Object, bool isChildfrom, GameObject* parent)
{
	if (isChildfrom == true && parent !=NULL) {
		
			std::vector<GameObject*>::iterator IteratorToAdd = App->meshimporter->MeshesOnScene.begin();
			for (int count = 0; count < MeshesOnScene.size(); ++count) {

				GameObject* parentObj = *IteratorToAdd;
				if (parent->item_id == parentObj->item_id) {

					parentObj->ChildObjects.push_back(Object);
				}
			}
	}
	else {
		int size = MeshesOnScene.size();

		Object->item_id = size;

		Object->is_Selected = false;
		Object->is_Textured = false;
		
		

		MeshesOnScene.push_back(Object);
	}



}

void ModuleMeshImporter::CreateConsolelog(const char file[], int line, const char* format, ...)
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

