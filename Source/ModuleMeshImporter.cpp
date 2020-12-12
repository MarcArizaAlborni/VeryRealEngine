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
#include "ModuleHierarchy.h"
#include "ComponentTransform.h"
#include "FileSystem.h"
#include "ResourceManager.h"
#include "ModuleScene.h"
#include "libraries/Assimp/Assimp/include/cimport.h"
#include "libraries/Assimp/Assimp/include/scene.h"
#include "libraries/Assimp/Assimp/include/postprocess.h"
#pragma comment (lib, "libraries/Assimp/Assimp/libx86/assimp.lib")

#include "libraries/Glew/include/GL/glew.h"

#include <gl/GLU.h>
#pragma comment (lib, "libraries/PhysFS/include/physfs.h")
#include "libraries/PhysFS/include/physfs.h"

//#include "libraries/MathGeoLib/include/MathGeoLib.h"
#include "libraries/MathGeoLib/include/Math/float3.h"

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

void ModuleMeshImporter::LoadFile_Mesh(const char* file_path)
{
	
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

	//path modification
	std::string OGPath = file_path;
	std::string PreName;
	std::string Name;
	std::string NoExte;
	std::string FinalPath;
	std::string NewExte = ".meta";
	
	App->resources->GetSplittedFile(file_path, nullptr, &PreName, &Name);

	size_t pos_dot = Name.find_last_of(".");

	NoExte = Name.substr(0,pos_dot);

	FinalPath = PreName + NoExte + NewExte;

	

	//App->filemanager->CurrentlyDetectedMETA = FinalPath;  // We set the path to the meta we will be using


	//if (App->filemanager->Exists(FinalPath.c_str())) {
	//
	//	if (scene != nullptr) {
	//
	//		std::vector<Game_Object*>::iterator It = App->geometrymanager->ObjectsOnScene.begin();
	//		Game_Object* Parent = *It;
	//
	//		ProcessNode(file_path, scene, scene->mRootNode, App->scene->ROOT_SCENE_OBJECT);
	//
	//		aiReleaseImport(scene);
	//	}
	//}
	//else {
	//
	//	//HERE SHOULD GO AND CREATE META
	//
	//	PHYSFS_openWrite(FinalPath.c_str()); // We create Meta File
	//
	//	if (scene != nullptr) {
	//
	//		std::vector<Game_Object*>::iterator It = App->geometrymanager->ObjectsOnScene.begin();
	//		Game_Object* Parent = *It;
	//
	//		ProcessNode(file_path, scene, scene->mRootNode, App->scene->ROOT_SCENE_OBJECT);
	//
	//		aiReleaseImport(scene);
	//	}
	//
	//}
	//
	//
	//App->filemanager->LoadMesh_META();
	//
	//App->filemanager->CreateMesh_META(NULL, file_path);
	//
	//App->filemanager->StoreMetaIDs_List.clear();
	//App->filemanager->CurrentlyDetectedMETA = "";


	

	if (scene != nullptr) {

		std::vector<Game_Object*>::iterator It = App->geometrymanager->ObjectsOnScene.begin();
		Game_Object* Parent = *It;

		ProcessNode(file_path, scene, scene->mRootNode, App->scene->ROOT_SCENE_OBJECT);

		aiReleaseImport(scene);

		LOG("[WARNING] Succes importing the scene & creating objects");
	}

	//App->filemanager->LoadMesh_META();
	
	//App->filemanager->CreateMesh_META(NULL, file_path);
	//
	//App->filemanager->StoreMetaIDs_List.clear();
	//App->filemanager->CurrentlyDetectedMETA = "";
}

