#include "Component_AudioSource.h"
#include "Component.h"
#include "GameObject.h"

Component_AudioSource::Component_AudioSource(Game_Object* ComponentOwner) :Component(ComponentOwner)
{

	owner = ComponentOwner;
	type = Component_Types::Source;

	
	sound_go = Wwise::CreateSoundObj(owner->item_id, owner->name.c_str(), 0,0,0);

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
