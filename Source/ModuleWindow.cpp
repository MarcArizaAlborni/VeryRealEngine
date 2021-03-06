#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleScene.h"
#include "ModuleEditor.h"
#include "GameObject.h"
#include "ModuleCamera3D.h"
#include "Component.h"
#include "ComponentCamera.h"
#include "ModuleInput.h"


ModuleWindow::ModuleWindow(Application* app, const char* name, bool start_enabled) : Module(app,"Window", start_enabled)
{
	window = NULL;
	screen_surface = NULL;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	
	LOG("Init SDL window & surface");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		WindowInformation.width=SCREEN_WIDTH* SCREEN_SIZE;
	
		WindowInformation.height= SCREEN_HEIGHT * SCREEN_SIZE;
		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if (WIN_FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if (WIN_RESIZABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if (WIN_BORDERLESS == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if (WIN_FULLSCREEN_DESKTOP == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		if (WIN_MAXIMIZED == true) {

			flags |= SDL_WINDOW_MAXIMIZED;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowInformation.width, WindowInformation.height, flags);

		if (window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}



	return ret;
}

update_status ModuleWindow::Update(float dt)
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::SetTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}

// BRIGHTNESS
float ModuleWindow::GetBrightness() const
{
	return window_brightness;
}

void ModuleWindow::ChangeWindowBrightnessTo(float brightness)
{
	if (brightness < 0.000f)
	{
		brightness = 0.000f;
	}
		
	else if 
		(brightness > 1.000f)
		brightness = 1.000f;

	SDL_SetWindowBrightness(window, brightness);

	window_brightness = brightness;
}

// WINDOWS GETTERS
bool ModuleWindow::GetFullscreen() const
{
	return window_fullscreen;
}

bool ModuleWindow::GetResizable() const
{
	return window_resizable;
}

bool ModuleWindow::GetBorderless() const
{
	return window_borderless;
}

bool ModuleWindow::GetFullDesktop() const
{
	return window_full_desktop;
}


// WINDOWS SETTERS
void ModuleWindow::SetFullscreen(bool fullscreen)
{
	if (fullscreen)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		SDL_SetWindowFullscreen(window, 0);
	}
		

	window_fullscreen = fullscreen;
}

void ModuleWindow::SetResizable(bool resizable)
{
	/*SDL_SetWindowResizable(window, (SDL_bool)resizable);*/

	window_resizable = resizable;
}

void ModuleWindow::SetFullScreenDesktop(bool fullscreen_desktop)
{
	if (fullscreen_desktop)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
		
	else
	{
		SDL_SetWindowFullscreen(window, 0);
	}
		
	window_full_desktop = fullscreen_desktop;
}

int ModuleWindow::GetWindow_Height()
{
	
	int Height;
	int Width;
	SDL_GetWindowSize(window, &Width, &Height);

	return Height;
}

int ModuleWindow::GetWindow_Width()
{
	int Height;
	int Width;
	SDL_GetWindowSize(window, &Width, &Height);

	return Width;
}


void ModuleWindow::SetBorderless(bool borderless)
{
	SDL_SetWindowBordered(window, (SDL_bool)!borderless); // If true enables borders, If false sets borderless flag

	window_borderless = borderless;
}