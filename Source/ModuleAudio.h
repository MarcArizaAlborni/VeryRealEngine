#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include <vector>
#include <string>

#include "libraries/Wwise/AK/SoundEngine/Common/AkTypes.h"

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
	bool CleanUp();


	
	

	void LoadEventsFromJson();

	AkGameObjectID CurrentListenerID;

	void LoadSoundBank(const char* path);


	AkBankID Currently_Loaded_BankID = 0;

private:

	void DetectAudioBanks(const char* directory, std::vector<std::string>& file_list);
	
	void SetUpWwise();

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
