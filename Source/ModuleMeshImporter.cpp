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
void ModuleMeshImporter::LoadMesh(const char* file_path)
{
	//LOGFIX("Importing Model %s...",file_path);	

	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes()) {

		aiNode* rootNodeScene=scene->mRootNode;

		//LoadNodeInfo(scene, rootNodeScene);

		bool ParentHasFound=false;

		if (scene->mNumMeshes > 1) {

			GameObject* ItemParentMesh = new GameObject();
			ItemParentMesh->is_Drawn = false;
			ItemParentMesh->is_EmptyParent = true;
			AddMeshToListMeshesOnScene(ItemParentMesh, false, NULL,true);
			ParentHasFound = true;

		}

		for (int i = 0; i < scene->mNumMeshes; ++i) {

			GameObject* ourGameObject = new GameObject();
			
			aiMesh* MeshToLoad = scene->mMeshes[i];

			////////////////// TRYING TO MAKE MODELS LOAD POSITIONS

			if (MeshToLoad->HasPositions()) {
				vec3 MedianPoint = { 0,0,0 };
				vec3 VertexPositionAdd = { 0,0,0 };

				for (int m = 0; m < MeshToLoad->mNumVertices; ++m) {

					VertexPositionAdd.x += MeshToLoad->mVertices->x;
					VertexPositionAdd.y += MeshToLoad->mVertices->y;
					VertexPositionAdd.z += MeshToLoad->mVertices->z;

				}

				MedianPoint.x = VertexPositionAdd.x / MeshToLoad->mNumVertices;
				MedianPoint.y = VertexPositionAdd.y / MeshToLoad->mNumVertices;
				MedianPoint.z = VertexPositionAdd.z / MeshToLoad->mNumVertices;

				ourGameObject->Mesh_Transform_Modifiers.VectorTranslation.x = MedianPoint.x;
				ourGameObject->Mesh_Transform_Modifiers.VectorTranslation.y = MedianPoint.y;
				ourGameObject->Mesh_Transform_Modifiers.VectorTranslation.z = MedianPoint.z;
				
			}
			

			/////////////////

			
			//ourGameObject->mesh_name=(std::string)MeshToLoad->mName;
			

			MeshToLoad->mNumVertices = scene->mMeshes[i]->mNumVertices;

			ourGameObject->MeshData.num_vertex = MeshToLoad->mNumVertices;

			ourGameObject->MeshData.vertex = new Vertex_Sub[ourGameObject->MeshData.num_vertex * 3];

			memcpy(ourGameObject->MeshData.vertex, MeshToLoad->mVertices, sizeof(float) * ourGameObject->MeshData.num_vertex * 3);
		
			if (MeshToLoad->HasFaces()) {

				ourGameObject->MeshData.num_index = MeshToLoad->mNumFaces * 3; //aixo

				int a = 0;

				ourGameObject->MeshData.index = new uint[ourGameObject->MeshData.num_index];

				for (int c = 0; c < MeshToLoad->mNumFaces; ++c) {

					//IF MESHES HAVE TRIS
					if (MeshToLoad->mFaces[c].mNumIndices == 3) {

						memcpy(&ourGameObject->MeshData.index[c * 3], MeshToLoad->mFaces[c].mIndices, 3 * sizeof(uint));
					}
				}
			}

			if (scene->mMeshes[i]->HasNormals()) {

				ourGameObject->MeshData.normals = new float[ourGameObject->MeshData.num_vertex * 3];
				memcpy(ourGameObject->MeshData.normals, scene->mMeshes[i]->mNormals, sizeof(float) * ourGameObject->MeshData.num_vertex* 3);
			}

			if (MeshToLoad->HasTextureCoords(0))
			{
				ourGameObject->MeshData.num_texcoords = MeshToLoad->mNumVertices;
				ourGameObject->MeshData.texcoords = new float[ourGameObject->MeshData.num_texcoords * 2];

				for (int Z = 0; Z< ourGameObject->MeshData.num_texcoords; ++Z) {

					ourGameObject->MeshData.texcoords[Z * 2] = MeshToLoad->mTextureCoords[0][Z].x;
					ourGameObject->MeshData.texcoords[(Z * 2) + 1] = MeshToLoad->mTextureCoords[0][Z].y;
				}
			}
			
			App->renderer3D->GenerateVertexBuffer(ourGameObject->MeshData.vertex, ourGameObject->MeshData.num_vertex, ourGameObject->MeshData.id_vertex);
			App->renderer3D->GenerateIndexBuffer(ourGameObject->MeshData.index, ourGameObject->MeshData.num_index, ourGameObject->MeshData.id_index);
			App->renderer3D->GenerateTextBuffer(ourGameObject->MeshData.texcoords, ourGameObject->MeshData.num_texcoords, ourGameObject->MeshData.texcoords_id);
			App->renderer3D->GenerateNormalBuffer(ourGameObject, *ourGameObject->MeshData.normals);


			if (ParentHasFound == true) {
				AddMeshToListMeshesOnScene(ourGameObject, true, NULL);
			}
			else {
				AddMeshToListMeshesOnScene(ourGameObject, false, NULL);
			}
		}
		//Free memory
		aiReleaseImport(scene);
	}

	
}



vec3 ModuleMeshImporter::LoadNodeInfo(const aiScene* scene, aiNode* rootNode)
{
	vec3 RetVec = { 0,0,0 };
	vec3 InitVec = { 1,1,1 };
	aiMatrix4x4 TransformationMatr;

	for (int i = 0; i < 4; ++i) {

		for (int b = 0; b < 4; ++b) {

			TransformationMatr[i][b] = rootNode->mTransformation[i][b];
		}
	}
	
	
	return RetVec;
}

void ModuleMeshImporter::AddMeshToListMeshesOnScene(GameObject* Object, bool isChildfrom, GameObject* parent,bool parentFound )
{
	if (isChildfrom == true) {

		
		
			std::vector<GameObject*>::reverse_iterator IteratorToAddParent = App->meshimporter->MeshesOnScene.rbegin();
			
			GameObject* itemParent = *IteratorToAddParent;

			int size2 = itemParent->ChildObjects.size() + 1;

			Object->item_id = size2;

			Object->is_Selected = false;
			Object->is_Textured = true;
			//Object->mesh_name = "Empty Parent";
			itemParent->ChildObjects.push_back(Object);
			
	}
	else {

		int size = MeshesOnScene.size() +1;

		Object->item_id = size;

		Object->is_Selected = false;
		Object->is_Textured = true;
		
		if (parentFound) {
			Object->mesh_name = "Empty Parent";
		}
		

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

