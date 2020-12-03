#include "Globals.h"
#include "Application.h"
#include "ModuleMeshImporter.h"
#include "ModuleRenderer3D.h"
#include "FileSystem.h"
#include "ModuleEditor.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentTexture.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"
#include "ModuleScene.h"
#include "libraries/Assimp/Assimp/include/cimport.h"
#include "libraries/Assimp/Assimp/include/scene.h"
#include "libraries/Assimp/Assimp/include/postprocess.h"
#pragma comment (lib, "libraries/Assimp/Assimp/libx86/assimp.lib")

#include "libraries/Glew/include/GL/glew.h"

#include <gl/GLU.h>
#pragma comment (lib, "libraries/PhysFS/include/physfs.h")
#include "libraries/PhysFS/include/physfs.h"

#include "libraries/MathGeoLib/include/MathGeoLib.h"

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

//// Load a mesh with index and vertex
//void ModuleMeshImporter::LoadMesh(const char* file_path,bool LoadfromWAF)
//{
//	//LOGFIX("Importing Model %s...",file_path);	
//
//	bool ReadyToLoad = false;
//	const aiScene* scene;
//	if (LoadfromWAF == true) {
//		const char* path = "Assets/Models/House/BakerHouse.fbx";
//		scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
//	}
//	else {
//		scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
//	}
//
//	if (LoadfromWAF == false) {
//		
//		if (scene != nullptr) {
//			ReadyToLoad = true;
//		}
//	}
//
//	if (LoadfromWAF == true) {
//		ReadyToLoad = true;
//	}
//
//	if (ReadyToLoad == true) {
//
//		if (LoadfromWAF == false) {
//			aiNode* rootNodeScene = scene->mRootNode;
//		}
//
//		LoadedFile* InformationToRecieve;
//
//		int TemporaryID = -1; // This is only temporary, should not be used this way
//
//		if (LoadfromWAF == false) {
//
//			StoredFile InformationToSend;
//			InformationToSend.Scene = scene;
//			App->filemanager->SaveInformationFile_Mesh(TemporaryID = App->GiveRandomNum_Undefined(), InformationToSend);
//
//		}
//		else { TemporaryID = 172; }
//
//		InformationToRecieve = App->filemanager->LoadInformationFile_Mesh(TemporaryID);
//		//InformationToRecieve = App->filemanager->LoadedResources.back();
//
//		bool ParentHasFound = false;
//
//		if (LoadfromWAF == true) {
//
//			if (InformationToRecieve->AmountMeshes > 1) {
//
//				GameObject* ItemParentMesh = new GameObject();
//				ItemParentMesh->Modifier.is_Drawn = true;
//				ItemParentMesh->Modifier.is_EmptyParent = true;
//				ItemParentMesh->Identifiers.path = file_path;
//				AddMeshToListMeshesOnScene(ItemParentMesh, false, NULL, true);
//				ParentHasFound = true;
//
//			}
//
//			for (int i = 0; i < InformationToRecieve->AmountMeshes; ++i) {
//
//				GameObject* ourGameObject = new GameObject();
//				//aiMesh* MeshToLoad = scene->mMeshes[i];
//				ourGameObject->Identifiers.path = file_path;
//				
//				ourGameObject->MeshData.num_vertex = InformationToRecieve->MeshInfo[i].AmountVertex;
//
//				ourGameObject->MeshData.vertex = new Vertex_Sub[ourGameObject->MeshData.num_vertex * 3];
//
//				for (int h = 0; h < InformationToRecieve->MeshInfo[i].AmountVertex; ++h) {
//				
//					ourGameObject->MeshData.vertex[h] = InformationToRecieve->MeshInfo[i].Vertex[h];
//				}
//
//				//memcpy(ourGameObject->MeshData.vertex, MeshToLoad->mVertices, sizeof(float) * ourGameObject->MeshData.num_vertex * 3);
//				
//				if (InformationToRecieve->MeshInfo[i].AmountFaces!=0) {
//
//					ourGameObject->MeshData.num_index = InformationToRecieve->MeshInfo[i].AmountFaces*3; //aixo
//
//					int a = 0;
//
//					ourGameObject->MeshData.index = new uint[ourGameObject->MeshData.num_index];
//					
//
//					for (int c = 0; c < InformationToRecieve->MeshInfo[i].AmountFaces; ++c) {
//
//						//IF MESHES HAVE TRIS
//						if (InformationToRecieve->MeshInfo[i].FaceInfo[c].AmountIndex== 3) {
//
//							unsigned int IndexCopy[3];
//
//
//							//IndexCopy = new uint[ourGameObject->MeshData.num_index];
//
//
//							IndexCopy[0] = InformationToRecieve->MeshInfo[i].FaceInfo[c].indexV1;
//							IndexCopy[1] = InformationToRecieve->MeshInfo[i].FaceInfo[c].indexV2;
//							IndexCopy[2] = InformationToRecieve->MeshInfo[i].FaceInfo[c].indexV3;
//							
//							memcpy(&ourGameObject->MeshData.index[c * 3], IndexCopy, 3 * sizeof(uint));
//							
//						}
//					}
//				}
//
//				if (InformationToRecieve->MeshInfo[i].Normal.size()!=0) {
//
//					ourGameObject->MeshData.normals = new Vertex_Sub[ourGameObject->MeshData.num_vertex * 3];
//
//					for (int mf = 0; mf < InformationToRecieve->MeshInfo[i].AmountVertex; ++mf) {
//						ourGameObject->MeshData.normals[mf] = InformationToRecieve->MeshInfo[i].Normal[mf];
//					}
//					
//					//memcpy(ourGameObject->MeshData.normals, scene->mMeshes[i]->mNormals, sizeof(float) * ourGameObject->MeshData.num_vertex * 3);
//				}
//
//				if (InformationToRecieve->MeshInfo[i].TextureCoords.size()!=0)
//				{
//					ourGameObject->MeshData.num_texcoords = InformationToRecieve->MeshInfo[i].AmountVertex;
//					ourGameObject->MeshData.texcoords = new float[ourGameObject->MeshData.num_texcoords * 2];
//
//					for (int Z = 0; Z < ourGameObject->MeshData.num_texcoords; ++Z) {
//
//						ourGameObject->MeshData.texcoords[Z * 2] = InformationToRecieve->MeshInfo[i].TextureCoords[Z].x; //??????
//						ourGameObject->MeshData.texcoords[(Z * 2) + 1] = InformationToRecieve->MeshInfo[i].TextureCoords[Z].y;
//					}
//				}
//
//				App->renderer3D->GenerateVertexBuffer(ourGameObject->MeshData.vertex, ourGameObject->MeshData.num_vertex, ourGameObject->MeshData.id_vertex);
//				App->renderer3D->GenerateIndexBuffer(ourGameObject->MeshData.index, ourGameObject->MeshData.num_index, ourGameObject->MeshData.id_index);
//				App->renderer3D->GenerateTextBuffer(ourGameObject->MeshData.texcoords, ourGameObject->MeshData.num_texcoords, ourGameObject->MeshData.texcoords_id);
//				App->renderer3D->GenerateNormalBuffer(ourGameObject, ourGameObject->MeshData.normals);
//
//
//				if (ParentHasFound == true) {
//
//					AddMeshToListMeshesOnScene(ourGameObject, true, NULL);
//				}
//				else {
//					AddMeshToListMeshesOnScene(ourGameObject, false, NULL);
//				}
//			}
//			//Free memory
//			aiReleaseImport(scene);
//
//		}
//		else {
//
//			if (InformationToRecieve->AmountMeshes > 1) {
//
//				GameObject* ItemParentMesh = new GameObject();
//				ItemParentMesh->Modifier.is_Drawn = true;
//				ItemParentMesh->Modifier.is_EmptyParent = true;
//				
//				AddMeshToListMeshesOnScene(ItemParentMesh, false, NULL, true);
//				ParentHasFound = true;
//
//			}
//
//			for (int i = 0; i < InformationToRecieve->AmountMeshes; ++i) {
//
//				GameObject* ourGameObject = new GameObject();
//
//				aiMesh* MeshToLoad = scene->mMeshes[i];
//
//				MeshToLoad->mNumVertices = InformationToRecieve->MeshInfo[i].AmountVertex;
//				MeshToLoad->mNumFaces = InformationToRecieve->MeshInfo[i].AmountFaces;
//
//				for (int d = 0; d < InformationToRecieve->MeshInfo[i].AmountFaces; ++d) {
//
//					
//					MeshToLoad->mFaces[d].mNumIndices = InformationToRecieve->MeshInfo[i].FaceInfo[d].AmountIndex;
//				}
//
//				ourGameObject->MeshData.num_vertex = MeshToLoad->mNumVertices;
//
//				ourGameObject->MeshData.vertex = new Vertex_Sub[ourGameObject->MeshData.num_vertex * 3];
//
//				memcpy(ourGameObject->MeshData.vertex, MeshToLoad->mVertices, sizeof(float) * ourGameObject->MeshData.num_vertex * 3);
//
//				if (MeshToLoad->HasFaces()) {
//
//					ourGameObject->MeshData.num_index = MeshToLoad->mNumFaces * 3; //aixo
//
//					int a = 0;
//
//					ourGameObject->MeshData.index = new uint[ourGameObject->MeshData.num_index];
//
//					for (int c = 0; c < MeshToLoad->mNumFaces; ++c) {
//
//						//IF MESHES HAVE TRIS
//						if (MeshToLoad->mFaces[c].mNumIndices == 3) {
//
//							memcpy(&ourGameObject->MeshData.index[c * 3], MeshToLoad->mFaces[c].mIndices, 3 * sizeof(uint));
//						}
//					}
//				}
//
//				if (scene->mMeshes[i]->HasNormals()) {
//
//					ourGameObject->MeshData.normals = new Vertex_Sub[ourGameObject->MeshData.num_vertex * 3];
//					memcpy(ourGameObject->MeshData.normals, scene->mMeshes[i]->mNormals, sizeof(float) * ourGameObject->MeshData.num_vertex * 3);
//				}
//
//				if (MeshToLoad->HasTextureCoords(0))
//				{
//					ourGameObject->MeshData.num_texcoords = MeshToLoad->mNumVertices;
//					ourGameObject->MeshData.texcoords = new float[ourGameObject->MeshData.num_texcoords * 2];
//
//					for (int Z = 0; Z < ourGameObject->MeshData.num_texcoords; ++Z) {
//
//						ourGameObject->MeshData.texcoords[Z * 2] = MeshToLoad->mTextureCoords[0][Z].x;
//						ourGameObject->MeshData.texcoords[(Z * 2) + 1] = MeshToLoad->mTextureCoords[0][Z].y;
//					}
//				}
//
//				App->renderer3D->GenerateVertexBuffer(ourGameObject->MeshData.vertex, ourGameObject->MeshData.num_vertex, ourGameObject->MeshData.id_vertex);
//				App->renderer3D->GenerateIndexBuffer(ourGameObject->MeshData.index, ourGameObject->MeshData.num_index, ourGameObject->MeshData.id_index);
//				App->renderer3D->GenerateTextBuffer(ourGameObject->MeshData.texcoords, ourGameObject->MeshData.num_texcoords, ourGameObject->MeshData.texcoords_id);
//				App->renderer3D->GenerateNormalBuffer(ourGameObject, ourGameObject->MeshData.normals);
//
//
//				if (ParentHasFound == true) {
//
//					AddMeshToListMeshesOnScene(ourGameObject, true, NULL);
//				}
//				else {
//					AddMeshToListMeshesOnScene(ourGameObject, false, NULL);
//				}
//			}
//			//Free memory
//			aiReleaseImport(scene);
//		}
//
//	}
//}


