#include "GameObject.h"

#include <vector>
#include "Application.h"
#include "ComponentCamera.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"
#include "ComponentTransform.h"

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

Component* Game_Object::AddComponent(Component* component)
{
	Component* Ret = nullptr;

	
	switch (component->type) {

	case(Component_Types::None):

		break;

	case(Component_Types::Mesh):
		
		break;

	case(Component_Types::Transform):

		break;

	case(Component_Types::Camera):

		break;

	case(Component_Types::Texture):

		break;

	default:
		//
		break;
	}

	Component_List.push_back(component);

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
