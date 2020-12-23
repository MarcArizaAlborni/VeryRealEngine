#include "Wise_Objects.h"

Wwise::WwiseGameObject::WwiseGameObject(unsigned long idGO, const char* nameGO)
{
}

Wwise::WwiseGameObject::~WwiseGameObject()
{
}

unsigned long Wwise::WwiseGameObject::GetID()
{
	return 0;
}

const char* Wwise::WwiseGameObject::GetName()
{
	return nullptr;
}

float3 Wwise::WwiseGameObject::GetPos()
{
	return float3();
}

void Wwise::WwiseGameObject::SetPosition(float x, float y, float z, float x_front, float y_front, float z_front, float x_top, float y_top, float z_top)
{
}

void Wwise::WwiseGameObject::PlayEvent(unsigned long id)
{
}

void Wwise::WwiseGameObject::PauseEvent(unsigned long id)
{
}

void Wwise::WwiseGameObject::SetAuxiliarySends(AkReal32 value, const char* target_bus, AkGameObjectID listener_id)
{
}

Wwise::WwiseGameObject* Wwise::CreateSoundObj(unsigned long id, const char* name, float x, float y, float z, bool is_default_listener)
{
	return nullptr;
}

AkBankID Wwise::LoadBank(const char* name)
{
	return AkBankID();
}
