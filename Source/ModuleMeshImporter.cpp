#include "Globals.h"
#include "Application.h"
#include "ModuleMeshImporter.h"
#include "ModuleRenderer3D.h"
#include "FileSystem.h"
#include "ModuleEditor.h"

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
void ModuleMeshImporter::LoadMesh(const char* file_path,bool LoadfromWAF)
{
	//LOGFIX("Importing Model %s...",file_path);	

	bool ReadyToLoad = false;
	const aiScene* scene;
	if (LoadfromWAF == true) {
		const char* path = "Assets/Models/House/BakerHouse.fbx";
		scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	}
	else {
		scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	}

	if (LoadfromWAF == false) {
		
		if (scene != nullptr) {
			ReadyToLoad = true;
		}
	}

	if (LoadfromWAF == true) {
		ReadyToLoad = true;
	}

	if (ReadyToLoad == true) {

		if (LoadfromWAF == false) {
			aiNode* rootNodeScene = scene->mRootNode;
		}

		//THE ERRROR IS EITHER WRITING THE INFORMATION OR THE LOOP 

		//StoredFile InformationToSend;
		//InformationToSend.Scene = scene;
		//int ID_Detected;
		//StoredFile* FileToLoad = new StoredFile();
		//
		//ID_Detected =App->filemanager->CheckExistence_Mesh(InformationToSend);
		//if (ID_Detected == 0){ //IF IT HAS NOT BEEN DETECTED

		//	
		//	App->filemanager->GenerateLibraryFile_Mesh(App->GiveRandomNum_Undefined(), InformationToSend);
		//	
		//}
		//else{// IF IT HAS BEEN DETECTED
		//	InformationToSend = App->filemanager->LoadLibraryFile_Mesh(ID_Detected);
		//	scene = InformationToSend.Scene;
		//}


		LoadedFile* InformationToRecieve;

		int TemporaryID = -1; // This is only temporary, should not be used this way

		if (LoadfromWAF == false) {

			StoredFile InformationToSend;
			InformationToSend.Scene = scene;
			App->filemanager->SaveInformationFile_Mesh(TemporaryID = App->GiveRandomNum_Undefined(), InformationToSend);

		}
		else { TemporaryID = 172; }

		InformationToRecieve = App->filemanager->LoadInformationFile_Mesh(TemporaryID);
		//InformationToRecieve = App->filemanager->LoadedResources.back();

		bool ParentHasFound = false;

		if (LoadfromWAF == true) {

			if (InformationToRecieve->AmountMeshes > 1) {

				GameObject* ItemParentMesh = new GameObject();
				ItemParentMesh->is_Drawn = true;
				ItemParentMesh->is_EmptyParent = true;
				AddMeshToListMeshesOnScene(ItemParentMesh, false, NULL, true);
				ParentHasFound = true;

			}

			for (int i = 0; i < InformationToRecieve->AmountMeshes; ++i) {

				GameObject* ourGameObject = new GameObject();
				aiMesh* MeshToLoad = scene->mMeshes[i];
				
				

				
				

				for (int d = 0; d < InformationToRecieve->MeshInfo[i].AmountFaces; ++d) {

					for (int c = 0; c < InformationToRecieve->MeshInfo[i].FaceInfo[d].AmountIndex; ++c) {

						uint value;

						//InformationToRecieve->MeshInfo[i].FaceInfo[d];
						//MeshToLoad->mFaces[d].mIndices[c] = InformationToRecieve->MeshInfo[i].FaceInfo[d].Index[c];

					}

					//MeshToLoad->mFaces[d].mNumIndices = InformationToRecieve->MeshInfo[i].FaceInfo[d].AmountIndex;
				}

				ourGameObject->MeshData.num_vertex = InformationToRecieve->MeshInfo[i].AmountVertex;

				ourGameObject->MeshData.vertex = new Vertex_Sub[ourGameObject->MeshData.num_vertex * 3];

				for (int h = 0; h < InformationToRecieve->MeshInfo[i].AmountVertex; ++h) {
				
					ourGameObject->MeshData.vertex[h] = InformationToRecieve->MeshInfo[i].Vertex[h];
				}

				

				

				//memcpy(ourGameObject->MeshData.vertex, MeshToLoad->mVertices, sizeof(float) * ourGameObject->MeshData.num_vertex * 3);
				
				if (InformationToRecieve->MeshInfo[i].AmountFaces!=0) {

					ourGameObject->MeshData.num_index = InformationToRecieve->MeshInfo[i].AmountFaces*3; //aixo

					int a = 0;

					ourGameObject->MeshData.index = new uint[ourGameObject->MeshData.num_index];

					for (int c = 0; c < InformationToRecieve->MeshInfo[i].AmountFaces; ++c) {

						//IF MESHES HAVE TRIS
						if (InformationToRecieve->MeshInfo[i].FaceInfo[c].AmountIndex== 3) {

							for (int fi = 0; fi < InformationToRecieve->MeshInfo[i].FaceInfo[c].AmountIndex; ++fi) {

								//ourGameObject->MeshData.index[c * 3] = InformationToRecieve->MeshInfo[i].FaceInfo[c].Index[fi];
								memcpy(&InformationToRecieve->MeshInfo[i].FaceInfo[c].Index, &MeshToLoad->mFaces[c].mIndices, 3 * sizeof(uint));
								MeshToLoad->mFaces[c].mIndices[fi];
								MeshToLoad->mFaces[c].mIndices[fi + 1];
								MeshToLoad->mFaces[c].mIndices[fi + 2];
								memcpy(&ourGameObject->MeshData.index[c * 3], &InformationToRecieve->MeshInfo[i].FaceInfo[c].Index, 3 * sizeof(uint));
							}
							
						}
					}
				}

				if (InformationToRecieve->MeshInfo[i].Normal.size()!=0) {

					ourGameObject->MeshData.normals = new Vertex_Sub[ourGameObject->MeshData.num_vertex * 3];

					for (int mf = 0; mf < InformationToRecieve->MeshInfo[i].AmountVertex; ++mf) {
						ourGameObject->MeshData.normals[mf] = InformationToRecieve->MeshInfo[i].Normal[mf];
					}
					
					//memcpy(ourGameObject->MeshData.normals, scene->mMeshes[i]->mNormals, sizeof(float) * ourGameObject->MeshData.num_vertex * 3);
				}

				if (InformationToRecieve->MeshInfo[i].TextureCoords.size()!=0)
				{
					ourGameObject->MeshData.num_texcoords = InformationToRecieve->MeshInfo[i].AmountVertex;
					ourGameObject->MeshData.texcoords = new float[ourGameObject->MeshData.num_texcoords * 2];

					for (int Z = 0; Z < ourGameObject->MeshData.num_texcoords; ++Z) {

						ourGameObject->MeshData.texcoords[Z * 2] = InformationToRecieve->MeshInfo[i].TextureCoords[Z].x; //??????
						ourGameObject->MeshData.texcoords[(Z * 2) + 1] = InformationToRecieve->MeshInfo[i].TextureCoords[Z].y;
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
		else {


			if (InformationToRecieve->AmountMeshes > 1) {

				GameObject* ItemParentMesh = new GameObject();
				ItemParentMesh->is_Drawn = true;
				ItemParentMesh->is_EmptyParent = true;
				AddMeshToListMeshesOnScene(ItemParentMesh, false, NULL, true);
				ParentHasFound = true;

			}

			for (int i = 0; i < InformationToRecieve->AmountMeshes; ++i) {

				GameObject* ourGameObject = new GameObject();

				aiMesh* MeshToLoad = scene->mMeshes[i];

				MeshToLoad->mNumVertices = InformationToRecieve->MeshInfo[i].AmountVertex;
				MeshToLoad->mNumFaces = InformationToRecieve->MeshInfo[i].AmountFaces;

				for (int d = 0; d < InformationToRecieve->MeshInfo[i].AmountFaces; ++d) {

					for (int c = 0; c < MeshToLoad->mFaces[d].mNumIndices; ++c) {

						uint value;

						MeshToLoad->mFaces[d].mIndices[c] = InformationToRecieve->MeshInfo[i].FaceInfo[d].Index[c];

					}

					MeshToLoad->mFaces[d].mNumIndices = InformationToRecieve->MeshInfo[i].FaceInfo[d].AmountIndex;
				}

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

					ourGameObject->MeshData.normals = new Vertex_Sub[ourGameObject->MeshData.num_vertex * 3];
					memcpy(ourGameObject->MeshData.normals, scene->mMeshes[i]->mNormals, sizeof(float) * ourGameObject->MeshData.num_vertex * 3);
				}

				if (MeshToLoad->HasTextureCoords(0))
				{
					ourGameObject->MeshData.num_texcoords = MeshToLoad->mNumVertices;
					ourGameObject->MeshData.texcoords = new float[ourGameObject->MeshData.num_texcoords * 2];

					for (int Z = 0; Z < ourGameObject->MeshData.num_texcoords; ++Z) {

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


	App->editor->ConsoleLogs.push_back(tmp_string2);
}

