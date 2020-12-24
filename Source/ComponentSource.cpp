#include "ComponentSource.h"
#include "ComponentListener.h"
#include "ModuleAudio.h"
#include "Component.h"
#include "GameObject.h"
#include "ComponentTransform.h"


Component_Source::Component_Source(Game_Object* ComponentOwner) :Component(ComponentOwner)
{

	owner = ComponentOwner;

	owner->name = "AudioSource";

	type = Component_Types::Source;

	float3 Position;
	//For Positions

	Component_Transform* Trans_Cmp = (Component_Transform*)owner->GetComponent(Component_Types::Transform);


	Position = Trans_Cmp->GetPosition();

	WiseItem = WiseItem->CreateAudioSource(owner->item_id, owner->name.c_str(), Position);
}

Component_Source::~Component_Source()
{
}

void Component_Source::Update()
{
}

void Component_Source::SetID(AkGameObjectID id)
{
	this->id = id;
}
