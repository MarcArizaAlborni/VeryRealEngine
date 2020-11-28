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
#pragma comment (lib, "libraries/PhysFS/include/physfs.h")
#include "libraries/PhysFS/include/physfs.h"

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
				ItemParentMesh->path = file_path;
				AddMeshToListMeshesOnScene(ItemParentMesh, false, NULL, true);
				ParentHasFound = true;

			}

			for (int i = 0; i < InformationToRecieve->AmountMeshes; ++i) {

				GameObject* ourGameObject = new GameObject();
				//aiMesh* MeshToLoad = scene->mMeshes[i];
				ourGameObject->path = file_path;
				
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

							unsigned int IndexCopy[3];


							//IndexCopy = new uint[ourGameObject->MeshData.num_index];


							IndexCopy[0] = InformationToRecieve->MeshInfo[i].FaceInfo[c].indexV1;
							IndexCopy[1] = InformationToRecieve->MeshInfo[i].FaceInfo[c].indexV2;
							IndexCopy[2] = InformationToRecieve->MeshInfo[i].FaceInfo[c].indexV3;
							
							memcpy(&ourGameObject->MeshData.index[c * 3], IndexCopy, 3 * sizeof(uint));
							
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

void ModuleMeshImporter::LoadFile_Mesh(const char* file_path)
{
	
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

	scene->mMeshes[1];
	
	aiNode* Node;

	PreviousListSize = App->meshimporter->MeshesOnScene.size();

	ProcessNode(file_path, scene, scene->mRootNode, nullptr);
	
	//CreateGameObjectsNodeMap(scene, file_path);
	
	if (ChildrenToAddList.size() == 1) {

		CreateChildsWithParent(false);
	}
	else if (ChildrenToAddList.size() > 1) {

		CreateChildsWithParent(true);
	}

	ChildrenToAddList.clear();

	//ParentCreatedChildren(ChildrenAmount);

	ChildrenAmount = -1;
	
	aiReleaseImport(scene);
	
	aiMaterial* a; 
}

void ModuleMeshImporter::ProcessNode(const char* file_path, const aiScene* scene, const aiNode* node,GameObject* item)
{
	//Parent should be called into this function to create childs?
	
	for (int size = 0; size < node->mNumMeshes; ++size) {

		NodeMap NodeToAdd;
		aiMesh* MeshLoaded = scene->mMeshes[node->mMeshes[size]];
		
			NodeToAdd.ScenePositionArray = node->mMeshes[size];

			
			if (MeshLoaded->mMaterialIndex >= 0) {

				aiMaterial* MaterialLoaded;
				MaterialLoaded = scene->mMaterials[MeshLoaded->mMaterialIndex];
				NodeToAdd.MaterialPositionArray = MeshLoaded->mMaterialIndex;
				NodeToAdd.Name = node->mName.C_Str();

				aiString PathMaterial;
				if ((MaterialLoaded->GetTexture(aiTextureType_DIFFUSE, 0, &PathMaterial) == AI_SUCCESS)) {
					NodeToAdd.MaterialPath = PathMaterial.C_Str();
				}

				
		    }


	    CreateGameObjectsByNodes(scene, file_path, MeshLoaded,node, NodeToAdd);

		if (NodeToAdd.ScenePositionArray != -1) {
			NodeMapList.push_back(NodeToAdd);
		}
		
	}

	for (int i = 0; i < node->mNumChildren; ++i) {

		ProcessNode(file_path, scene, node->mChildren[i], nullptr);

	}

}

void ModuleMeshImporter::CreateChildsWithParent(bool WithParent)
{

	if (WithParent == true) {

		GameObject* ItemParentMesh = new GameObject();
		ItemParentMesh->is_Drawn = true;
		ItemParentMesh->is_EmptyParent = true;
		ItemParentMesh->path = "path";
		ItemParentMesh->is_FamilyMove = true;
		AddMeshToListMeshesOnScene(ItemParentMesh, false, NULL, true);

		std::vector<GameObject*>::iterator IteratorChild = ChildrenToAddList.begin();

		for (int i = 0; i < ChildrenToAddList.size(); ++i) {


			GameObject* Mesh = *IteratorChild;

			Mesh->item_id = i+1;

			App->meshimporter->MeshesOnScene.back()->ChildObjects.push_back(Mesh);

			++IteratorChild;

		}

		


	}
	else {

		std::vector<GameObject*>::iterator IteratorChild = ChildrenToAddList.begin();

		App->meshimporter->MeshesOnScene.push_back(*IteratorChild);
		

	}


}

void ModuleMeshImporter::LoadSceneMesh(const aiScene* scene, int mesh_position)
{
}

void ModuleMeshImporter::CreateGameObjectsNodeMap(const aiScene* scene, const char* file_path)
{
	NodeMapList.size();

	bool ParentIsFound = false;

	if (NodeMapList.size() > 1) {

		GameObject* ItemParentMesh = new GameObject();
		ItemParentMesh->is_Drawn = true;
		ItemParentMesh->is_EmptyParent = true;
		ItemParentMesh->path = "path";
		AddMeshToListMeshesOnScene(ItemParentMesh, false, NULL, true);
		ParentIsFound = true;

	}

	//THIS HAS TO BE CHANGED


	//for (int i = 0; i < 4; ++i) {

	 for (int i = 0; i < NodeMapList.size(); ++i) {
			
			GameObject* ourGameObject = new GameObject();

			//The error comes from the dummies that are added to the NodeMapList.
			int positionArray = NodeMapList.at(i).ScenePositionArray;

			aiMesh* MeshToLoad = scene->mMeshes[positionArray];

			ourGameObject->mesh_name = NodeMapList.at(i).Name;
		   // MeshToLoad = scene->mMeshes[i];

			for (int d = 0; d < MeshToLoad->mNumFaces; ++d) {


				MeshToLoad->mFaces[d].mNumIndices;
			}

			MeshToLoad->mNumVertices = scene->mMeshes[positionArray]->mNumVertices;

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

						unsigned int IndexCopy[3];

						memcpy(&ourGameObject->MeshData.index[c * 3], MeshToLoad->mFaces[c].mIndices, 3 * sizeof(uint));
					}
				}
			}

			if (scene->mMeshes[positionArray]->HasNormals()) {

				ourGameObject->MeshData.normals = new Vertex_Sub[ourGameObject->MeshData.num_vertex * 3];
				memcpy(ourGameObject->MeshData.normals, scene->mMeshes[positionArray]->mNormals, sizeof(float) * ourGameObject->MeshData.num_vertex * 3);
			}

			if (MeshToLoad->HasTextureCoords(0))
			{
				ourGameObject->MeshData.num_texcoords = MeshToLoad->mNumVertices;
				ourGameObject->MeshData.texcoords = new float[ourGameObject->MeshData.num_vertex * 2];

				
				for (int Z = 0; Z < ourGameObject->MeshData.num_texcoords; ++Z) {

					ourGameObject->MeshData.texcoords[Z * 2] = MeshToLoad->mTextureCoords[0][Z].x;
					ourGameObject->MeshData.texcoords[Z * 2 + 1] = MeshToLoad->mTextureCoords[0][Z].y;
				}
			}

			App->renderer3D->GenerateVertexBuffer(ourGameObject->MeshData.vertex, ourGameObject->MeshData.num_vertex, ourGameObject->MeshData.id_vertex);
			App->renderer3D->GenerateIndexBuffer(ourGameObject->MeshData.index, ourGameObject->MeshData.num_index, ourGameObject->MeshData.id_index);
			if (ourGameObject->MeshData.texcoords != NULL) {
				App->renderer3D->GenerateTextBuffer(ourGameObject->MeshData.texcoords, ourGameObject->MeshData.num_texcoords, ourGameObject->MeshData.texcoords_id);
			}
			App->renderer3D->GenerateNormalBuffer(ourGameObject, *ourGameObject->MeshData.normals);

			
			
			
			std::string PathToLoad = App->textureImporter->CreateTexturesNodeMap(NodeMapList.at(positionArray), scene, file_path).texture_path.c_str();

			

			if(PathToLoad!=""){

			    LOGFIX(PathToLoad.c_str());
			
				ourGameObject->TextureData = App->textureImporter->LoadTextureImage(PathToLoad.c_str());
			}
			else {

				LOGFIX("Mesh Node Has No Texture");
			}
			
			
			if (ParentIsFound == true) {

				AddMeshToListMeshesOnScene(ourGameObject, true, NULL);
			}
			else {
				AddMeshToListMeshesOnScene(ourGameObject, false, NULL);
			}
		
	}
		//Free memory
		aiReleaseImport(scene);
	
	NodeMapList.clear();
}

