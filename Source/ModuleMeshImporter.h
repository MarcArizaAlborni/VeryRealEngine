#pragma once
#ifndef __ModuleImporters_H__
#define __ModuleImporters_H__
#include "Module.h"
#include "Globals.h"



#include "libraries/MathGeoLib/include/MathGeoLib.h"


// Class Mesh

struct VectorTransformations;
struct TextureInfo;
struct aiScene;
struct aiNode;
struct StoredFile;
struct aiMesh;
class ImportSettings;

struct MeshInfo
{
	
	uint id_index=0;                         // index in VRAM
	uint num_index = 0;                      // amount of indexes in a mesh
	uint* index = nullptr;                   // id of the index
	uint id_vertex = 0;                      // unique vertex in VRAM
	uint num_vertex = 0;                     // amount of vertex in a mesh
	float3* vertex=nullptr;                  // id of the vertex

	float* texcoords = nullptr;              //coordinates of the texture in the mesh
	uint num_texcoords = 0;                  // amount of coordinates of the texture in the mesh
	uint texcoords_id = 0;                   // id of the coordinate of the texture in the mesh
	
	GLuint TextureName=0;                    // name of the current texture aplied to the mesh

	float3* normals;                     // amount of normals in the mesh
	uint id_normals=0;                       // id of the normals in the mesh

	std::string Name;
};

struct NodeMap {

	std::vector<NodeMap> Children;
	int ScenePositionArray = -1;
	int MaterialPositionArray = -1;
	std::string MaterialPath = "";
	std::string Name = "";
};

class ModuleMeshImporter : public Module
{
public:
	ModuleMeshImporter(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleMeshImporter();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	// LIST MESH 
	
	void LoadFile_Mesh(const char* file_path);

	void ProcessNode(const char* file_path, const aiScene* scene, const aiNode* node, Game_Object* Parent);
	std::vector<NodeMap> NodeMapList;

	std::vector<MeshInfo*> LoadSceneMeshes(const aiScene* scene, const char* file_path, const aiNode* node);
	void CreateMaterials(aiMaterial* material, Game_Object* Object);
	//List of meshes active
	 //CurrentActive meshes list
	std::vector<TextureInfo*> LoadedTexturesList; // Currently Loaded textures list
	int CheckMeshExistance(std::string MeshPath);
	std::vector<MeshInfo*> Mesh_Resource_List;
	// Load Assimp Node Info

	vec3 LoadNodeInfo(const aiScene* scene, aiNode* rootNode);
	


private:
	
	float3 PositionValue;
	float3 ScaleValue;
	
public:


	
};

#endif