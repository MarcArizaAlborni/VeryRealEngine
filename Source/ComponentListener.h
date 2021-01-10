#pragma once
#ifndef __ComponentListener_H__
#define __ComponentListener_H__

#include "Component.h"
#include "ModuleAudio.h"
#include "ComponentSource.h"

class WwiseObjects;

class Component_Listener :public Component {
public:

	Component_Listener(Game_Object* ComponentOwner);
	~Component_Listener();

	void Update();

	WwiseObjects* WiseItem = nullptr;
	AkGameObjectID id = 0;

};

#endif