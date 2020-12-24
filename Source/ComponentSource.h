#ifndef __ComponentSource_H__
#define __ComponentSource_H__

#include "Component.h"
#include "libraries/Wwise/AK/SoundEngine/Common/AkTypes.h"

class WwiseObjects;

class Component_Source : public Component
{
public:
	Component_Source(Game_Object* ComponentOwner);
	~Component_Source();

	
	void Update();

	

	void SetID(AkGameObjectID id);

public:

	WwiseObjects* WiseItem = nullptr;
	AkGameObjectID id = 0;
	bool isPaused = false;
	bool isPlaying = false;
};

#endif __C_AudioSource__H__