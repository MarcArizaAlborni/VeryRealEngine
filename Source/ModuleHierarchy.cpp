#include "Globals.h"
#include "Application.h"
#include "ModuleHierarchy.h"

ModuleHierarchy::ModuleHierarchy(Application* app, const char* name, bool start_enabled) : Module(app, name, start_enabled)
{
	

	
}

ModuleHierarchy::~ModuleHierarchy()
{}


bool ModuleHierarchy::Start()
{
	
	

	return true;
}

update_status ModuleHierarchy::Update(float dt)
{

	if (ShowHierarchyWindow == true) {

		HierarchyWindow();
	}

	return UPDATE_CONTINUE;
}

bool ModuleHierarchy::CleanUp()
{
	

	return true;
}

void ModuleHierarchy::HierarchyWindow()
{
}

void ModuleHierarchy::CreateConsolelog(const char file[], int line, const char* format, ...)
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