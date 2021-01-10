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
    DOOM_FILE_ID = AK::EVENTS::FIRST30;
    THOMAS_FILE_ID = AK::EVENTS::SECOND30;
    SHARK_FILE_ID = AK::EVENTS::FISH_DYNAMIC;
    PENGUIN_FILE_ID = AK::EVENTS::PENGUIN_STATIC;



    SetUpWwise();

    LoadSoundBank("MyMusicBank");

    return true;
}

bool ModuleAudio::Start()
{
    AK::SoundEngine::Suspend();
    //LoadEventsFromJson();

    return true;
}

update_status ModuleAudio::Update(float dt)
{

    Reverb_Audio();

    Speaker_Panning_Audio();
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

       


    

        ImGui::End();

    }
}



void ModuleAudio::AddSourceComponent(Game_Object* ParentGameObject, bool isSpatial)
{
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

  
    AkStreamMgrSettings stmSettings;
    AK::StreamMgr::GetDefaultSettings(stmSettings);

    if (!AK::StreamMgr::Create(stmSettings))
    {
        LOG("Could not create the Streaming Manager");

        //return false;
    }

   
    AkDeviceSettings deviceSettings;

    AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);

    if (g_lowLevelIO.Init(deviceSettings) != AK_Success)
    {

        LOG("Could not create the streaming device and Low-Level I/O system");

        //return false;
    }

   
    AkInitSettings initSettings;

    AkPlatformInitSettings platformInitSettings;

    AK::SoundEngine::GetDefaultInitSettings(initSettings);

    AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);


    if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) != AK_Success)
    {
        LOG("Could not initialize the Sound Engine.");

        //return false;
    }

  
    AkMusicSettings musicInit;

    AK::MusicEngine::GetDefaultInitSettings(musicInit);

    if (AK::MusicEngine::Init(&musicInit) != AK_Success)
    {
        LOG("Could not initialize the Music Engine.");

        
    }

    AkSpatialAudioInitSettings settings; 

   // if (AK::SpatialAudio::Init(settings) != AK_Success)
   // {
   //     LOG("Could not initialize the Spatial Audio.");
   // }

    

#ifndef AK_OPTIMIZED

    // Initialize communications (not in release build!)

    AkCommSettings commSettings;
    AK::Comm::GetDefaultInitSettings(commSettings);

    if (AK::Comm::Init(commSettings) != AK_Success)
    {
        LOG("Could not initialize communication.");

        
    }

#endif // AK_OPTIMIZED

    AkBankID bankID;
    AKRESULT retValue;
    retValue = AK::SoundEngine::LoadBank(BANKS_INIT_PATH, AK_DEFAULT_POOL_ID, bankID);
    assert(retValue == AK_Success);

}

void ModuleAudio::UpdateSpatialObjectsInfo()
{
 
   UpdateSpatialObjectsInfoChilds(App->scene->ROOT_SCENE_OBJECT);
   
}

