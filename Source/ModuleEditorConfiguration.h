

#pragma once

#ifndef __ModuleEditorConfig_H__
#define __ModuleEditorConfig_H__


#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include <vector>
#include "libraries/ImGUI/imgui.h"

struct GPU_Status {

	char* model_name;
	char* renderer_name;
	char* version;


};

struct CPU_Status {

	int CPU_Count;
	int Cache_size;
	int System_Ram;
	bool isActive_3D;
	bool isActive_AVX2;
	bool isActive_AVX;
	bool isActive_AltiVec;
	bool isActive_MMX;
	bool isActive_RDTSC;
	bool isActive_SSE;
	bool isActive_SSE2;
	bool isActive_SSE3;
	bool isActive_SSE41;
	bool isActive_SSE42;

};

struct Hardware_Status {

	GPU_Status GPU;
	CPU_Status CPU;


};


class ModuleEditorConfiguration : public Module
{
public:

	ModuleEditorConfiguration(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleEditorConfiguration();

	Hardware_Status HardwareStat;

	// ---------------Config Window---------------
	void CreateConfigWindow();
	void CreateConfigWindow_Options();
	void CreateConfigWindow_Application();
	void CreateConfigWindow_Window();
	void CreateConfigWindow_FileSystem();
	void CreateConfigWindow_Input();
	void CreateConfigWindow_Hardware();
	void GetHardwareStatus();

	bool vSync = true;

	float brightness;

	bool active_window;
	bool active_fullscreen;
	bool active_Resizable;
	bool active_Borderless;
	bool active_Full_Desktop;
	
}; 

#endif