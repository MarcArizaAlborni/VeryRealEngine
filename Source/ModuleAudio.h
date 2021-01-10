#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include <vector>
#include <string>

#include "libraries/Wwise/AK/SoundEngine/Common/AkTypes.h"
#include "ModuleGeometryManager.h"

#define BANKS_PATH "Assets/Audio/"
#define BANKS_INIT_PATH "Assets/Audio/Init.bnk"

#define MAX_VOLUME_AUDIO 2


enum class AudioFiles{

	SHARK,
	PENGUIN,
	DOOM,
	THOMAS
};


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

	void Speaker_Panning_Audio();

	void LoadEventsFromJson();

	AkGameObjectID CurrentListenerID;

	void LoadSoundBank(const char* path);


	AkBankID Currently_Loaded_BankID = 0;

	AudioFiles AudioFileType;


	void AddSourceComponent(Game_Object* ParentGameObject, bool isSpatial);


	uint DOOM_FILE_ID;
	uint THOMAS_FILE_ID;
	uint SHARK_FILE_ID;
	uint PENGUIN_FILE_ID;


private:

	void DetectAudioBanks(const char* directory, std::vector<std::string>& file_list);

	void SetUpWwise();

	void UpdateSpatialObjectsInfo();

	void UpdateSpatialObjectsInfoChilds(Game_Object* Parent);

	float CalculateVolumeDistance(vec camPos, vec centPos);

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

	void SetVolume(uint id, float volume);

	void SetSpatialVolume(uint id, float Newvolume);


public:
	uint GetID();

public:
	float volume = 1.0f;
	float StoredVolume = volume;
	float UserVolume = StoredVolume;
	bool isOutofRange = false;
	float  SpatialAreaOffset = 5;
	vec CenterPosition;

	//Effects panel
	AkRtpcValue val_pitch = 0;
	AkRtpcValue val_high = 0;
	AkRtpcValue val_low = 0;

	bool reset_vals = false;

private:
	const char* name = nullptr;
	AkGameObjectID id;

	AkVector position = { 0,0,0 };
	AkVector orientationFront = { 0,0,0 };
	AkVector orientationTop = { 0,0,0 };

};

#endif  