void ModuleMeshImporter::LoadFile_Mesh(const char* file_path)
{
	
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr) {

		std::vector<Game_Object*>::iterator It = App->geometrymanager->ObjectsOnScene.begin();
		Game_Object* Parent = *It;

		ProcessNode(file_path, scene, scene->mRootNode, App->scene->ROOT_SCENE_OBJECT);
		
		aiReleaseImport(scene);
	}
}

void ModuleMeshImporter::ProcessNode(const char* file_path, const aiScene* scene, const aiNode* node,Game_Object* Parent)
{
	Game_Object* ObjectToAdd = new Game_Object(node->mName.C_Str());

	aiVector3D  Imported_Translation;
	aiVector3D  Imported_Scale;
	aiQuaternion Imported_Rotation;

	node->mTransformation.Decompose(Imported_Scale, Imported_Rotation, Imported_Translation);

	float3	Translation_Calculated(Imported_Translation.x, Imported_Translation.y, Imported_Translation.z);
	float3	Scale_Calculated(Imported_Scale.x, Imported_Scale.y, Imported_Scale.z);
	Quat	Rotation_Calculated(Imported_Rotation.x, Imported_Rotation.y, Imported_Rotation.z, Imported_Rotation.w);
	Quat    RotMat;
	
	
	while (strstr(node->mName.C_Str(), "_$AssimpFbx$") != nullptr && node->mNumChildren == 1)
	{
		node = node->mChildren[0];

		node->mTransformation.Decompose(Imported_Scale, Imported_Rotation, Imported_Translation);

		RotMat = Quat(Imported_Rotation.x, Imported_Rotation.y, Imported_Rotation.z, Imported_Rotation.w);


		Translation_Calculated.x += Imported_Translation.x;
		Translation_Calculated.y += Imported_Translation.y;
		Translation_Calculated.z += Imported_Translation.z;

		Scale_Calculated.x *= Imported_Scale.x;
		Scale_Calculated.y *= Imported_Scale.y;
		Scale_Calculated.z *= Imported_Scale.z;

		Rotation_Calculated = Rotation_Calculated * RotMat;

		

	}

	if (node->mNumMeshes > 0) {

		std::vector<MeshInfo*> Mesh = LoadSceneMeshes(scene, file_path, node);

		for (int number = 0; number < Mesh.size(); ++number) {

		
			Component_Mesh* Comp_Mesh = new Component_Mesh(ObjectToAdd);

			Comp_Mesh->CreateMesh(Mesh[number]);
			Comp_Mesh->CreatePath(file_path);
			ObjectToAdd->AddExistingComponent(Comp_Mesh);
			
			aiMesh* MeshImported = scene->mMeshes[node->mMeshes[number]];

			if (MeshImported->mMaterialIndex >= 0) {
				
				aiMaterial* texture = scene->mMaterials[MeshImported->mMaterialIndex];

				CreateMaterials(texture, ObjectToAdd);
			}
		}
	}

	

	Parent->GenerateChildren(ObjectToAdd);

	//ObjectToAdd->Parent = Parent;


	ObjectToAdd->Transformations->UpdateTransformationsObjects(Translation_Calculated, Scale_Calculated, Rotation_Calculated);

	//Parent->Children_List.push_back(ObjectToAdd);


	for (uint i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(file_path, scene, node->mChildren[i], ObjectToAdd);
	}

}



