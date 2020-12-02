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






	default:
		break;
	}

	Component_List.push_back(component);

	return nullptr;
}

Component* Game_Object::GetComponent(Component_Types type)
{
	return nullptr;
}

void Game_Object::GenerateChildren(Game_Object* ObjectToAdd)
{
	this->Children_List.push_back(ObjectToAdd);
}

void Game_Object::DeleteSpecificChildren(Game_Object* ObjectToDelete)
{
}

void Game_Object::DeleteAllChildren()
{
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
}

void Game_Object::CleanUp()
{
}
