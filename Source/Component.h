#pragma once
#ifndef __Component_H__
#define __Component_H__
#include <string>
#include <vector>

class Game_Object;

enum class Component_Types {

	None=-1,
	Transform,
	Mesh,
	Texture,
	Camera

};

class Component {

public:

	Component(Game_Object* ComponentOwner) : Enabled(true), owner(ComponentOwner), type(Component_Types::None) {};

	Component_Types type;
	bool Enabled;
	Game_Object* owner;

	virtual void Enable() {};
	virtual void Disable() {};
	virtual void Update() {};
	virtual void CleanUp() {};

};


#endif