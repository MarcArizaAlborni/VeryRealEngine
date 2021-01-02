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

	// If we want to create a distance delimiter for audio sources

	isSpatialDependant = is_Spatial;

	if (is_Spatial) {


		owner = ComponentOwner;

		App->meshimporter->LoadFile_Mesh("Assets/Models/Primitives/LowPoly_Sphere.FBX");

		// We set the name and the wireframe to the sphere
		App->scene->ROOT_SCENE_OBJECT->Children_List[App->scene->ROOT_SCENE_OBJECT->Children_List.size() - 1]->Children_List[0]->name;
		App->scene->ROOT_SCENE_OBJECT->Children_List[App->scene->ROOT_SCENE_OBJECT->Children_List.size() - 1]->Children_List[0]->name = "Source Spatial Area";
		App->scene->ROOT_SCENE_OBJECT->Children_List[App->scene->ROOT_SCENE_OBJECT->Children_List.size() - 1]->Children_List[0]->is_Wireframed = true;
		App->scene->ROOT_SCENE_OBJECT->Children_List[App->scene->ROOT_SCENE_OBJECT->Children_List.size() - 1]->Children_List[0]->isAudioDistanceObject = true;


		//We get the component transform of the sphere and the general mesh

		Component_Transform* Spatial_Sphere = (Component_Transform*)App->scene->ROOT_SCENE_OBJECT->Children_List[
			App->scene->ROOT_SCENE_OBJECT->Children_List.size() - 1]->Children_List[0]->GetComponent(Component_Types::Transform);

		Component_Transform* Trans_Cmp = (Component_Transform*)owner->GetComponent(Component_Types::Transform);

		//We set the translation to be equal to the one of the owner of the component source
		

		Spatial_Sphere->UpdateTransformationsObjects(Trans_Cmp->Translation, Spatial_Sphere->Scale, Spatial_Sphere->Rotation);

		//Here we add the game object as a child to the owner of the component source, instead of having one for itself
		App->scene->ROOT_SCENE_OBJECT->Children_List[App->scene->ROOT_SCENE_OBJECT->Children_List.size() - 2]->Children_List[0]->ChangeParentFromObject(App->scene->ROOT_SCENE_OBJECT->Children_List[App->scene->ROOT_SCENE_OBJECT->Children_List.size() - 1]->Children_List[0]);

		App->scene->ROOT_SCENE_OBJECT->Children_List.erase(App->scene->ROOT_SCENE_OBJECT->Children_List.end()-1);

		type = Component_Types::Source;

		float3 Position;



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
