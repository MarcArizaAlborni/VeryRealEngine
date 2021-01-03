#ifndef _COMPONENT_AUDIO_REVERB_H_
#define _COMPONENT_AUDIO_REVERB_H_

#include "Component.h"


class Component_Reverb : public Component
{
public:
	Component_Reverb(Game_Object* ComponentOwner);
	~Component_Reverb();

	void Update() override;

};

#endif