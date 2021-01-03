#pragma once

// Warning disabled ---
#pragma warning( disable : 4577 ) // Warning that exceptions are disabled
#pragma warning( disable : 4530 ) // Warning that exceptions are disabled

#include <windows.h>
#include <stdio.h>

// File System Directories
#define LIBRARY_FOLDER "/Library/"
#define LIBRARY_SCENE_FOLDER "/Library/Scenes/"
#define LIBRARY_TEXTURES_FOLDER "/Library/Textures/"
#define LIBRARY_MESH_FOLDER "/Library/Meshes/"
#define LIBRARY_MODELS_FOLDER "/Library/Models/"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define PI			3.14159265358979323846f
#define TWO_PI		6.28318530717958647692f
#define HALF_PI		1.57079632679489661923f
#define QUARTER_PI	0.78539816339744830961f
#define INV_PI		0.31830988618379067154f
#define INV_TWO_PI	0.15915494309189533576f
#define HAVE_M_PI

typedef unsigned __int64 uint64;
typedef unsigned __int32 uint32;
typedef unsigned int uint;

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 1024 
#define SCREEN_HEIGHT 768
#define SCREEN_SIZE 1
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE true
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define WIN_MAXIMIZED false

#define VSYNC true
#define TITLE "VeryRealEngine"

class Application;
extern Application* App;