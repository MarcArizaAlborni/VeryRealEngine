#include "ComponentSource.h"
#include "ComponentListener.h"
#include "ModuleAudio.h"
#include "Component.h"
#include "GameObject.h"
#include "ComponentTransform.h"
#include "Application.h"
#include "ModuleMeshImporter.h"
#include "ModuleScene.h"


Component_Source::Component_Source(Game_Object* ComponentOwner) :Component(ComponentOwner)
{

	owner = ComponentOwner;



	type = Component_Types::Source;

	float3 Position;
	

	Component_Transform* Trans_Cmp = (Component_Transform*)owner->GetComponent(Component_Types::Transform);


	Position = Trans_Cmp->GetPosition();

	WiseItem = WiseItem->CreateAudioSource(owner->item_id, owner->name.c_str(), Position);
}

Component_Source::Component_Source(Game_Object* ComponentOwner, bool is_Spatial) :Component(ComponentOwner)
{
	if (is_Spatial) {
		owner = ComponentOwner;

		App->meshimporter->LoadFile_Mesh("Assets/Models/Primitives/LowPoly_Sphere.FBX");

		App->scene->ROOT_SCENE_OBJECT->Children_List[App->scene->ROOT_SCENE_OBJECT->Children_List.size() - 1]->Children_List[0];

		

		type = Component_Types::Source;

		float3 Position;


		Component_Transform* Trans_Cmp = (Component_Transform*)owner->GetComponent(Component_Types::Transform);


		Position = Trans_Cmp->GetPosition();

		WiseItem = WiseItem->CreateAudioSource(owner->item_id, owner->name.c_str(), Position);
	}
	else {
		 
		//If isSpatial==false, we create a regular component source


		owner = ComponentOwner;

	

		type = Component_Types::Source;

		float3 Position;
		

		Component_Transform* Trans_Cmp = (Component_Transform*)owner->GetComponent(Component_Types::Transform);


		Position = Trans_Cmp->GetPosition();

		WiseItem = WiseItem->CreateAudioSource(owner->item_id, owner->name.c_str(), Position);
	}
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
