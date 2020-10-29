#include "Globals.h"
#include "Application.h"
#include "ModuleEditorMainMenuBar.h"

#include "libraries/ImGUI/imgui.h"
#include "libraries/ImGUI/imgui_internal.h"
#include "libraries/ImGUI/imgui_impl_sdl.h"
#include "libraries/ImGUI/imgui_impl_opengl3.h"

#include "libraries/Glew/include/GL/glew.h" 
#include "libraries/SDL/include/SDL_opengl.h"


ModuleEditorMainMenuBar::ModuleEditorMainMenuBar(Application* app, const char* name, bool start_enabled) : Module(app, "ModuleMainMenuBar", start_enabled)
{

}

ModuleEditorMainMenuBar::~ModuleEditorMainMenuBar()
{}

bool ModuleEditorMainMenuBar::Start()
{
	show_about_window = false;
	show_hierarchy_window = true;
	show_console_window = true;
	show_inspector_window = true;
	return true;
}

// ----------------------------MENU BAR-------------------------------------
//Creation
void ModuleEditorMainMenuBar::CreateMainMenuBar() {

	//MenuEditor
	if (ImGui::BeginMainMenuBar())
	{
		CreateMainMenuBar_File();
		CreateMainMenuBar_Edit();
		CreateInsertPrimitivesWindow();
		CreateMainMenuBar_View();
		CreateMainMenuBar_Help();
		

		ImGui::EndMainMenuBar();
	}
}

//CREATION OF SUBMENUS
//---------FILE--------

void ModuleEditorMainMenuBar::CreateMainMenuBar_File() {

	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Quit", "ESC")) {

			App->input->ExitEngine = true;
		}
		ImGui::EndMenu();
	}
}

//----------EDIT-----------
void ModuleEditorMainMenuBar::CreateMainMenuBar_Edit() {

	if (ImGui::BeginMenu("Edit"))
	{
		if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}
		if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false)) {}  // Disabled item
		if (ImGui::MenuItem("Cut", "Ctrl+X")) {}
		if (ImGui::MenuItem("Copy", "Ctrl+C")) {}
		if (ImGui::MenuItem("Paste", "Ctrl+V")) {}

		ImGui::EndMenu();
	}
}

//-----------VIEW-----------
void ModuleEditorMainMenuBar::CreateMainMenuBar_View() {

	if (ImGui::BeginMenu("Window"))
	{
		ImGui::MenuItem("Console", "1", &show_console_window); //  We need to get 1 as input to close It
		ImGui::MenuItem("Configuration", "2", &show_config_window); // We need to get 4 as input to close It
		ImGui::MenuItem("Show GameObject Hierarchy", "3", &show_hierarchy_window);
		ImGui::MenuItem("Show GameObject Inspector", "4", &show_inspector_window);
		if (App->input->keyboard[SDL_SCANCODE_4]) {

			// Condition to enable/disable when clicking 4

		}

		ImGui::EndMenu();
	}
}

//---------------------HELP-----------------
void ModuleEditorMainMenuBar::CreateMainMenuBar_Help() {

	if (ImGui::BeginMenu("Help"))
	{
		if (ImGui::MenuItem("Gui Demo")) {};

		if (ImGui::MenuItem("Documentation"))
			App->RequestBrowser("https://github.com/MarcArizaAlborni/VeryRealEngine"); // Missing wiki

		if (ImGui::MenuItem("Download Latest"))
			App->RequestBrowser("https://github.com/MarcArizaAlborni/VeryRealEngine"); // Missing release

		if (ImGui::MenuItem("Report a bug"))
			App->RequestBrowser("https://github.com/MarcArizaAlborni/VeryRealEngine/issues");

		(ImGui::MenuItem("About", "", &show_about_window));

		ImGui::EndMenu();
	}
}



void ModuleEditorMainMenuBar::CreateConsolelog(const char file[], int line, const char* format, ...)
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

//--------------------INSERT PRIMITIVES-----------------
void ModuleEditorMainMenuBar::CreateInsertPrimitivesWindow()
{
	if (ImGui::BeginMenu("Insert"))
	{
		if (ImGui::BeginMenu("Create"))
		{
			if (ImGui::MenuItem("Plane"))
			{
				LOGFIX("Creating : Plane");
				drawplane = true;
			}
			if (ImGui::MenuItem("Cube"))
			{
				LOGFIX("Creating : Cube");
				drawcube = true;
			}
			if (ImGui::MenuItem("Pyramid"))
			{
				LOGFIX("Creating : Pyramid");
				drawpyramid = true;
			}
			if (ImGui::MenuItem("Cylinder"))
			{
				LOGFIX("Creating : Cylinder");
				drawcylinder = true;
			}
			if (ImGui::MenuItem("Sphere"))
			{
				LOGFIX("Creating : Sphere");
				drawsphere = true;
			}
			ImGui::MenuItem("Import A mesh");
			ImGui::EndMenu();

		}

		ImGui::EndMenu();
	}
}
