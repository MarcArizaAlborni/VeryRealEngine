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

struct MeshTransformation {

	VectorTransformations VectorTranslation;   //Vector to determine the current position of the mesh in the world
	VectorTransformations VectorRotation;      //Vector to determine the current rotation of the mesh in the world
	VectorTransformations VectorScale;         //Vector to determine the current scale of the mesh in the world

	bool TransformsUpdated;                    //Vector to determine the current position of the mesh in the world

	float3 LocalTranslation;                   //Vector to determine the current position of the mesh in the world
	float3 WorldTranslation;                   //Vector to determine the current position of the mesh in the world
	float3 LocalScale;                         //Vector to determine the current position of the mesh in the world
	float3 WorldScale;                         //Vector to determine the current position of the mesh in the world
	Quat LocalRotation;                        //Vector to determine the current position of the mesh in the world
	Quat WorldRotation;                        //Vector to determine the current position of the mesh in the world

	float4x4 LocalMatrix;                      //Vector to determine the current position of the mesh in the world
	float4x4 WorldMatrix;                      //Vector to determine the current position of the mesh in the world
};

struct Vertex_Sub {

	float x = 0, y = 0, z=0;
};

struct MeshInfo
{
	uint id_index=0;                         // index in VRAM
	uint num_index = 0;                      // amount of indexes in a mesh
	uint* index = nullptr;                   // id of the index
	uint id_vertex = 0;                      // unique vertex in VRAM
	uint num_vertex = 0;                     // amount of vertex in a mesh
	Vertex_Sub* vertex=nullptr;              // id of the vertex

	float* texcoords = nullptr;              //coordinates of the texture in the mesh
	uint num_texcoords = 0;                  // amount of coordinates of the texture in the mesh
	uint texcoords_id = 0;                   // id of the coordinate of the texture in the mesh
	
	GLuint TextureName=0;                    // name of the current texture aplied to the mesh

	Vertex_Sub* normals;                     // amount of normals in the mesh
	uint id_normals=0;                       // id of the normals in the mesh
};

struct Object_Modifiers {

	bool is_Selected;                        // if this mesh is currently selected 

	bool is_Textured = true;                 // if this mesh is currently textured

	bool is_Drawn = true;                    // if this mesh should be rendered

	bool is_Wireframed = false;              // if this mesh is currently using wireframe to be drawn

	bool is_Checkered = false;               // if the checkers texture is applied to the mesh

	bool ToBeDrawInspector = false;          // if the mesh info should be drawn in the inspector

	bool is_EmptyParent;                     // if the mesh is an empty parent or not

	bool showFaceNormals = false;            //if we draw normals for faces 

	bool showVertexNormals = false;          //if we draw normals for vertex

	bool is_FamilyMove = false;              // if we apply transformations to each member of the family of this mesh

};

struct Object_Identifiers{
	int item_id = 0;                        // id given to each mesh to able to manage game object lists more eficiently
	std::string path = "";                  //Vector to determine the current position of the mesh in the world
	std::string mesh_name;                 // Name given to the mesh that will be shown in the engine to the user
};

struct GameObject {
     
	MeshInfo MeshData; //Information about vertex and index related to the mesh

	Object_Identifiers Identifiers;

	Object_Modifiers Modifier;

	std::string mesh_name; // Name given to the mesh that will be shown in the engine to the user

	std::vector<GameObject*> ChildObjects; // vector of child game objects inside of a game object

	MeshTransformation Mesh_Transform_Modifiers; // vectors for mesh transformation

	TextureInfo TextureData; // information of the texture applied to the mesh

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

	// LIST MESH STUFF

	//Mesh Import functions 
	void LoadMesh(const char* file_path,bool LoadfromWAF=false);
	
	void LoadFile_Mesh(const char* file_path);

	void ProcessNode(const char* file_path, const aiScene* scene, const aiNode* node, GameObject* Parent);
	std::vector<NodeMap> NodeMapList;

	void CreateGameObjectsByNodes(const aiScene* scene, const char* file_path,aiMesh* meshLoad, const aiNode* node, NodeMap map);

	//List of meshes active
	std::vector<GameObject*> MeshesOnScene; //CurrentActive meshes list
	std::vector<TextureInfo*> LoadedTexturesList; // Currently Loaded textures list
	std::vector<GameObject*> LoadedMeshesList; //Currently Loaded textures list

	// Load Assimp Node Info

	vec3 LoadNodeInfo(const aiScene* scene, aiNode* rootNode);
	// Add a mesh to the list
	
	//Object to add, if its a child and who is the parent
	void AddMeshToListMeshesOnScene(GameObject* ObjectToBeAdded,bool isChildfrom,GameObject* parent=NULL,bool parentfound=false);
private:


	std::vector<GameObject*> ChildrenToAddList;
	void CreateChildsWithParent(bool WithParent);
	
	float3 PositionValue;
	float3 ScaleValue;
	
public:
	Quat RotationValue = { -0.707106769,0,0,0.707106769 }; // THIS IS THE ERROR IN THE ROTATION IMPORT
	Quat RotationImportedVal;
	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
	
};

#endif