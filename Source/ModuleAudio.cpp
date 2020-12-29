#include "ModuleAudio.h"
#include "Application.h"
#include "Globals.h"
#include "ModuleEditor.h"
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

    SetUpWwise();

    LoadSoundBank("MyMusicBank");

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

update_status ModuleAudio::PostUpdate(float dt)
{
    AK::SoundEngine::RenderAudio();
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

void ModuleAudio::CreateAudioWindow()
{
    if (App->editor->show_audio_window) {

        ImGui::Begin("AudioManager");




        ImGui::Columns(3);

        ImGui::Text("General Audio Settings");

        ImGui::NextColumn();

        ImGui::Text("Available Audio Files");

        ImGui::NextColumn();

        ImGui::Text("Selected Audio Settings");

        ImGui::NextColumn();

        ImGui::Separator();


        //Column1

      
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();

        if (ImGui::Button("Stop All", { 75,20 })) {

            AK::SoundEngine::StopAll();

        }
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();

        if (ImGui::Button("Mute All", { 75,20 })) {

            
         
           // AK::SoundEngine::Query::GetPlayingIDsFromGameObject

        }

        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();

        if (ImGui::Button("Un-Mute All", { 80,20 })) {



        }
       
        ImGui::NextColumn();
        //Column2
        ImGui::Text("Column2");
        ImGui::NextColumn();
        //Column3
        ImGui::Text("Column3");
       

       

        ImGui::NextColumn();

       

        

      


       // AK::SoundEngine::StopAll();


        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE"); 
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");
        ImGui::Text("Audio Manager HERE");

        ImGui::End();




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

void ModuleAudio::SetUpWwise()
{
    //Memory
    AkMemSettings memSettings;
    memSettings.uMaxNumPools = 20;

    if (AK::MemoryMgr::Init(&memSettings) != AK_Success)
    {
        LOG("Could not create the memory manager.");

        //return false;
    }

    // Create and initialize an instance of the default streaming manager
    AkStreamMgrSettings stmSettings;
    AK::StreamMgr::GetDefaultSettings(stmSettings);

    if (!AK::StreamMgr::Create(stmSettings))
    {
        LOG("Could not create the Streaming Manager");

        //return false;
    }

    // Create a streaming device with blocking low-level I/O handshaking.
    AkDeviceSettings deviceSettings;

    AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);

    if (g_lowLevelIO.Init(deviceSettings) != AK_Success)
    {

        LOG("Could not create the streaming device and Low-Level I/O system");

        //return false;
    }

    // Create the Sound Engine using default initialization parameters
    AkInitSettings initSettings;

    AkPlatformInitSettings platformInitSettings;

    AK::SoundEngine::GetDefaultInitSettings(initSettings);

    AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);


    if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) != AK_Success)
    {
        LOG("Could not initialize the Sound Engine.");

        //return false;
    }

    // Initialize the music engine using default initialization parameters
    AkMusicSettings musicInit;

    AK::MusicEngine::GetDefaultInitSettings(musicInit);

    if (AK::MusicEngine::Init(&musicInit) != AK_Success)
    {
        LOG("Could not initialize the Music Engine.");

        //return false;
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

        //return false;
    }

#endif // AK_OPTIMIZED


    AkBankID bankID;
    AKRESULT retValue;
    retValue = AK::SoundEngine::LoadBank(BANKS_INIT_PATH, AK_DEFAULT_POOL_ID, bankID);
    assert(retValue == AK_Success);

}





void ModuleAudio::LoadSoundBank(const char* path)
{

    std::string fullPath = "Assets/Audio/";
    fullPath += path;
    fullPath += ".bnk";

  
    AKRESULT ResultVal=  AK::SoundEngine::LoadBank(fullPath.c_str(), AK_DEFAULT_POOL_ID, Currently_Loaded_BankID);


    if (ResultVal == AK_Success) {
        LOG("Bank %s Loaded Correctly", fullPath.c_str());
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

void WwiseObjects::SetVolume(uint id, float volume)
{
   AK::SoundEngine::SetGameObjectOutputBusVolume(this->id, AK_INVALID_GAME_OBJECT, volume);
    this->volume = volume;
}


uint WwiseObjects::GetID()
{
    return id;
}
