#include "ModuleAudio.h"
#include "Application.h"
#include "Globals.h"
#include "FileSystem.h"
#include "..\Game\Assets\Audio\Wwise_IDs.h"
#include "wwise.h"
#include "libraries/Wwise/IO/Win32/AkFilePackageLowLevelIOBlocking.h"
#pragma comment( lib, "libraries/PhysFS/libx86/physfs.lib" )
#include "libraries/PhysFS/include/physfs.h"
#include <fstream>
#include <string>

// We're using the default Low-Level I/O implementation that's part
// of the SDK's sample code, with the file package extension




CAkDefaultIOHookBlocking g_lowLevelIO;

ModuleAudio::ModuleAudio(Application* app, const char* name, bool start_enabled) : Module(app, "Audio", start_enabled)
{
}

ModuleAudio::~ModuleAudio()
{
}

bool ModuleAudio::Init()
{
    //Memory
    AkMemSettings memSettings;
    memSettings.uMaxNumPools = 20;

    if (AK::MemoryMgr::Init(&memSettings) != AK_Success)
    {
        LOG("Could not create the memory manager.");

        return false;
    }

    // Create and initialize an instance of the default streaming manager
    AkStreamMgrSettings stmSettings;
    AK::StreamMgr::GetDefaultSettings(stmSettings);

    if (!AK::StreamMgr::Create(stmSettings))
    {
        LOG("Could not create the Streaming Manager");

        return false;
    }

    // Create a streaming device with blocking low-level I/O handshaking.
    AkDeviceSettings deviceSettings;

    AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);

    if (g_lowLevelIO.Init(deviceSettings) != AK_Success)
    {

        LOG("Could not create the streaming device and Low-Level I/O system");

        return false;
    }

    // Create the Sound Engine using default initialization parameters
    AkInitSettings initSettings;

    AkPlatformInitSettings platformInitSettings;

    AK::SoundEngine::GetDefaultInitSettings(initSettings);

    AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);


    if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) != AK_Success)
    {
        LOG("Could not initialize the Sound Engine.");

        return false;
    }
    
    // Initialize the music engine using default initialization parameters
    AkMusicSettings musicInit;

    AK::MusicEngine::GetDefaultInitSettings(musicInit);

    if (AK::MusicEngine::Init(&musicInit) != AK_Success)
    {
        LOG("Could not initialize the Music Engine.");

        return false;
    }

    // Initialize Spatial Audio using default initialization parameters
    //AkSpatialAudioInitSettings settings; // The constructor fills AkSpatialAudioInitSettings with the recommended default settings. 

    //if (AK::SpatialAudio::Init(settings) != AK_Success)
    //{
    //    LOG("Could not initialize the Spatial Audio.");

    //    return false;
    //}

#ifndef AK_OPTIMIZED

    // Initialize communications (not in release build!)

    AkCommSettings commSettings;
    AK::Comm::GetDefaultInitSettings(commSettings);

    if (AK::Comm::Init(commSettings) != AK_Success)
    {
        LOG("Could not initialize communication.");

        return false;
    }

#endif // AK_OPTIMIZED


    AkBankID bankID;
    AKRESULT retValue;
    retValue = AK::SoundEngine::LoadBank(BANKS_INIT_PATH, AK_DEFAULT_POOL_ID, bankID);



    std::vector<std::string> banks;
    ReadFileBanks(&banks);


    for (std::vector<std::string>::iterator it = banks.begin(); it != banks.end(); ++it)
    {
        LoadBank((*it).c_str());
    }

	return true;
}

bool ModuleAudio::Start()
{

   

    //LoadEventsFromJson();
   

   
       
    
	return true;
}

update_status ModuleAudio::Update(float dt)
{
	int a = 0;
	return UPDATE_CONTINUE;
}

bool ModuleAudio::CleanUp()
{
#ifndef AK_OPTIMIZED
    // Terminate Communication Services
    AK::Comm::Term();
#endif // AK_OPTIMIZED

    // Terminate Music Engine
    AK::MusicEngine::Term();

    // Terminate Sound Engine
    AK::SoundEngine::Term();

    // Terminate Streaming Manager
    g_lowLevelIO.Term();
    if (AK::IAkStreamMgr::Get())
        AK::IAkStreamMgr::Get()->Destroy();

    // Terminate Memory Manager
    AK::MemoryMgr::Term();

	return true;
}

