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
class Component_Listener;
class Component_Source;

enum class Component_Types;

class Game_Object {

public:
	Game_Object(std::string name= "GameObject");
	~Game_Object();

	std::string name;
	int item_id=0;
	
	Component_Transform* Transformations = nullptr;
	Component_Texture* Textures = nullptr;
	Component_Mesh* Mesh = nullptr;
	Component_Camera* Camera = nullptr;
	Component_Listener* Listener = nullptr;
	Component_Source* Source = nullptr;
	
	Component_Camera* GetComponentCamera();

	Game_Object* Parent = nullptr;

	void GenerateToParent(Game_Object* Parent);

	std::vector<Game_Object*> Children_List;
	std::vector<Component*> Component_List;

	Component* AddComponent(Component_Types typus);
	Component* AddExistingComponent(Component* component);
	Component* GetComponent(Component_Types type);

	void GenerateChildren(Game_Object* ObjectToAdd);
	void ChangeParentFromObject(Game_Object* ObjectToAdd);
	void DeleteSpecificChildren(Game_Object* ObjectToDelete);
	void DeleteAllChildren();
	void GiveNewParent(Game_Object* Parent);

	void Enable();
	void Disable();

	//BOOLS
	bool Enabled;
	bool is_Wireframed;
	bool is_Checkered;
	bool showVertexNormals;
	bool is_Selected;
	bool ToBeDrawInspector;
	

	bool is_spatial_Origin = false; //spatial audio source
	bool isAudioDistanceObject=false; // if it appears in the hierarchy (for audio source distance objects) and if its the game object related to the mesh that sets the max distance 
	//of the audio source

public:

	void Update();
	void CleanUp();
};


#endif