void ModuleMeshImporter::CreateGameObjectsByNodes(const aiScene* scene, const char* file_path, aiMesh* meshLoad, const aiNode* node,NodeMap map)
{

	NodeMapList.size();

	bool ParentIsFound = false;

	
		GameObject* ourGameObject = new GameObject();

		
		for (int d = 0; d < meshLoad->mNumFaces; ++d) {


			meshLoad->mFaces[d].mNumIndices;
		}

		
		ourGameObject->MeshData.num_vertex = meshLoad->mNumVertices;

		ourGameObject->MeshData.vertex = new Vertex_Sub[ourGameObject->MeshData.num_vertex * 3];

		memcpy(ourGameObject->MeshData.vertex, meshLoad->mVertices, sizeof(float) * ourGameObject->MeshData.num_vertex * 3);

		if (meshLoad->HasFaces()) {

			ourGameObject->MeshData.num_index = meshLoad->mNumFaces * 3; //aixo

			int a = 0;

			ourGameObject->MeshData.index = new uint[ourGameObject->MeshData.num_index];

			for (int c = 0; c < meshLoad->mNumFaces; ++c) {

				//IF MESHES HAVE TRIS
				if (meshLoad->mFaces[c].mNumIndices == 3) {

					unsigned int IndexCopy[3];

					memcpy(&ourGameObject->MeshData.index[c * 3], meshLoad->mFaces[c].mIndices, 3 * sizeof(uint));
				}
			}
		}

		if (meshLoad->HasNormals()) {

			ourGameObject->MeshData.normals = new Vertex_Sub[ourGameObject->MeshData.num_vertex * 3];
			memcpy(ourGameObject->MeshData.normals, meshLoad->mNormals, sizeof(float) * ourGameObject->MeshData.num_vertex * 3);
		}

		if (meshLoad->HasTextureCoords(0))
		{
			ourGameObject->MeshData.num_texcoords = meshLoad->mNumVertices;
			ourGameObject->MeshData.texcoords = new float[ourGameObject->MeshData.num_vertex * 2];


			for (int Z = 0; Z < ourGameObject->MeshData.num_texcoords; ++Z) {

				ourGameObject->MeshData.texcoords[Z * 2] = meshLoad->mTextureCoords[0][Z].x;
				ourGameObject->MeshData.texcoords[Z * 2 + 1] = meshLoad->mTextureCoords[0][Z].y;
			}
		}

		App->renderer3D->GenerateVertexBuffer(ourGameObject->MeshData.vertex, ourGameObject->MeshData.num_vertex, ourGameObject->MeshData.id_vertex);
		App->renderer3D->GenerateIndexBuffer(ourGameObject->MeshData.index, ourGameObject->MeshData.num_index, ourGameObject->MeshData.id_index);
		if (ourGameObject->MeshData.texcoords != NULL) {
			App->renderer3D->GenerateTextBuffer(ourGameObject->MeshData.texcoords, ourGameObject->MeshData.num_texcoords, ourGameObject->MeshData.texcoords_id);
		}
		App->renderer3D->GenerateNormalBuffer(ourGameObject, *ourGameObject->MeshData.normals);




		std::string PathToLoad = App->textureImporter->CreateTexturesNodeMap(map, scene, file_path).texture_path.c_str();



		if (PathToLoad != "") {

			LOGFIX(PathToLoad.c_str());

			ourGameObject->TextureData = App->textureImporter->LoadTextureImage(PathToLoad.c_str());
		}
		else {

			LOGFIX("Mesh Node Has No Texture");
		}


		/*if (ParentIsFound == true) {

			AddMeshToListMeshesOnScene(ourGameObject, true, NULL);
		}
		else {
			AddMeshToListMeshesOnScene(ourGameObject, false, NULL);
		}*/


		ChildrenToAddList.push_back(ourGameObject);

	++ChildrenAmount;

	//Free memory
	//aiReleaseImport(scene);

	NodeMapList.clear();



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



void ModuleMeshImporter::ParentCreatedChildren(int numChildren)
{

	if (numChildren > 0) {

		int size = App->meshimporter->MeshesOnScene.size() - PreviousListSize;
		int position = PreviousListSize;
		//int size = App->meshimporter->MeshesOnScene.size() - numChildren + 1;



		GameObject* ItemParentMesh = new GameObject();
		ItemParentMesh->is_Drawn = true;
		ItemParentMesh->is_EmptyParent = true;
		ItemParentMesh->path = "path";
		AddMeshToListMeshesOnScene(ItemParentMesh, false, NULL, true);
		
		
		std::vector<GameObject*>::iterator it = App->meshimporter->MeshesOnScene.begin() + PreviousListSize;
		for (int num = PreviousListSize; num < size + 1 ; ++num) {


			GameObject* Mesh = *it;

			App->meshimporter->MeshesOnScene.back()->ChildObjects.push_back(Mesh);

			//MeshesOnScene.erase(App->meshimporter->MeshesOnScene.begin() + position);
			
			--position;
			
			++it;
			

		}


		for (int i = App->meshimporter->MeshesOnScene.size()-2; i >= PreviousListSize; --i) {

			MeshesOnScene.erase(MeshesOnScene.begin() + i);

		}


		
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

