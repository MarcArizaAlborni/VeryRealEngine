#include "Component_AudioSource.h"
#include "Component.h"
#include "GameObject.h"

Component_AudioSource::Component_AudioSource(Game_Object* ComponentOwner) :Component(ComponentOwner)
{

	owner = ComponentOwner;
	type = Component_Types::Source;

   //
}

Component_AudioSource::~Component_AudioSource()
{
}

void Component_AudioSource::Update()
{
}

void Component_AudioSource::SetSoundID(AkUniqueID ID)
{
	sound_ID = ID;
}
