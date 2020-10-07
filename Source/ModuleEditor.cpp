#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"


ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleEditor::~ModuleEditor()
{}

// -----------------------------------------------------------------
bool ModuleEditor::Start()
{
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleEditor::CleanUp()
{

	return true;
}

// -----------------------------------------------------------------
update_status ModuleEditor::Update(float dt)
{

	// Main Menu GUI

	//if (ImGui::BeginMainMenuBar())
	//{
	//	if (ImGui::BeginMenu("File"))
	//	{
	//		if (ImGui::MenuItem("Quit", "ESC")) {

	//			App->input->ExitEngine = true;
	//		}
	//		ImGui::EndMenu();
	//	}

	//	if (ImGui::BeginMenu("View"))
	//	{
	//		ImGui::MenuItem("Console", "1"); // Console Window
	//		ImGui::MenuItem("Configuration", "4", &show_config_window); // We need to get 4 as input to close It

	//		if (App->input->keyboard[SDL_SCANCODE_4]) {

	//			// Condition to enable/disable when clicking 4

	//		}

	//		ImGui::EndMenu();
	//	}

	//	if (ImGui::BeginMenu("Edit"))
	//	{
	//		if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}
	//		if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false)) {}  // Disabled item
	//		if (ImGui::MenuItem("Cut", "Ctrl+X")) {}
	//		if (ImGui::MenuItem("Copy", "Ctrl+C")) {}
	//		if (ImGui::MenuItem("Paste", "Ctrl+V")) {}

	//		ImGui::EndMenu();
	//	}

	//	if (ImGui::BeginMenu("Help"))
	//	{
	//		if (ImGui::MenuItem("Gui Demo")) {};

	//		if (ImGui::MenuItem("Documentation"))
	//			App->RequestBrowser("https://github.com/MarcArizaAlborni/VeryRealEngine"); // Missing wiki

	//		if (ImGui::MenuItem("Download Latest"))
	//			App->RequestBrowser("https://github.com/MarcArizaAlborni/VeryRealEngine"); // Missing release

	//		if (ImGui::MenuItem("Report a bug"))
	//			App->RequestBrowser("https://github.com/MarcArizaAlborni/VeryRealEngine/issues");

	//		if (ImGui::MenuItem("About")) {}

	//		ImGui::EndMenu();
	//	}

	//	ImGui::EndMainMenuBar();
	//}


	//if (show_config_window) {

	//	ImGui::Begin("Configuration", &show_config_window);

	//	ImGui::End();

	//}

	return UPDATE_CONTINUE;
}


