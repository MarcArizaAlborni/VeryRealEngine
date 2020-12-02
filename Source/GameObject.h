#pragma once
#ifndef __GameObject_H__
#define __GameObject_H__

#include <string>
#include <vector>

class Component;
class Component_Texture;
class Component_Mesh;
class Component_Camera;
class Component_Transform;
enum class Component_Types;
class Game_Object {

public:
	Game_Object(std::string name= "GameObject");
	~Game_Object();

	std::string name;
	
	bool Enabled;

	Component_Transform* Transformations = nullptr;
	Component_Texture* Textures = nullptr;
	Component_Mesh* Mesh = nullptr;
	Component_Camera* Camera = nullptr;
	


	Game_Object* Parent = nullptr;

	void GenerateToParent(Game_Object* Parent);

	std::vector<Game_Object*> Children_List;
	std::vector<Component*> Component_List;

	Component* AddComponent(Component* Component);
	Component* GetComponent(Component_Types type);


	void GenerateChildren(Game_Object* ObjectToAdd);
	void DeleteSpecificChildren(Game_Object* ObjectToDelete);
	void DeleteAllChildren();

	void Enable();
	void Disable();



	

	//MeshInfo MeshData; //Information about vertex and index related to the mesh

	//Object_Identifiers Identifiers;

	//Object_Modifiers Modifier;

	//MeshTransformation Mesh_Transform_Modifiers; // vectors for mesh transformation

	//TextureInfo TextureData; // information of the texture applied to the mesh


public:

	void Update();
	void CleanUp();


};






#endif