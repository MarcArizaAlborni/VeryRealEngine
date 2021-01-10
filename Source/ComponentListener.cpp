#include "ComponentListener.h"
#include "ModuleAudio.h"
#include "Component.h"
#include "GameObject.h"
#include "ComponentTransform.h"

Component_Listener::Component_Listener(Game_Object* ComponentOwner) :Component(ComponentOwner)
{
	type = Component_Types::Listener;
	owner = ComponentOwner;
	float3 Position;
	//For Positions

	Component_Transform* Trans_Cmp = (Component_Transform*)owner->GetComponent(Component_Types::Transform);

	Position = Trans_Cmp->GetPosition();

	WiseItem = WiseItem->CreateAudioListener(owner->item_id, owner->name.c_str(), Position);
	
}

Component_Listener::~Component_Listener()
{

}

void Component_Listener::Update()
{

}