void ModuleMeshImporter::CreateChildsWithParent(bool WithParent)
{

	if (WithParent == true) {

		GameObject* ItemParentMesh = new GameObject();
		ItemParentMesh->Modifier.is_Drawn = true;
		ItemParentMesh->Modifier.is_EmptyParent = true;
		ItemParentMesh->Identifiers.path = "path";
		ItemParentMesh->Mesh_Transform_Modifiers.TransformsUpdated = true;
		//ItemParentMesh->is_FamilyMove = true;

		ItemParentMesh->Mesh_Transform_Modifiers.VectorRotation.x = RotationImportedVal.x;
		ItemParentMesh->Mesh_Transform_Modifiers.VectorRotation.y = RotationImportedVal.y;
		ItemParentMesh->Mesh_Transform_Modifiers.VectorRotation.z = RotationImportedVal.z;
		ItemParentMesh->Mesh_Transform_Modifiers.VectorRotation.angle = RotationImportedVal.w;
		AddMeshToListMeshesOnScene(ItemParentMesh, false, NULL, true);

		std::vector<GameObject*>::iterator IteratorChild = ChildrenToAddList.begin();

		for (int i = 0; i < ChildrenToAddList.size(); ++i) {

			GameObject* Mesh = *IteratorChild;

			Mesh->Identifiers.item_id = i+1;

			App->meshimporter->MeshesOnScene.back()->ChildObjects.push_back(Mesh);

			++IteratorChild;

		}
	}
	else {

		std::vector<GameObject*>::iterator IteratorChild = ChildrenToAddList.begin();

		App->meshimporter->MeshesOnScene.push_back(*IteratorChild);
	}
}

