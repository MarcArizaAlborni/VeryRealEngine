#ifndef _ComponentSource_H_
#define _ComponentSource_H_

#include "Component.h"
#include "Wise_Objects.h"
#include "..\Game\Assets\Audio\Wwise_IDs.h"

class Wwise_Object;

class Component_AudioSource : public Component
{
public:
	Component_AudioSource(Game_Object* ComponentOwner);
	~Component_AudioSource();

	void Update() override;
	

	//Value Save(Document::AllocatorType& allocator) const override;
	//bool Load(Document& document) override;

	void SetSoundID(AkUniqueID ID);

public:
	Wwise::WwiseGameObject* sound_go = nullptr;
	AkUniqueID sound_ID = 0;
};

#endif