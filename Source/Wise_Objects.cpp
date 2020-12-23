#include "Wise_Objects.h"
#include "wwise.h"
#include "Globals.h"
#include "libraries/Wwise/IO/Win32/AkFilePackageLowLevelIOBlocking.h"

Wwise::WwiseGameObject::WwiseGameObject(unsigned long idGO, const char* nameGO)
{
	ID = idGO;
	name = nameGO;
	AKRESULT eResult = AK::SoundEngine::RegisterGameObj(ID, name);
	if (eResult != AK_Success)
	{
		LOG("Failed to register GameObject to Wwise!");
	}
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
	ID;
	if (AK::SoundEngine::PostEvent(id, ID) == AK_INVALID_PLAYING_ID)
	{
		assert(!"Error playing event");
	}
}

void Wwise::WwiseGameObject::PauseEvent(unsigned long id)
{
}

void Wwise::WwiseGameObject::SetAuxiliarySends(AkReal32 value, const char* target_bus, AkGameObjectID listener_id)
{
}

Wwise::WwiseGameObject* Wwise::CreateSoundObj(unsigned long id, const char* name, float x, float y, float z, bool is_default_listener)
{
	WwiseGameObject* emitter = nullptr;

	emitter = new WwiseGameObject(id, name);

	if (is_default_listener)
	{
		AkGameObjectID listener_id = emitter->GetID();
		AK::SoundEngine::SetDefaultListeners(&listener_id, 1);
	}

	emitter->SetPosition(x, y, z);

	return emitter;
}

AkBankID Wwise::LoadBank(const char* name)
{
	return AkBankID();
}