void ModuleMeshImporter::CreateGameObjectsByNodes(const aiScene* scene, const char* file_path, aiMesh* meshLoad, const aiNode* node,NodeMap map)
{

	NodeMapList.size();

	bool ParentIsFound = false;

     GameObject* ourGameObject = new GameObject();
     
     ourGameObject->mesh_name = node->mName.C_Str();
     
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
    // App->renderer3D->GenerateNormalBuffer(ourGameObject, ourGameObject->MeshData.normals);

     
     
	 TextureInfo TextureLoad;
     
	 TextureLoad = App->textureImporter->CreateTexturesNodeMap(map, scene, file_path);
     
	std::string PathToLoad= TextureLoad.texture_path.c_str();
     
     if (PathToLoad != "") {
     
     	LOGFIX(PathToLoad.c_str());
     
	
     	ourGameObject->TextureData = App->textureImporter->LoadTextureImage(PathToLoad.c_str());
		ourGameObject->TextureData.Colour = TextureLoad.Colour;
     }
     else {
		 ourGameObject->TextureData.Colour = TextureLoad.Colour;
     	LOGFIX("Mesh Node Has No Texture, Aplying Colour");
     }
     
     
     /*if (ParentIsFound == true) {
     
     	AddMeshToListMeshesOnScene(ourGameObject, true, NULL);
     }
     else {
     	AddMeshToListMeshesOnScene(ourGameObject, false, NULL);
     }*/
     
     
     ChildrenToAddList.push_back(ourGameObject);
     
     

	//Free memory
	//aiReleaseImport(scene);

	NodeMapList.clear();



}