void ModuleAudio::UpdateSpatialObjectsInfoChilds(Game_Object* Parent)
{


    std::vector<Game_Object*>::iterator It = Parent->Children_List.begin();
    for (int i = 0; i < Parent->Children_List.size(); ++i) {

        Game_Object* Object = *It;



        Component_Mesh* ComponentMeshesChild = (Component_Mesh*)Object->GetComponent(Component_Types::Mesh);

        Component_Source* SourceCmp = (Component_Source*)Object->GetComponent(Component_Types::Source);


        if (SourceCmp != nullptr) {

            if (SourceCmp->WiseItem->reset_vals == true)
            {

                SourceCmp->WiseItem->val_high = 0;
                SourceCmp->WiseItem->val_low = 0;
                SourceCmp->WiseItem->val_pitch = 0;

                SourceCmp->WiseItem->reset_vals = false;
            }
            else {

                AK::SoundEngine::SetRTPCValue("Pitch", SourceCmp->WiseItem->val_pitch, SourceCmp->WiseItem->GetID());
                AK::SoundEngine::SetRTPCValue("High_Pass", SourceCmp->WiseItem->val_high, SourceCmp->WiseItem->GetID());
                AK::SoundEngine::SetRTPCValue("Low_Pass", SourceCmp->WiseItem->val_low, SourceCmp->WiseItem->GetID());
            }

            if (SourceCmp->isSpatialDependant) {

                vec CameraPos = { App->camera->scene_camera->Position.x,App->camera->scene_camera->Position.y, App->camera->scene_camera->Position.z };

                Game_Object* SpatialObject = Object->Children_List[0];

                Component_Mesh* ComponentMeshesSpatialObj = (Component_Mesh*)SpatialObject->GetComponent(Component_Types::Mesh);

                Component_Transform* ComponentTransSpatialObj = (Component_Transform*)SpatialObject->GetComponent(Component_Types::Transform);

                SourceCmp->WiseItem->CenterPosition = ComponentMeshesSpatialObj->global_OBB.CenterPoint();

                float Finalvolume;

                if (ComponentMeshesSpatialObj->global_OBB.Contains(CameraPos)) {

                    SourceCmp->WiseItem->isOutofRange = false;




                     Finalvolume =  CalculateVolumeDistance(CameraPos, SourceCmp->WiseItem->CenterPosition);
                    
                     Finalvolume = (ComponentTransSpatialObj->Scale.x / Finalvolume) * SourceCmp->WiseItem->UserVolume;
                    
                     SourceCmp->WiseItem->SetSpatialVolume(SourceCmp->id, Finalvolume);

                }
                else {

                    SourceCmp->WiseItem->isOutofRange = true;

                    SourceCmp->WiseItem->SetSpatialVolume(SourceCmp->id, 0);

                }


                //SourceCmp->WiseItem->SetSpatialVolume(SourceCmp->id, 0);


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

float ModuleAudio::CalculateVolumeDistance(vec camPos, vec centPos)
{

    float Value;
    vec Position;

    Position.x = abs(camPos.x - centPos.x);
    Position.y = abs(camPos.y - centPos.y);
    Position.z = abs(camPos.z - centPos.z);

    if (Position.x < Position.y) {

        if (Position.y < Position.z) {


            return Position.z;
        }
        else if (Position.y > Position.z) {

            return Position.y;

        }
        else {
            return Position.z;
        }

    }
    else {
        if (Position.x < Position.z) {


            return Position.z;
        }
        else if (Position.x > Position.z) {

            return Position.x;

        }
        else {
            return Position.x;
        }
    }

}

void ModuleAudio::LoadSoundBank(const char* path)
{

    std::string fullPath = "Assets/Audio/";
    fullPath += path;
    fullPath += ".bnk";


    AKRESULT ResultVal = AK::SoundEngine::LoadBank(fullPath.c_str(), AK_DEFAULT_POOL_ID, Currently_Loaded_BankID);


    if (ResultVal == AK_Success) {
        LOG("Bank %s Loaded Correctly", fullPath.c_str());
    }

}

void ModuleAudio::Reverb_Audio()
{
    Component_Mesh* fish = (Component_Mesh*)App->scene->Dynamic_Source->GetComponent(Component_Types::Mesh);

    Component_Transform* fish_trans = (Component_Transform*)App->scene->Dynamic_Source->GetComponent(Component_Types::Transform);
    Component_Mesh* fish_trans_child = (Component_Mesh*)App->scene->Dynamic_Source->Children_List[0]->GetComponent(Component_Types::Mesh);

    Component_Mesh* tunnel = (Component_Mesh*)App->scene->Reverb_Source->GetComponent(Component_Types::Mesh);


    vec point = fish_trans_child->global_OBB.CenterPoint();


    //vec point = { App->camera->scene_camera->Position.x,App->camera->scene_camera->Position.y, App->camera->scene_camera->Position.z };

    Component_Source* DynamicSourceReverb = (Component_Source*)App->scene->Dynamic_Source->GetComponent(Component_Types::Source);

    if (tunnel->global_OBB.Contains(point))
    {
        AkRtpcValue val_fish = 100;
        AK::SoundEngine::SetRTPCValue("Fish_Position", val_fish, DynamicSourceReverb->WiseItem->GetID());

    }
    else
    {
        AkRtpcValue val_fish = 0;
        AK::SoundEngine::SetRTPCValue("Fish_Position", val_fish, DynamicSourceReverb->WiseItem->GetID());
    }

}

void ModuleAudio::Speaker_Panning_Audio()
{
    //Penguin
    Component_Transform* Penguin_Transform = (Component_Transform*)App->scene->Static_Source->GetComponent(Component_Types::Transform);
    Component_Mesh* Penguin_Mesh = (Component_Mesh*)App->scene->Static_Source->GetComponent(Component_Types::Mesh);
    Component_Source* StaticSourcePanning = (Component_Source*)App->scene->Static_Source->GetComponent(Component_Types::Source);


    Component_Transform* Camera_Transform = (Component_Transform*)App->scene->object_scene_camera->GetComponent(Component_Types::Transform);
   
    float3 CameraRotation=Camera_Transform->Rotation.ToEulerXYZ();
    
    vec CameraPosition = { App->camera->scene_camera->Position.x,App->camera->scene_camera->Position.y, App->camera->scene_camera->Position.z };
    

    //Angel lo confirma

    vec3 Matrix = App->camera->scene_camera->Z;
  
    vec CameraVector = { Matrix.x, Matrix.y,Matrix.z };

  
    
  vec TargetVector =  Penguin_Mesh->global_OBB.CenterPoint();

  vec DistanceVector = { TargetVector.x - CameraPosition.x,TargetVector.y - CameraPosition.y,TargetVector.z - CameraPosition.z };

  //(CameraVector.Abs()) * TargetVector.Abs());


 float AngleAdq= CameraVector.AngleBetween(TargetVector);


 float AngleDeg=RadToDeg(AngleAdq);
 
// float NewAngle = Acos((CameraVector.Dot(TargetVector) / (CameraVector.Abs() * TargetVector.Abs())));

  float Distance1 = TargetVector.x * TargetVector.x  + TargetVector.z * TargetVector.z;

  float Distance2 = CameraPosition.x * CameraPosition.x  + CameraPosition.z * CameraPosition.z;

  float Distance3= TargetVector.x * CameraPosition.x +  TargetVector.z * CameraPosition.z;

    CameraRotation.x;
    CameraRotation.y;
    CameraRotation.z;

    
  
  float Result_Angle = Acos(Distance3 / Sqrt(Distance1 * Distance2));
  float AngleDegG = RadToDeg(Result_Angle); //This one is the correct angle


   
    float3 Peng_Position = Penguin_Transform->Translation;
   
    vec CenterPointPeng = Penguin_Mesh->global_AABB.CenterPoint();

    if (Peng_Position.z > CameraPosition.z) { 

       

        AK::SoundEngine::SetRTPCValue("Penguin_Panning_Sides", 0, StaticSourcePanning->WiseItem->GetID());
       
           
        

    }
    else if (Peng_Position.z < CameraPosition.z) {

        AK::SoundEngine::SetRTPCValue("Penguin_Panning_Sides", 2, StaticSourcePanning->WiseItem->GetID());

    }
    else {

        AK::SoundEngine::SetRTPCValue("Penguin_Panning_Sides", 1, StaticSourcePanning->WiseItem->GetID());

    }



    //FISH
    Component_Transform* Fish_Transform = (Component_Transform*)App->scene->Dynamic_Source->GetComponent(Component_Types::Transform);
    Component_Mesh* Fish_Mesh = (Component_Mesh*)App->scene->Dynamic_Source->GetComponent(Component_Types::Mesh);
    Component_Source* DynamicSourcePanning = (Component_Source*)App->scene->Dynamic_Source->GetComponent(Component_Types::Source);

    float3 Fish_Position = Fish_Transform->Translation;

    vec CenterPointFish = Fish_Mesh->global_AABB.CenterPoint();

    if (Fish_Position.z > CameraPosition.z) {



        AK::SoundEngine::SetRTPCValue("Fish_Panning_Sides", 0, DynamicSourcePanning->WiseItem->GetID());




    }
    else if (Fish_Position.z < CameraPosition.z) {

        AK::SoundEngine::SetRTPCValue("Fish_Panning_Sides", 2, DynamicSourcePanning->WiseItem->GetID());

    }
    else {

        AK::SoundEngine::SetRTPCValue("Fish_Panning_Sides", 1, DynamicSourcePanning->WiseItem->GetID());

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

void WwiseObjects::SetSpatialVolume(uint id, float Newvolume)
{
    float FinalVolume;

    if (this->isOutofRange) {

        FinalVolume = 0;

    }
    else {

        FinalVolume = this->StoredVolume = Newvolume;

    }

    AK::SoundEngine::SetGameObjectOutputBusVolume(this->id, AK_INVALID_GAME_OBJECT, FinalVolume);

}

uint WwiseObjects::GetID()
{
    return id;
}


