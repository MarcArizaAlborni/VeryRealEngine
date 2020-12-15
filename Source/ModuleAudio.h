#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include <vector>
#include <string>



class ModuleAudio : public Module
{
public:

	ModuleAudio(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleAudio();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();


	



};

#endif  