std::vector<MeshInfo*> ModuleMeshImporter::LoadSceneMeshes(const aiScene* scene, const char* file_path,  const aiNode* node)
{
	std::vector<MeshInfo*> ItemList;

	for (int number = 0; number < node->mNumMeshes; number++) {


		MeshInfo* OurMesh = new MeshInfo();

		aiMesh* meshLoad = scene->mMeshes[node->mMeshes[number]];

		OurMesh->num_vertex = meshLoad->mNumVertices;

		OurMesh->vertex = new Vertex_Sub[OurMesh->num_vertex * 3];

		memcpy(OurMesh->vertex, meshLoad->mVertices, sizeof(float) * OurMesh->num_vertex * 3);

		if (meshLoad->HasFaces()) {

			OurMesh->num_index = meshLoad->mNumFaces * 3;


			OurMesh->index = new uint[OurMesh->num_index];

			for (int c = 0; c < meshLoad->mNumFaces; ++c) {

				unsigned int IndexCopy[3];

				memcpy(&OurMesh->index[c * 3], meshLoad->mFaces[c].mIndices, 3 * sizeof(uint));
			}
		}

		if (meshLoad->HasNormals()) {

			OurMesh->normals = new Vertex_Sub[OurMesh->num_vertex * 3];
			memcpy(OurMesh->normals, meshLoad->mNormals, sizeof(float) * OurMesh->num_vertex * 3);

		}


		if (meshLoad->HasTextureCoords(0))
		{
			OurMesh->num_texcoords = meshLoad->mNumVertices;
			OurMesh->texcoords = new float[OurMesh->num_vertex * 2];


			for (int Z = 0; Z < OurMesh->num_texcoords; ++Z) {

				OurMesh->texcoords[Z * 2] = meshLoad->mTextureCoords[0][Z].x;
				OurMesh->texcoords[Z * 2 + 1] = meshLoad->mTextureCoords[0][Z].y;
			}
		}

		App->renderer3D->GenerateVertexBuffer(OurMesh->vertex, OurMesh->num_vertex, OurMesh->id_vertex);
		App->renderer3D->GenerateIndexBuffer(OurMesh->index, OurMesh->num_index, OurMesh->id_index);
		if (OurMesh->texcoords != NULL) {
			App->renderer3D->GenerateTextBuffer(OurMesh->texcoords, OurMesh->num_texcoords, OurMesh->texcoords_id);
		}
		App->renderer3D->GenerateNormalBuffer(OurMesh, OurMesh->normals);



		ItemList.push_back(OurMesh);

	}

	return ItemList;
}

void ModuleMeshImporter::CreateMaterials(aiMaterial* material, Game_Object* Object)
{

	TextureInfo* OurMat = new TextureInfo();

	aiColor4D	color;
	aiString	texPath;
	std::string		texName;
	std::string		texExtension;

	if (material->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)										// Could also get specular and ambient occlusion colours.
	{
		//OurMat->SetColor(Color(color.r, color.g, color.b, color.a));
		OurMat->Colour.r = color.r;
		OurMat->Colour.g = color.g;
		OurMat->Colour.b = color.b;
		OurMat->Colour.a = color.a;

	}
	if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texPath) == AI_SUCCESS)
	{
		App->filemanager->SplitFilePath(texPath.C_Str(), nullptr, &texName, &texExtension);

		texName = "Assets/Textures/" + texName + "." + texExtension;
		
		TextureInfo MaterialLoad = App->textureImporter->LoadTextureImage(texName.c_str());

		

		OurMat->height = MaterialLoad.height;
		OurMat->width = MaterialLoad.width;
		OurMat->texture_id = MaterialLoad.texture_id;
		OurMat->texture_name = MaterialLoad.texture_name;
		OurMat->texture_path = MaterialLoad.texture_path;




	}


	Component_Texture* TextureComponent = new Component_Texture(Object, OurMat);
	Object->AddExistingComponent(TextureComponent);



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

			Object->Identifiers.item_id = size2;

			Object->Modifier.is_Selected = false;
			Object->Modifier.is_Textured = true;
			//Object->mesh_name = "Empty Parent";
			itemParent->ChildObjects.push_back(Object);
	}
	else {

		int size = MeshesOnScene.size() +1;

		Object->Identifiers.item_id = size;
		Object->Modifier.is_Selected = false;
		Object->Modifier.is_Textured = true;
		
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

