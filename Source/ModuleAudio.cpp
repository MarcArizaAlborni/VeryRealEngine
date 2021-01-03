#include "ModuleAudio.h"
#include "Application.h"
#include "Globals.h"
#include "ModuleEditor.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "GameObject.h"
#include "ComponentTransform.h"
#include "ComponentCamera.h"
#include "Component.h"
#include "ModuleCamera3D.h"
#include "FileSystem.h"
#include "..\Game\Assets\Audio\Wwise_IDs.h"
#include "wwise.h"
#include "ComponentSource.h"
#include "ComponentListener.h"
#include "ComponentMesh.h"
#include "ModuleScene.h"
#include "libraries/Wwise/IO/Win32/AkFilePackageLowLevelIOBlocking.h"
#pragma comment( lib, "libraries/PhysFS/libx86/physfs.lib" )
#include "libraries/PhysFS/include/physfs.h"
#include <fstream>
#include <string>

//#include "..\Wwise/AK/SoundEngine/Common/AkTypes.h"


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

    /*Reverb_Audio();*/


    UpdateSpatialObjectsInfo();

    

    

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

void ModuleAudio::UpdateSpatialObjectsInfo()
{
    std::vector<Game_Object*>::iterator It = App->scene->ROOT_SCENE_OBJECT->Children_List.begin();
    for (int i = 0; i<App->scene->ROOT_SCENE_OBJECT->Children_List.size(); ++i) {

        Game_Object* Object = *It;

        UpdateSpatialObjectsInfoChilds(Object);

            ++It;
    }

}

void ModuleAudio::UpdateSpatialObjectsInfoChilds(Game_Object* Parent)
{


    std::vector<Game_Object*>::iterator It = Parent->Children_List.begin();
    for (int i = 0; i < Parent->Children_List.size(); ++i) {

        Game_Object* Object = *It;


       Component_Mesh* ComponentMeshesChild = (Component_Mesh*)Object->GetComponent(Component_Types::Mesh);
     
       Component_Source* SourceCmp = (Component_Source*)Object->GetComponent(Component_Types::Source);
       
       if (SourceCmp != nullptr) {

           if (SourceCmp->isSpatialDependant) {

               vec CameraPos = { App->camera->scene_camera->Position.x,App->camera->scene_camera->Position.y, App->camera->scene_camera->Position.z };

               if (!ComponentMeshesChild->global_OBB.Contains(CameraPos)) {

                   SourceCmp->WiseItem->SetVolume(SourceCmp->id, 0);
                  // SourceCmp->WiseItem->PauseEvent(SourceCmp->id);
               }
               else {
                   SourceCmp->WiseItem->SetVolume(SourceCmp->id, 0);
                   //SourceCmp->WiseItem->ResumeEvent(SourceCmp->id);
               }

               int val = SourceCmp->id;
           }
           
       }

       if (ComponentMeshesChild != nullptr) {
           if (Object->isAudioDistanceObject) {
               ComponentMeshesChild->UpdateOnTransformOBB(); //memory leak here


             

           }
       }


      



        UpdateSpatialObjectsInfoChilds(Object);

        ++It;
    }




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

void ModuleAudio::Reverb_Audio()
{
    Component_Mesh* fish = (Component_Mesh*)App->scene->Dynamic_Source->GetComponent(Component_Types::Mesh);

    Component_Transform* fish_trans = (Component_Transform*)App->scene->Dynamic_Source->GetComponent(Component_Types::Transform);
   
    Component_Mesh* tunnel = (Component_Mesh*)App->scene->Reverb_Source->GetComponent(Component_Types::Mesh);

    vec point = { fish_trans->Translation.x,fish_trans->Translation.y,fish_trans->Translation.z };
    /*vec point = { App->camera->scene_camera->Position.x,App->camera->scene_camera->Position.y, App->camera->scene_camera->Position.z };*/

    if (tunnel->global_OBB.Contains(point))
    {
       
        /*if (!reverb)
        {
            App->scene->train->GetComponent(Component::AUDIOSOURCE)->AsAudioSource()->sound_go->SetAuxiliarySends(1.0f, "env_tunnel", App->scene->audiolistenerdefault->GetComponent(Component::AUDIOLISTENER)->AsAudioListener()->sound_go->GetID());
            reverb = true;
        }*/
    }
    else
    {
        /*if (reverb)
        {
            App->scene->train->GetComponent(Component::AUDIOSOURCE)->AsAudioSource()->sound_go->SetAuxiliarySends(1.0f, "env_normal", App->scene->audiolistenerdefault->GetComponent(Component::AUDIOLISTENER)->AsAudioListener()->sound_go->GetID());
            reverb = false;
        }*/
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

void WwiseObjects::SetAuxiliarySends(AkReal32 value, const char* target_bus, AkGameObjectID listener_id)
{
    AkAuxSendValue reverb;
    reverb.listenerID = listener_id;
    reverb.auxBusID = AK::SoundEngine::GetIDFromString(target_bus);
    reverb.fControlValue = value;

    AKRESULT res = AK::SoundEngine::SetGameObjectAuxSendValues(listener_id, &reverb, 0);
}

uint WwiseObjects::GetID()
{
    return id;
}