void ModuleAudio::ReadFileBanks(std::vector<std::string>* soundbanks)
{
    std::vector<std::string> files;
    DetectAudioBanks(BANKS_PATH, files);

    
    std::string extension = "bnk";
    std::string file_extension;
    std::string file_name;
    for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it)
    {
        App->filemanager->SplitFilePath((*it).c_str(), nullptr, &file_name, &file_extension);
        if (!file_extension.compare(extension)) 
        {
            App->filemanager->DeleteExtension(file_name);
            if (!file_name.compare("Init")) {  
                continue;
            }

            soundbanks->push_back(file_name);
        }
    }
}

void ModuleAudio::DetectAudioBanks(const char* directory, std::vector<std::string>& file_list)
{

    char** rc = PHYSFS_enumerateFiles(directory);
    char** i;

    std::string dir(directory);

    for (i = rc; *i != nullptr; i++) {
        if (!PHYSFS_isDirectory((dir + *i).c_str())) {
            file_list.push_back(*i);
        }
    }

    PHYSFS_freeList(rc);
}

void ModuleAudio::LoadBank(const char* path)
{
    std::string fullPath = "Assets/Audio/";
    fullPath += path;
    fullPath += ".bnk";

    AkBankID bankID;

  
    if (App->filemanager->Exists(fullPath.c_str())) {
      AKRESULT Res=  AK::SoundEngine::LoadBank(fullPath.c_str(), AK_DEFAULT_POOL_ID, bankID);
      if (Res == AK_Success) {
          LOG("Bank %s Loaded Correctly", fullPath.c_str());
        }
    }
}

void ModuleAudio::LoadEventsFromJson()
{
    std::vector<std::string> jsonlist;
    ReadFileBanks(&jsonlist);

    for (std::vector<std::string>::iterator it = jsonlist.begin(); it != jsonlist.end(); ++it)
    {

        std::string path = "Assets/Audio/" + (*it) + ".json";

        uint Id = 0;
        //std::string name;
      
        json File = App->LoaderJson()->Load(path.c_str());
       
        
        json Events = File["SoundBanksInfo"]["SoundBanks"][0]["IncludedEvents"];
       

        for (uint i = 0; i < Events.size(); ++i)
        {
            json node = Events[i];

            std::string idstring = node["Id"];
            std::string namestring = node["Name"];
            Id = std::stoul(idstring);

           
        }

        uint i = 0;

        
    }
}


//WWISE OBJECTS


WwiseObjects::WwiseObjects(unsigned __int64 id, const char* name)
{
    this->id = id;
    this->name = name;

    AK::SoundEngine::RegisterGameObj(this->id, this->name);
}

WwiseObjects::~WwiseObjects()
{
    AK::SoundEngine::UnregisterGameObj(id);
}

void WwiseObjects::SetPosition(float posX, float posY, float posZ, float frontX, float frontY, float frontZ, float topX, float topY, float topZ)
{
    position.X = -posX;
    position.Y = posY;
    position.Z = -posZ;

    orientationFront.X = frontX;
    orientationFront.Y = frontY;
    orientationFront.Z = frontZ;

    orientationTop.X = topX;
    orientationTop.Y = topY;
    orientationTop.Z = topZ;

    AkSoundPosition soundPosition;
    soundPosition.Set(position, orientationFront, orientationTop);
    AK::SoundEngine::SetPosition(id, soundPosition);
}

void WwiseObjects::PlayEvent(uint id)
{
    AK::SoundEngine::PostEvent(id, this->id);
}

void WwiseObjects::PauseEvent(uint id)
{
    AK::SoundEngine::ExecuteActionOnEvent(id, AK::SoundEngine::AkActionOnEventType::AkActionOnEventType_Pause, this->id);
}

void WwiseObjects::ResumeEvent(uint id)
{
    AK::SoundEngine::ExecuteActionOnEvent(id, AK::SoundEngine::AkActionOnEventType::AkActionOnEventType_Resume, this->id);
}

void WwiseObjects::StopEvent(uint id)
{
   AK::SoundEngine::ExecuteActionOnEvent(id, AK::SoundEngine::AkActionOnEventType::AkActionOnEventType_Stop, this->id);
}



WwiseObjects* WwiseObjects::CreateAudioSource(uint id, const char* name, float3 position)
{
    WwiseObjects* Object = new WwiseObjects(id, name);
    Object->SetPosition(position.x, position.y, position.z);

    return Object;
}

WwiseObjects* WwiseObjects::CreateAudioListener(uint id, const char* name, float3 position)
{
    WwiseObjects* Object = new WwiseObjects(id, name);

    AkGameObjectID ListenerID = Object->GetID();

    int ListenerAmount = 1;

    AK::SoundEngine::SetDefaultListeners(&ListenerID, ListenerAmount);

    Object->SetPosition(position.x, position.y, position.z);

    App->audio->CurrentListenerID = ListenerID;

    return Object;
}



uint WwiseObjects::GetID()
{
    return id;
}
