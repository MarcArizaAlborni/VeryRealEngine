#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"


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
	
	LOGFIX("Init SDL window & surface");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOGFIX("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
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

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowInformation.width, WindowInformation.height, flags);

		if (window == NULL)
		{
			LOGFIX("Window could not be created! SDL_Error: %s\n", SDL_GetError());
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

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOGFIX("Destroying SDL window and quitting all SDL systems");

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

void ModuleWindow::CreateConsolelog(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
	OutputDebugString(tmp_string2);


	App->console->ConsoleLogs.push_back(tmp_string2);
}

void ModuleWindow::SetBorderless(bool borderless)
{
	SDL_SetWindowBordered(window, (SDL_bool)!borderless); // If true enables borders, If false sets borderless flag

	window_borderless = borderless;
}