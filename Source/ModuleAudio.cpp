#include "ModuleAudio.h"

ModuleAudio::ModuleAudio(Application* app, const char* name, bool start_enabled) : Module(app, "Audio", start_enabled)
{
}

ModuleAudio::~ModuleAudio()
{
}

bool ModuleAudio::Start()
{
	return true;
}

update_status ModuleAudio::Update(float dt)
{
	int a = 0;
	return UPDATE_CONTINUE;
}

bool ModuleAudio::CleanUp()
{
	return true;
}
