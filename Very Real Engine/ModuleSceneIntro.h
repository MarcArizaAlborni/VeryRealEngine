#pragma once
#include "Module.h"

#include "Globals.h"

#include "libraries/imgui/imgui.h"
#include "libraries/imgui/imgui_impl_opengl2.h"

#include "libraries/glew/include/GL/glew.h"

#include "libraries/MathGeoLib/include/MathGeoLib.h"


#define BOUNCER_TIME 200

struct PhysBody3D;
class Cube;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
};
