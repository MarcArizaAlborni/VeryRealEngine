#include "ComponentReverb.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleScene.h"
#include "GameObject.h"
#include "ComponentTransform.h"
#include "ComponentCamera.h"
#include "ComponentSource.h"
#include "ComponentListener.h"
#include "ModuleInput.h"



Component_Reverb::Component_Reverb(Game_Object* ComponentOwner) :Component(ComponentOwner)
{
	owner = ComponentOwner;

	type = Component_Types::Reverb;
}

Component_Reverb::~Component_Reverb()
{
}


void Component_Reverb::Update()
{

	Component_Source* DynamicSource = (Component_Source*)App->scene->Dynamic_Source->GetComponent(Component_Types::Source);
	Component_Listener* Listener = (Component_Listener*)App->scene->object_scene_camera->GetComponent(Component_Types::Listener);
	DynamicSource->WiseItem->SetAuxiliarySends(1.0f, "Reverb", Listener->WiseItem->GetID());
	
}
