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


	void ModuleAudio::ReadFileBanks(std::vector<std::string>* soundbanks);
	void LoadBank(const char* path);

	void LoadEventsFromJson();
	
private:

	void DetectAudioBanks(const char* directory, std::vector<std::string>& file_list);
	


};

#endif  
