#ifndef __ModuleScene_H__
#define __ModuleScene_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#include "JScene.h"

#include "libraries/imGuizmo/ImGuizmo.h"

class Game_Object;
class Component;
class Component_Transform;
class Component_Camera;
class Component_Source;
class Component_Listener;
class ImportSettings;

class ModuleScene : public Module
{
public:

	ModuleScene(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleScene();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	bool ResetScene();
	void SaveScene();
	bool LoadScene();

	bool camera_culling = false;
	
	Game_Object* ROOT_SCENE_OBJECT = nullptr;
	Game_Object* object_scene_camera = nullptr;

	//Guizmos
	void GuizmoDrawn();
	void ChangeOperationGuizmo(ImGuizmo::OPERATION& op);

	ImGuizmo::OPERATION gizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
	ImGuizmo::MODE gizmoMode = ImGuizmo::MODE::WORLD;

	Game_Object* ObjectToBeDeleted;

	void RemoveSelectedItem(Game_Object* Object);

	int Game_Objects_IdGen = 0;
	
public:
	Game_Object* LookForSelectedChild(Game_Object* obj);

public:
	//Audios
	Game_Object* background_music = nullptr;
	Game_Object* background_music_2 = nullptr;


private:

	void LoadStaticSoundSource();
	void LoadDynamicSoundSource();
	void LoadMusicSource();


private: //Timer Rotation Music

	bool StartMusic2 = true;
	Timer MusicPlaylistTimer;
	int MusicPlaylistTime;

	bool PlayingMus1 = false;
	bool PlayingMus2 = false;
	bool SwapMusic = false;

	void RotateMusics();

	void AudioControlls();

};

#endif // __ModuleScene_H__