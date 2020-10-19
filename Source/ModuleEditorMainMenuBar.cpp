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

	if (ImGui::BeginMenu("View"))
	{
		ImGui::MenuItem("Console", "1", &show_console_window); //  We need to get 1 as input to close It
		ImGui::MenuItem("Configuration", "4", &show_config_window); // We need to get 4 as input to close It

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

//--------------------INSERT PRIMITIVES-----------------
void ModuleEditorMainMenuBar::CreateInsertPrimitivesWindow()
{
	if (ImGui::BeginMenu("Insert"))
	{
		if (ImGui::BeginMenu("Create"))
		{
			if (ImGui::MenuItem("Line"))
			{
				drawline = true;
			}
			if (ImGui::MenuItem("Plane"))
			{
				drawplane = true;
			}
			if (ImGui::MenuItem("Cube"))
			{
				drawcube = true;
			}
			if (ImGui::MenuItem("Pyramid"))
			{
				drawpyramid = true;
			}
			if (ImGui::MenuItem("Cylinder"))
			{
				drawcylinder = true;
			}
			if (ImGui::MenuItem("Sphere"))
			{
				drawsphere = true;
			}
			ImGui::MenuItem("Import A mesh");
			ImGui::EndMenu();

		}

		ImGui::EndMenu();
	}
}
