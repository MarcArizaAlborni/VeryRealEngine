#pragma once
#ifndef __ModuleImporters_H__
#define __ModuleImporters_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

// Class Mesh

struct MeshTransformation {

	GLfloat Translation_Vec3[3] = { 0.0f,0.0f,0.0f };

	GLfloat Rotation_Vec3[4] = { 0.0f,0.0f,0.0f,0.0f };

	GLfloat Scale_Vec3[3] = { 0.0f,0.0f,0.0f };
};

struct MeshInfo
{
	uint id_index=0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex=nullptr;

	float* texcoords = nullptr;
	uint num_texcoords = 0;
	uint texcoords_id = 0;
	
	GLuint TextureName;


	
};

struct GameObject {
     
	MeshInfo MeshData; //Information about vertex and index related to the mesh

	std::string mesh_name; // Name given to the mesh that will be shown in the engine to the user

	bool is_Selected; // if this mesh is currently selected 

	bool is_Textured=true; // if this mesh is currently textured

	bool is_Drawn=true; // if this mesh should be rendered

	bool is_Wireframed=false; // if this mesh is currently using wireframe to be drawn

	bool is_Checkered = false;

	int item_id; // id given to each mesh to able to manage game object lists more eficiently

	std::vector<GameObject*> ChildObjects; // vector of child game objects inside of a game object

	MeshTransformation Mesh_Transform_Modifiers;

	bool ToBeDrawInspector;

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
	MeshInfo* LoadMesh(char* file_path);

	//List of meshes active
	std::vector<GameObject*> MeshesOnScene;
	
	// Add a mesh to the list

	//Object to add, if its a child and who is the parent
	void AddMeshToListMeshesOnScene(GameObject* ObjectToBeAdded,bool isChildfrom,GameObject* parent);


	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
	
};

#endif