#include "GameObject.h"

#include <vector>
#include "Application.h"
#include "ComponentCamera.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"
#include "ComponentTransform.h"
#include "Component.h"

Game_Object::Game_Object(std::string name) : name(name), Enabled(true)
{
	
	this->Parent = nullptr;	
}

Game_Object::~Game_Object()
{
}

void Game_Object::GenerateToParent(Game_Object* Parent)
{
}

Component* Game_Object::AddComponent(Component_Types typus)
{
	Component* Ret = nullptr;

	bool UniqueComponent = false;

	switch (typus) {

	case Component_Types::None:
		LOG("[WARNING] The Emptyness of a component has been added to GameObject");
		
		break;

	case Component_Types::Mesh:
		LOG("[WARNING]Component Mesh added to GameObject");

		Ret = new Component_Mesh(this);
		UniqueComponent = true;
		
		break;

	case Component_Types::Transform:
		LOG("[WARNING]Component Transform added to GameObject");

		Ret = new Component_Mesh(this);
		UniqueComponent = true;


		break;

	case Component_Types::Camera:
		LOG("[WARNING]Component Camera added to GameObject");

		//Ret = new Component_Mesh(this); WIP
		UniqueComponent = true;
		break;

	case Component_Types::Texture:
		LOG("[WARNING]Component Texture added to GameObject");

		Ret = new Component_Texture(this);

		UniqueComponent = true;
		break;

	default:
		LOG("[WARNING]Error when adding Component");
		break;
	}

	if (Ret != nullptr) {

		if (UniqueComponent) {



		}

		Component_List.push_back(Ret);
	}
	else {
		LOG("[WARNING] Component doesn't exist");
	}

	return nullptr;
}

Component* Game_Object::GetComponent(Component_Types type)
{
	Component* Ret;

	for (int i = 0; i < Component_List.size(); ++i) {

		if (Component_List[i]->type == type) {

			return(Component_List[i]);

		}
	}

	return nullptr;
}

void Game_Object::GenerateChildren(Game_Object* ObjectToAdd)
{
	this->Children_List.push_back(ObjectToAdd);
}

void Game_Object::DeleteSpecificChildren(Game_Object* ObjectToDelete)
{

	if (Children_List.size() > 0) {

		for (int i = 0; i < Children_List.size(); ++i) {

			
			if (Children_List[i] == ObjectToDelete) {

				Children_List[i]->CleanUp();

				delete 	Children_List[i];

				Children_List.erase(Children_List.begin() + i);
			}
		}
	}
}

void Game_Object::DeleteAllChildren()
{
	
	if (Children_List.size() > 0) {

		for (int i = 0; i < Children_List.size(); ++i) {

			//Children_List[i]->CleanUp();

			delete Children_List[i];

		}

		Children_List.clear();
	}
}

void Game_Object::Enable()
{
	this->Enabled = true;
}

void Game_Object::Disable()
{
	this->Enabled = false;
}

void Game_Object::Update()
{
	if (Component_List.size() > 0) {

		std::vector<Component*>::iterator It = Component_List.begin();
		bool ret = true;

		for (; It != Component_List.end() && ret == true; ++It) {
			(*It)->Update();
		}

	}



}

void Game_Object::CleanUp()
{
}