void ModuleMeshImporter::ProcessNode(const char* file_path, const aiScene* scene, const aiNode* node,Game_Object* Parent)
{
	Game_Object* ObjectToAdd = new Game_Object(node->mName.C_Str());

	if (ObjectToAdd->name == "RootNode") {
		ObjectToAdd->name = ObjectToAdd->name + std::to_string(App->hierarchy->RootNodeCount);
		++App->hierarchy->RootNodeCount;
	}

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
		Component_Mesh* Comp_Mesh = new Component_Mesh(ObjectToAdd);

		for (int number = 0; number < Mesh.size(); ++number) {

		
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
	Component_Transform* MeshTrans = (Component_Transform*)ObjectToAdd->GetComponent(Component_Types::Transform);

	if (ObjectToAdd->Mesh != nullptr && MeshTrans != nullptr)
	{
		ObjectToAdd->Mesh->CreateLocalAABB();
		ObjectToAdd->Mesh->GetGlobalAABB();
		ObjectToAdd->Mesh->GenerateBBBufers();
	}

	for (uint i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(file_path, scene, node->mChildren[i], ObjectToAdd);
	}

}


std::vector<MeshInfo*> ModuleMeshImporter::LoadSceneMeshes(const aiScene* scene, const char* file_path,  const aiNode* node)
{
	std::vector<MeshInfo*> ItemList;

	for (int number = 0; number < node->mNumMeshes; number++) {

		aiMesh* meshLoad = scene->mMeshes[node->mMeshes[number]];

		  
		    node->mName.C_Str();
		

			MeshInfo* OurMesh = new MeshInfo();

			OurMesh->Name = node->mName.C_Str();

			OurMesh->num_vertex = meshLoad->mNumVertices;
			//OurMesh->Name = meshLoad->mName.C_Str();
			OurMesh->vertex = new float3[OurMesh->num_vertex * 3];

			memcpy(OurMesh->vertex, meshLoad->mVertices, sizeof(float) * OurMesh->num_vertex * 3);

			if (meshLoad->HasFaces()) {

				OurMesh->num_index = meshLoad->mNumFaces * 3;


				OurMesh->index = new uint[OurMesh->num_index];

				for (int c = 0; c < meshLoad->mNumFaces; ++c) {



					memcpy(&OurMesh->index[c * 3], meshLoad->mFaces[c].mIndices, 3 * sizeof(uint));
				}
			}

			if (meshLoad->HasNormals()) {

				OurMesh->normals = new float3[OurMesh->num_vertex * 3];
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

			
			//App->filemanager->SaveMeshInto_WAF(OurMesh, meshLoad);  //COMMENTED FOR NOW SO WE DONT GENERATE 




			ItemList.push_back(OurMesh);

			Mesh_Resource_List.push_back(OurMesh);
		
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
		
		int TexturePosition = -1;

		TexturePosition = App->textureImporter->CheckTextureExistance(texName);

		if (TexturePosition == -1) {
			TextureInfo MaterialLoad = App->textureImporter->LoadTextureImage(texName.c_str());

			OurMat->height = MaterialLoad.height;
			OurMat->width = MaterialLoad.width;
			OurMat->texture_id = MaterialLoad.texture_id;
			OurMat->texture_name = MaterialLoad.texture_name;
			OurMat->texture_path = MaterialLoad.texture_path;
			OurMat->uses = MaterialLoad.uses = 1;
			App->textureImporter->Textures_Resource_List.push_back(OurMat);

		}
		else {
			TextureInfo* MaterialLoad = App->textureImporter->Textures_Resource_List[TexturePosition];
			++App->textureImporter->Textures_Resource_List[TexturePosition]->uses;

			OurMat->height = MaterialLoad->height;
			OurMat->width = MaterialLoad->width;
			OurMat->texture_id = MaterialLoad->texture_id;
			OurMat->texture_name = MaterialLoad->texture_name;
			OurMat->texture_path = MaterialLoad->texture_path;
			++OurMat->uses;
		}
	}

	Component_Texture* TextureComponent = new Component_Texture(Object, OurMat);
	Object->AddExistingComponent(TextureComponent);
	
}


int ModuleMeshImporter::CheckMeshExistance(std::string MeshPath)
{
	int Ret = -1;

	std::vector<MeshInfo*>::iterator It = Mesh_Resource_List.begin();

	for (int size = 0; size < Mesh_Resource_List.size(); ++size) {

		MeshInfo* Mesh = *It;

		if (Mesh->Name == MeshPath) {

			Ret = size;
		}
		++It;
	}


	return Ret;
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





