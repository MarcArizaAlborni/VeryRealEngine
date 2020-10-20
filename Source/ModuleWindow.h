#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"

#include "libraries/SDL/include/SDL.h"

class Application;


struct WindowInfo {
	
	int width;
	int height;
	bool Fullscreen;



};

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, const char* name = "null", bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

	void SetTitle(const char* title);

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;

	// WIndows Functions
	float GetBrightness() const;
	void ChangeWindowBrightnessTo(float brightness);

	bool GetFullscreen() const;
	bool GetResizable() const;
	bool GetBorderless() const;
	bool GetFullDesktop() const;

	void SetFullscreen(bool fullscreen);
	void SetBorderless(bool borderless);
	void SetResizable(bool resizable);
	void SetFullScreenDesktop(bool fullscreen_desktop);

	//Window Settings
	float window_brightness = 1.0f;

	bool window_fullscreen = false;
	bool window_resizable = true;
	bool window_borderless = false;
	bool window_full_desktop = false;

	WindowInfo WindowInformation;



	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
};

#endif // __ModuleWindow_H__