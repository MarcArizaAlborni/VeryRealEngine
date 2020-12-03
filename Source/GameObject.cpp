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
	AddExistingComponent(new Component_Transform(this));
	this->Parent = nullptr;	

	
	is_Wireframed = false;
	is_Checkered = false;
	showVertexNormals = false;
	is_Selected = false;

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

		Ret = new Component_Transform(this);
		UniqueComponent = true;


		break;

	case Component_Types::Camera:
		LOG("[WARNING]Component Camera added to GameObject");

		//Ret = new Component_Camera(this); WIP
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

			for (int i = 0; i < Component_List.size(); ++i) {

				if (typus == Component_List[i]->type) {
					LOG("[WARNING] Component to be added already exists!");

					delete Ret;
					Ret = nullptr;
					return nullptr;

				}
			}
			

		}

		Component_List.push_back(Ret);
	}
	else {
		LOG("[WARNING] Component doesn't exist");
	}

	return Ret;
}

Component* Game_Object::AddExistingComponent(Component* component)
{
	Component* Ret;

	switch (component->type)
	{
	case(Component_Types::None):
		//LOG("Component Type Error! Something broke...");
		break;
	case(Component_Types::Transform):
		Ret = new Component_Transform(this);
		Transformations = (Component_Transform*)component;
		break;
	case(Component_Types::Texture):
		if (this->GetComponent(Component_Types::Texture) != nullptr) {
			return nullptr;
		}
		Ret = new Component_Texture(this);
		Textures = (Component_Texture*)component;
		break;
	case(Component_Types::Mesh):
		Mesh = (Component_Mesh*)component;
		Ret = new Component_Mesh(this);
		break;

	}

	//components.push_back(ret);
	Component_List.push_back(component);


	return Ret;
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
	ObjectToAdd->Parent = this;

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

	std::vector<Game_Object*>::iterator It = this->Children_List.begin();

	for (int size = 0; size < this->Children_List.size(); ++size) {
		Game_Object* Item = *It;

		Item->Update();

		
		std::vector<Component*>::iterator It2 = Item->Component_List.begin();
		bool ret = true;

		for (; It2 != Item->Component_List.end() && ret == true; ++It2) {

			if ((*It2)->type == Component_Types::Mesh) {
				((Component_Mesh*)(*It2))->Update();
			}
		}
		
		++It;
	}




	//if (Component_List.size() > 0) {
	//
	//	std::vector<Component*>::iterator It = Component_List.begin();
	//	bool ret = true;
	//
	//	for (; It != Component_List.end() && ret == true; ++It) {
	//		(*It)->Update();
	//	}
	//
	//}



}

void Game_Object::CleanUp()
{
}
