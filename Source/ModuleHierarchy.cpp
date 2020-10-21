#include "Globals.h"
#include "Application.h"
#include "ModuleHierarchy.h"

#include "libraries/ImGUI/imgui.h"
#include "libraries/ImGUI/imgui_internal.h"
#include "libraries/ImGUI/imgui_impl_sdl.h"
#include "libraries/ImGUI/imgui_impl_opengl3.h"

#include "libraries/Glew/include/GL/glew.h" 
#include "libraries/SDL/include/SDL_opengl.h"


ModuleHierarchyGameObject::ModuleHierarchyGameObject(Application* app, const char* name, bool start_enabled) : Module(app, name, start_enabled)
{
	

	
}

ModuleHierarchyGameObject::~ModuleHierarchyGameObject()
{}


bool ModuleHierarchyGameObject::Start()
{
	
	

	return true;
}

update_status ModuleHierarchyGameObject::Update(float dt)
{

	

	
	

	return UPDATE_CONTINUE;
}

bool ModuleHierarchyGameObject::CleanUp()
{
	

	return true;
}

void ModuleHierarchyGameObject::CreateHierarchyWindow()
{
	if (App->mainMenubar->show_hierarchy_window) {
		ImGui::Begin("Hierarchy",&App->mainMenubar->show_hierarchy_window);
		


		ImGui::End();

	}
}

void ModuleHierarchyGameObject::CreateConsolelog(const char file[], int line, const char* format, ...)
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