#pragma once
#include "Module.h"


//#include "libraries/imgui/imgui.h"
//#include "libraries/imgui/imgui_impl_opengl3.h"
//
//#include "libraries/imgui/imgui_impl_sdl.h"
//
//#include "libraries/glew/include/GL/glew.h"



//#include "libraries/MathGeoLib/include/MathGeoLib.h"






class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

public:


	//ImGuiIO* io = nullptr;

};
