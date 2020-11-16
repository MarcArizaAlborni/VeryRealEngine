#include "Globals.h"
#include "Application.h"
#include "ModuleEditorConsole.h"
#include "ModuleEditorMainMenuBar.h"

#include "libraries/ImGUI/imgui.h"
#include "libraries/ImGUI/imgui_internal.h"
#include "libraries/ImGUI/imgui_impl_sdl.h"
#include "libraries/ImGUI/imgui_impl_opengl3.h"

#include "libraries/Glew/include/GL/glew.h" 
#include "libraries/SDL/include/SDL_opengl.h"


ModuleEditorConsole::ModuleEditorConsole(Application* app, const char* name, bool start_enabled) : Module(app, "ModuleConsole", start_enabled)
{

}

ModuleEditorConsole::~ModuleEditorConsole()
{}

// -----------------------CONSOLE------------------------
void ModuleEditorConsole::CreateConsoleWindow()
{
	if (App->mainMenubar->show_console_window) {

		ImGui::Begin("Console", &App->mainMenubar->show_console_window);
		std::list<char*>::iterator Iterator = ConsoleLogs.begin();

		for (Iterator; Iterator != ConsoleLogs.end(); Iterator++) {


			ImGui::TextUnformatted(*Iterator);

		}

		ImGui::End();

	}

	LogsAmount = ConsoleLogs.size();

}


void ModuleEditorConsole::CreateConsolelog(const char file[], int line, const char* format, ...)
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


	ConsoleLogs.push_back(tmp_string2);

}
