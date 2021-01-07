#ifndef __ComponentSource_H__
#define __ComponentSource_H__

#include "Component.h"
#include "libraries/Wwise/AK/SoundEngine/Common/AkTypes.h"

class WwiseObjects;

class Component_Source : public Component
{
public:
	Component_Source(Game_Object* ComponentOwner);
	Component_Source(Game_Object* ComponentOwner,bool is_Spatial);
	~Component_Source();

	void Update();


	void SetID(AkGameObjectID id);

public:

	WwiseObjects* WiseItem = nullptr;
	AkGameObjectID id = 0;
	bool isPaused = false;
	bool isPlaying = false;
	bool isStopped = false;
	bool isModified = false;
	bool isMuted = false;
	
	bool isSpatialDependant = false;

	bool isDistanceDependant = true;


};

#endif __C_AudioSource__H__