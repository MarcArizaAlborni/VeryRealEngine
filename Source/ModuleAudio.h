#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include <vector>
#include <string>

#include "libraries/Wwise/AK/SoundEngine/Common/AkTypes.h"
#include "ModuleGeometryManager.h"

#define BANKS_PATH "Assets/Audio/"
#define BANKS_INIT_PATH "Assets/Audio/Init.bnk"

class ModuleAudio : public Module
{
public:

	ModuleAudio(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleAudio();
	bool Init();
	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	bool CleanUp();


	void CreateAudioWindow();
	
	void Reverb_Audio();
	
	void LoadEventsFromJson();

	AkGameObjectID CurrentListenerID;

	void LoadSoundBank(const char* path);


	AkBankID Currently_Loaded_BankID = 0;

private:

	void DetectAudioBanks(const char* directory, std::vector<std::string>& file_list);
	
	void SetUpWwise();

	void UpdateSpatialObjectsInfo();

	void UpdateSpatialObjectsInfoChilds(Game_Object* Parent);

};


class WwiseObjects {


	WwiseObjects(unsigned __int64 id, const char* name);
	~WwiseObjects();


public:
	void SetPosition(float posX = 0, float posY = 0, float posZ = 0, float frontX = 1, float frontY = 0, float frontZ = 0, float topX = 0, float topY = 1, float topZ = 0);
	void PlayEvent(uint id);
	void PauseEvent(uint id);
	void ResumeEvent(uint id);
	void StopEvent(uint id);
	
	WwiseObjects* CreateAudioSource(uint id, const char* name, float3 position);
	WwiseObjects* CreateAudioListener(uint id, const char* name, float3 position);

	void SetAuxiliarySends(AkReal32 value, const char* target_bus, AkGameObjectID listener_id);

	void SetVolume(uint id, float volume);
	

public:
	uint GetID();

public:
	float volume = 1.0f;

private:
	const char* name = nullptr;
	AkGameObjectID id;

	AkVector position = { 0,0,0 };
	AkVector orientationFront = { 0,0,0 };
	AkVector orientationTop = { 0,0,0 };
};

#endif  
