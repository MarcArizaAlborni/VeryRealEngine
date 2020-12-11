#include "Globals.h"
#include "Application.h"
#include "Globals.h"
#include "ModuleCamera3D.h"
#include "ModuleGeometryManager.h"
#include "Game_Time.h"
#include "ModuleEditor.h"
#include "ModuleMeshImporter.h"
#include "ModuleHierarchy.h"
#include "ModuleInspector.h"
#include "ResourceManager.h"
#include "ModuleScene.h"

#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "GameObject.h"
#include "ComponentTexture.h"
#include "Component.h"
#include "ComponentMesh.h"


#include "libraries/ImGUI/imgui.h"
#include "libraries/ImGUI/imgui_internal.h"
#include "libraries/ImGUI/imgui_impl_sdl.h"
#include "libraries/ImGUI/imgui_impl_opengl3.h"

#include "libraries/Glew/include/GL/glew.h" 
#include "libraries/SDL/include/SDL_opengl.h"
#include "libraries/imGuizmo/ImGuizmo.h"



ModuleEditor::ModuleEditor(Application* app, const char* name, bool start_enabled) : Module(app,"Editor", start_enabled)
{
	
}

ModuleEditor::~ModuleEditor()
{}

// -----------------------------------------------------------------
bool ModuleEditor::Start()
{

	LOGFIX("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	// Init Glew
	glewInit();

	const char* glsl_version = "#version 130";

	gl_context = SDL_GL_CreateContext(App->window->window);
	SDL_GL_MakeCurrent(App->window->window, gl_context);
	SDL_GL_SetSwapInterval(1);



	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking (panels)
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	//ImGui::StyleColorsClassic();
	//ImGui::StyleColorsLight();
	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// States
	show_demo_window = true;

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, gl_context);
	ImGui_ImplOpenGL3_Init(glsl_version);


	clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

	OnInit = true;

	active_window = true;

	drawplane = false;
	drawcube = false;
	drawpyramid = false;
	drawcylinder = false;
	drawsphere = false;


	// HARDWARE DETECTION
	GetHardwareStatus();
	LogsAmount = 0;


	//MAIN MENU BAR----------------------------
	show_about_window = false;
	show_hierarchy_window = true;
	show_console_window = true;
	show_inspector_window = true;
	show_config_window = true;
	show_popup_want_close = false;
	show_popup_want_close2 = false;
	show_resources_window = true;
	show_play_window = true;
	show_grid = true;
	show_ui = true;

	play_mode = false;
	pause_mode = false;
	editor_mode = true;

	scene_timer.Start();



	SceneElement = new Scene_Manager("Library/Scenes/Scene1.scene");
	if (!SceneElement->ReadJValueRoot()) {
		SceneElement = new Scene_Manager();
	}


	return ret;
}

// -----------------------------------------------------------------
bool ModuleEditor::CleanUp()
{
	LOGFIX("Unloading Intro scene");


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(App->window->window);
	SDL_Quit();

	return true;
}

// -----------------------------------------------------------------
update_status ModuleEditor::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN) {
		SaveScene();
	}

	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
		//LoadScene();
	}

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate(float dt)
{

	if (drawplane)
	{
		App->geometrymanager->DrawPlane();
		drawplane = false;
	}

	if (drawcube)
	{
		App->geometrymanager->DrawCube();
		drawcube = false;
	}

	if (drawpyramid)
	{
		App->geometrymanager->DrawPyramid();
		drawpyramid = false;
	}

	if (drawcylinder)
	{
		App->geometrymanager->DrawCylinder();
		drawcylinder = false;
	}

	if (drawsphere)
	{
		App->geometrymanager->DrawSphere();
		drawsphere = false;
	}

	bool closeEngine = false;

	

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
		if (event.type == SDL_QUIT)
			done = true;
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(App->window->window))
			done = true;
	}
	ImGuiIO& io = ImGui::GetIO(); (void)io;


    ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	/*if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);*/

	if (show_ui == true)
	{
		if (MainWindow("Main Window", show_main_dockSpace, ImGuiWindowFlags_MenuBar)) {
			CreateMainMenuBar();
			ImGui::End();
		}
		CreateConfigWindow();
		CreateAboutWindow();
		CreateConsoleWindow();
		App->hierarchy->CreateHierarchyWindow();
		App->inspector->DrawInspectorWindowInfo();
		App->resources->CreateResourcesWindow();
		App->resources->CreateWindowDropFile();
		CreateTextureVisualizer();


		//Popups close
		if (show_popup_want_close == true)
		{

			ImGui::SetNextWindowSize({ 300,150 });
			ImGui::SetNextWindowPos({ 625, 300 });

			ImGui::Begin("VeryReal Engine", &show_popup_want_close, ImGuiWindowFlags_NoCollapse
				| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

			ImGui::Separator();
			ImGui::Text("Are you sure you want to exit the Engine?");
			ImGui::Spacing();
			ImGui::Text("");
			ImGui::Spacing();
			ImGui::Text("");
			ImGui::Spacing();
			ImGui::Text("");
			ImGui::Spacing();
			ImGui::Spacing();
			if (ImGui::Button("Yes", { 80,20 }))
			{
				show_popup_want_close2 = true;
			}

			ImGui::SameLine(0.0F, 125.0f);
			if (ImGui::Button("No", { 80,20 }))
			{
				show_popup_want_close = false;
			}

			ImGui::End();
		}

		if (show_popup_want_close2 == true)
		{
			ImGui::SetNextWindowSize({ 350,200 });
			ImGui::SetNextWindowPos({ 725, 400 });

			ImGui::Begin("VeryReal Engine.", &show_popup_want_close2, ImGuiWindowFlags_NoCollapse
				| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

			ImGui::Separator();
			ImGui::Text("Are you really sure you want to exit the Engine?");
			ImGui::Spacing();
			ImGui::Text("     ");

			ImGui::SameLine(0, 75.0f);
			ImGui::Image((void*)(intptr_t)App->textureImporter->cat_crying.texture_id, { 125,100 });
			ImGui::Spacing();


			if (ImGui::Button("YES!!", { 80,20 }))
			{
				App->input->ExitEngine = true;
				//App->mainMenubar->show_popup_want_close3 = true;
			}

			ImGui::SameLine(0.0F, 172.0f);
			if (ImGui::Button("No", { 80,20 }))
			{
				show_popup_want_close = false;
				show_popup_want_close2 = false;
			}

			ImGui::End();

		}

		
	}
		
	CreateBar_Play();
	

	//Render
	ImGui::Render();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	//glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}

	//SDL_GL_SwapWindow(App->window->window);

	OnInit = false;

	return UPDATE_CONTINUE;
}


// Main docking
bool ModuleEditor::MainWindow(char* id, bool docking, ImGuiWindowFlags windowFlags)
{
	


	ImGuiViewport* viewport = ImGui::GetWindowViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground;

	static bool open = true;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	open = ImGui::Begin(id, &open, windowFlags);
	
	ImGui::PopStyleVar(3);

	
	


	if (docking) {

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspace_id = ImGui::GetID(id);
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
		}
	}

	



	return open;
}


// ------------------------ABOUT--------------------
void ModuleEditor::CreateAboutWindow()
{
	if (show_about_window) {
		ImGui::Begin("About");

		ImGui::Text("Very Real Engine v0.1");

		ImGui::Text("An actually real engine...");

		ImGui::Text("Made by Gerard Romeu Vidal & Marc Ariza Alborni");

		ImGui::Text("3rd Party Libraries:");

		ImGui::BulletText("SDL 2.0");

		ImGui::BulletText("Glew 2.0.0");

		ImGui::BulletText("ImGui v1.78");

		ImGui::BulletText("Math Geo Lib v1.5");

		ImGui::BulletText("OpenGL 3.1");

		ImGui::NewLine();

		ImGui::Text("License:");

		ImGui::Text("Copyright (c) <2020> <Gerard Romeu Vidal & Marc Ariza Alborni>");

		ImGui::NewLine();

		//THIS IS WRONG WE NEED TO FIX IT (WIP)

		
		ImGui::Text("This software is provided 'as-is', without any express or implied warranty.In no event will the authors be held liable for any damages arising from the use of this software. Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter itand redistribute it freely, subject to the following restrictions :");
		ImGui::Text("1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.");
		ImGui::Text("2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.");
		ImGui::Text("3. This notice may not be removed or altered from any source distribution.n.");


		ImGui::End();
	}
}


// ----------------------------MENU BAR-------------------------------------
//Creation
void ModuleEditor::CreateMainMenuBar() {

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

void ModuleEditor::CreateMainMenuBar_File() {

	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Quit", "ESC")) {

			show_popup_want_close = true;

		}
		ImGui::EndMenu();
	}
}

//----------EDIT-----------
void ModuleEditor::CreateMainMenuBar_Edit() {

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
void ModuleEditor::CreateMainMenuBar_View() {

	if (ImGui::BeginMenu("Window"))
	{
		ImGui::MenuItem("Console", "1", &show_console_window); //  We need to get 1 as input to close It
		ImGui::MenuItem("Configuration", "2", &show_config_window); // We need to get 4 as input to close It
		ImGui::MenuItem("Show GameObject Hierarchy", "3", &show_hierarchy_window);
		ImGui::MenuItem("Show GameObject Inspector", "4", &show_inspector_window);
		ImGui::MenuItem("Show Resources window", "5", &show_resources_window);
		if (App->input->keyboard[SDL_SCANCODE_4]) {

			// Condition to enable/disable when clicking 4

		}

		ImGui::EndMenu();
	}
}

//---------------------HELP-----------------
void ModuleEditor::CreateMainMenuBar_Help() {

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
void ModuleEditor::CreateInsertPrimitivesWindow()
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

//----------------------PLAY EDITOR---------------------------
void ModuleEditor::CreateBar_Play()
{
	if (App->editor->show_play_window) {

		ImGui::Begin("Play Editor", &App->editor->show_play_window);

		if (play_mode == true)
		{
			ImGui::SetWindowFontScale(1.25);
			ImGui::TextColored({ 255,255,0,1 }, "PLAY MODE");
		}

		if (pause_mode == true)
		{
			ImGui::SetWindowFontScale(1.25);
			ImGui::TextColored({ 255,255,0,1 }, "ENGINE PAUSED");
		}

		if (editor_mode == true)
		{
			
			ImGui::SetWindowFontScale(1.25);
			ImGui::TextColored({ 255,255,0,1 }, "EDITOR MODE");
		}

		ImGui::SetWindowFontScale(1.0);
		ImGui::SameLine();

		if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawPlayIcon.texture_id, { 25,25 }))
		{
			Game_Time::Start();
			App->scene->SaveScene();
			play_mode = true;
			editor_mode = false;
			
		}
		if (play_mode == true)
		{
			ImGui::SameLine();
			if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawStopIcon.texture_id, { 25,25 }))
			{
				Game_Time::Stop();
				play_mode = false;
				editor_mode = true;
				//Reset Pos func
				App->scene->LoadScene();
				
			}
		}
		
		ImGui::SameLine();
		if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawPauseIcon.texture_id, { 25,25 }))
		{
			Game_Time::Pause();
			pause_mode = true;
			play_mode = false;
			editor_mode = false;
		}
		if (pause_mode == true)
		{
			ImGui::SameLine();
			if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawResumeIcon.texture_id, { 25,25 }))
			{
				Game_Time::Resume();
				pause_mode = false;
				editor_mode = false;
				play_mode = true;
			}
		}

		ImGui::SameLine();
		if (Game_Time::oneframe)
		{
			{
				Game_Time::Pause();
				Game_Time::oneframe = false;
			}
		}
		if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawTickIcon.texture_id, { 25,25 }))
		{
			
			Game_Time::One_Frame();

		}
		ImGui::SameLine();
		ImGui::Checkbox("Show Grid", &show_grid);
		ImGui::SameLine();
		ImGui::Checkbox("Show UI", &show_ui);
		ImGui::SameLine();
		ImGui::Text("Real Time:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%.3f", scene_timer.ReadSec());
		ImGui::SameLine();
		ImGui::Text("Game Time:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%.3f", Game_Time::time);
		ImGui::End();
	}
}




// ---------------------------------CONFIG--------------------------------
// ----------------------------CONFIG WINDOW-------------------------------------
//Creation
void ModuleEditor::CreateConfigWindow() {

	if (App->editor->show_config_window) {

		ImGui::Begin("Configuration", &App->editor->show_config_window);

		CreateConfigWindow_Options();
		CreateConfigWindow_Application();
		CreateConfigWindow_Window();
		CreateConfigWindow_FileSystem();
		CreateConfigWindow_Input();
		CreateConfigWindow_Hardware();
		CreateConfigWindow_Resource();
		ImGui::End();

	}
}

//CREATION OF SUBMENUS
//---------OPTIONS--------
void ModuleEditor::CreateConfigWindow_Options() {

	if (ImGui::BeginMenu("Options")) {

		ImGui::MenuItem("Set Defaults");
		ImGui::MenuItem("Load");
		ImGui::MenuItem("Save");

		ImGui::EndMenu();
	}
}

//---------APPLICATION--------
void ModuleEditor::CreateConfigWindow_Application() {

	if (ImGui::CollapsingHeader("Application")) {

		static char str1[128] = "";
		ImGui::InputTextWithHint("App Name", "Enter Text Here", str1, IM_ARRAYSIZE(str1));
		ImGui::InputTextWithHint("Organization", "Enter Text Here", str1, IM_ARRAYSIZE(str1));


		ImGui::Separator();

		ImGui::SliderInt("Max FPS", &App->max_framerateCap, 1, 120);

		ImGui::Text("Limit Framerate:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%d", App->max_framerateCap);
		if (ImGui::Checkbox("VSync", &vSync)) {
			if (vSync) {
				SDL_GL_SetSwapInterval(1);
			}
			else {
				SDL_GL_SetSwapInterval(0);
			}
		}

		/*char title[25];
		sprintf_s(title, 25, "Framerate %.1f", App->fps_log[App->fps_log.size() - 1]);
		ImGui::PlotHistogram("##framerate", &App->fps_log[0], App->fps_log.size(), 0, title, 0.0f, 140.0f, ImVec2(310, 100));
		sprintf_s(title, 25, "Milliseconds %.1f", App->ms_log[App->ms_log.size() - 1]);
		ImGui::PlotHistogram("##milliseconds", &App->ms_log[0], App->ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));*/

		char title[25];
		sprintf_s(title, 25, "Framerate %.1f", App->fps_log[App->fps_log.size() - 1]);
		ImGui::PlotHistogram("##framerate", &App->fps_log[0], App->fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		sprintf_s(title, 25, "Milliseconds %0.1f", App->ms_log[App->ms_log.size() - 1]);
		ImGui::PlotHistogram("##milliseconds", &App->ms_log[0], App->ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));

		// Memory --------------------
	}
}

//------------WINDOW-----------------------
void ModuleEditor::CreateConfigWindow_Window()
{
	if (ImGui::CollapsingHeader("Window")) {

		ImGui::Checkbox("Active", &active_window);

		//Icon Stuff

		static int val = 1000;
		static int val2;
		static int val3;
		static int volume;

		brightness = App->window->GetBrightness();
		if (ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f))
			App->window->ChangeWindowBrightnessTo(brightness);


		ImGui::SliderInt("Size Height", &val2, 0.0f, 300.0f);
		ImGui::SliderInt("Size Width", &val3, 0.0f, 300.0f);

		ImGui::Text("Input Active: ");

		ImGui::SameLine(0.0f, 10.0f);

		if (App->input->keyboard[SDL_SCANCODE_W]) {

			ImGui::Text("GO UP BUTTON ");

		}
		else if (App->input->keyboard[SDL_SCANCODE_S]) {

			ImGui::Text("GO DOWN BUTTON ");

		}
		else if (App->input->keyboard[SDL_SCANCODE_A]) {

			ImGui::Text("GO LEFT BUTTON ");

		}
		else if (App->input->keyboard[SDL_SCANCODE_D]) {

			ImGui::Text("GO RIGHT BUTTON ");

		}
		else if (App->input->mouse_buttons[SDL_BUTTON_LEFT]) {

			ImGui::Text("GO LEFT BUTTON ");

		}
		else if (App->input->mouse_buttons[SDL_BUTTON_RIGHT]) {

			ImGui::Text("GO RIGHT BUTTON ");

		}
		else {
			ImGui::Text("No Input Detected");
		}

		ImGui::Text("Mouse Position");
		ImGui::SameLine(0.0f, 10.0f);
		ImGui::Text("X: %d", App->input->mouse_x);
		ImGui::SameLine(0.0f, 10.0f);
		ImGui::Text("Y: %d", App->input->mouse_y);

		ImGui::Text("Refresh Rate");

		ImGui::SameLine(0.0f, 30.0f);

		ImGui::Text("Current fps");

		active_fullscreen = App->window->GetFullscreen();
		if (ImGui::Checkbox("Fullscreen", &active_fullscreen))
			App->window->SetFullscreen(active_fullscreen);

		// Not working yet
		ImGui::SameLine();
		active_Resizable = App->window->GetResizable();
		(ImGui::Checkbox("Resizable", &active_Resizable));
		App->window->SetResizable(active_Resizable);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Restart to apply");

		active_Borderless = App->window->GetBorderless();
		if (ImGui::Checkbox("Borderless", &active_Borderless))
			App->window->SetBorderless(active_Borderless);
		ImGui::SameLine(0, 50.0f);

		active_Full_Desktop = App->window->GetFullDesktop();
		if (ImGui::Checkbox("Fullscreen Desktop", &active_Full_Desktop))
			App->window->SetFullScreenDesktop(active_Full_Desktop);

	}
}

//----------------------FILE VIEW----------------------
void ModuleEditor::CreateConfigWindow_FileSystem()
{

	if (ImGui::CollapsingHeader("File System")) {


	}
}

//---------------------INPUT-------------------------
void ModuleEditor::CreateConfigWindow_Input()
{

	if (ImGui::CollapsingHeader("Input")) {


	}
}

//---------------------HARDWARE-------------------------
void ModuleEditor::CreateConfigWindow_Hardware()
{

	if (ImGui::CollapsingHeader("Hardware")) {

		ImGui::Text("CPUs:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%d", HardwareStat.CPU.CPU_Count);

		ImGui::Text("Cache:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "(%d kb)", HardwareStat.CPU.Cache_size);

		ImGui::Text("System Ram:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%d GBs", HardwareStat.CPU.System_Ram);

		ImGui::TextColored({ 255,255,0,1 }, HardwareStat.GPU.model_name);
		ImGui::TextColored({ 255,255,0,1 }, HardwareStat.GPU.renderer_name);
		ImGui::TextColored({ 255,255,0,1 }, HardwareStat.GPU.version);

		ImGui::Text("3D Active:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%d", HardwareStat.CPU.isActive_3D);

		ImGui::Text("AltiVec Active:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%d", HardwareStat.CPU.isActive_AltiVec);

		ImGui::Text("AVX Active:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%d", HardwareStat.CPU.isActive_AVX);

		ImGui::Text("AVX2 Active:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%d", HardwareStat.CPU.isActive_AVX2);

		ImGui::Text("MMX Active:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%d", HardwareStat.CPU.isActive_MMX);

		ImGui::Text("RDTSC Active:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%d", HardwareStat.CPU.isActive_RDTSC);

		ImGui::Text("SSE Active:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%d", HardwareStat.CPU.isActive_SSE);

		ImGui::Text("SSE2 Active:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%d", HardwareStat.CPU.isActive_SSE2);

		ImGui::Text("SSE3 Active:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%d", HardwareStat.CPU.isActive_SSE3);

		ImGui::Text("SSE41 Active:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%d", HardwareStat.CPU.isActive_SSE41);

		ImGui::Text("SSE42 Active:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%d", HardwareStat.CPU.isActive_SSE42);
	}

}


void ModuleEditor::GetHardwareStatus()
{
	HardwareStat.CPU.CPU_Count = SDL_GetCPUCount();
	HardwareStat.CPU.Cache_size = SDL_GetCPUCacheLineSize();
	HardwareStat.CPU.System_Ram = SDL_GetSystemRAM() / 1000;
	HardwareStat.GPU.model_name = (char*)glGetString(GL_VENDOR);
	HardwareStat.GPU.renderer_name = (char*)glGetString(GL_RENDERER);
	HardwareStat.GPU.version = (char*)glGetString(GL_VERSION);
	HardwareStat.CPU.isActive_3D = SDL_Has3DNow();
	HardwareStat.CPU.isActive_AVX2 = SDL_HasAVX2();
	HardwareStat.CPU.isActive_AVX = SDL_HasAVX();
	HardwareStat.CPU.isActive_AltiVec = SDL_HasAltiVec();
	HardwareStat.CPU.isActive_MMX = SDL_HasMMX();
	HardwareStat.CPU.isActive_RDTSC = SDL_HasRDTSC();
	HardwareStat.CPU.isActive_SSE = SDL_HasSSE();
	HardwareStat.CPU.isActive_SSE2 = SDL_HasSSE2();
	HardwareStat.CPU.isActive_SSE3 = SDL_HasSSE3();
	HardwareStat.CPU.isActive_SSE41 = SDL_HasSSE41();
	HardwareStat.CPU.isActive_SSE42 = SDL_HasSSE42();
}

void ModuleEditor::CreateConfigWindow_Resource()
{
	if (ImGui::CollapsingHeader("Resources")) {

		int AmountOfTextures = App->textureImporter->Textures_Resource_List.size();
		ImGui::Text("Active Textures: %d", AmountOfTextures);
		std::vector<TextureInfo*>::iterator It= App->textureImporter->Textures_Resource_List.begin();
		for (int size = 0; size < App->textureImporter->Textures_Resource_List.size(); ++size) {

			TextureInfo* Text = *It;
			
			AmountOfUsesTexture = 0;

			std::vector<Game_Object*>::iterator ItObj = App->geometrymanager->ObjectsOnScene.begin();
			for (int i = 0; i < App->geometrymanager->ObjectsOnScene.size(); ++i) {

				Game_Object* Object = *ItObj;

				ItChildrenObjTextCount(Object,Text);
				
				Component_Texture* MeshDraw = (Component_Texture*)Object->GetComponent(Component_Types::Texture);

				
				if (MeshDraw != nullptr) {
					if (MeshDraw->Texture->texture_id == Text->texture_id) {
						++AmountOfUsesTexture;
					}
				}

				++ItObj;
			}

			ImGui::Text("%d.",size);
			ImGui::SameLine();
			ImGui::Text(Text->texture_path.c_str());
			ImGui::SameLine();
			ImGui::TextColored({ 255,255,0,1 }, "%d", AmountOfUsesTexture);

			++It;
		}
	
		ImGui::Separator();
	

		/*int AmountOfMeshes = App->meshimporter->Mesh_Resource_List.size(); 
		ImGui::Text("Active Meshes: %d", AmountOfMeshes);
		std::vector<MeshInfo*>::iterator Itm = App->meshimporter->Mesh_Resource_List.begin();
		for (int size = 0; size < App->textureImporter->Textures_Resource_List.size(); ++size) {

			MeshInfo* Mesh = *Itm;

			AmountOfUsesMesh = 0;

			std::vector<Game_Object*>::iterator ItObj = App->geometrymanager->ObjectsOnScene.begin();
			for (int i = 0; i < App->geometrymanager->ObjectsOnScene.size(); ++i) {

				Game_Object* Object = *ItObj;

				ItChildrenObjMeshCount(Object, Mesh);

				Component_Mesh* MeshDraw = (Component_Mesh*)Object->GetComponent(Component_Types::Mesh);
			
				if (MeshDraw != nullptr) {
					if (MeshDraw->Mesh->Name == Mesh->Name) {
						++AmountOfUsesMesh;
					}
				}

				++ItObj;
			}

			ImGui::Text("%d.", size);
			ImGui::SameLine();
			ImGui::Text(Mesh->Name.c_str());
			ImGui::SameLine();
			ImGui::TextColored({ 255,255,0,1 }, "%d", AmountOfUsesMesh);

			++Itm;
		}*/
	}
}

void ModuleEditor::CreateTextureVisualizer()
{
	if (VisualizeTextureWindow) {


		ImGui::Begin("Texture Visualizer", &VisualizeTextureWindow);

		ImVec2 Size=ImGui::GetWindowSize();


		ImGui::Image((void*)(intptr_t)ToVisualizeTexture.texture_id, { Size.x,Size.y });



		ImGui::End();

		


	}



}



// -----------------------CONSOLE------------------------
void ModuleEditor::CreateConsoleWindow()
{
	if (App->editor->show_console_window) {

		ImGui::Begin("Console", &App->editor->show_console_window);
		std::list<const char*>::iterator Iterator = ConsoleLogs.begin();

		for (Iterator; Iterator != ConsoleLogs.end(); Iterator++) {


			ImGui::TextUnformatted(*Iterator);

		}

		ImGui::End();

	}

	LogsAmount = ConsoleLogs.size();

}



void ModuleEditor::SaveScene()
{

	Scene_Manager SceneToSave = SceneElement->AddJArray("GameObjects");

	
	int Sections = -1;

	std::vector<Game_Object*>::iterator It = App->geometrymanager->ObjectsOnScene.begin();
	for (int i = 0; i < App->geometrymanager->ObjectsOnScene.size(); ++i) {

		Game_Object* Item = *It;
		SaveGameObjectsChilds(SceneToSave, Item, &Sections);

			++It;
	}

	SceneElement->Save("Library/Scenes/Scene1.scene");

}

void ModuleEditor::SaveGameObjectsChilds(Scene_Manager Scene, Game_Object* Object, int* iterator)
{

	(*iterator)++;

	Scene_Manager Item = Scene.AddSectionArray(*iterator);

	Item.WriteInt("Enabled", Object->Enabled);
	Item.WriteInt("ItemId", Object->item_id);
	Item.WriteString("Name", Object->name);
	
	Scene_Manager Item_Components = Item.AddJArray("Components");
	//Object->

	std::vector<Game_Object*>::iterator It = Object->Children_List.begin();
	for (int i = 0; i < Object->Children_List.size(); ++i) {

		Game_Object* Item = *It;
		SaveGameObjectsChilds(Scene, Item, iterator);

		++It;
	}

}

void ModuleEditor::LoadScene(std::string SceneFileName)
{

	App->geometrymanager->ObjectsOnScene.clear(); //This is wrong neeeds to be fixed


	SceneElement = new Scene_Manager("Library/Scenes/Scene1.scene");

	Scene_Manager SceneItem = SceneElement->GetJArray("GameObjects");
	int j = 0;

	while (j != -1) {


		if (SceneItem.IsArraySection(j)) {

			LoadGameObject(SceneItem.GetSectionArray(j));
			++j;

		}
		else {
			j = -1;
		}

	}

}

void ModuleEditor::LoadGameObject(Scene_Manager Scene)
{

	if (!Scene.CheckString("Name")) {

	}

	





}

void ModuleEditor::CreateConsolelog(const char file[], int line, const char* format, ...)
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

void ModuleEditor::ItChildrenObjTextCount(Game_Object* Object,TextureInfo* Text)
{
	std::vector<Game_Object*>::iterator It = Object->Children_List.begin();

	for (int size = 0; size < Object->Children_List.size(); ++size) {

		Game_Object* Item = *It;

		ItChildrenObjTextCount(Item,Text);

		Component_Texture* MeshDraw = (Component_Texture*)Item->GetComponent(Component_Types::Texture);


		if (MeshDraw != nullptr) {
			if (MeshDraw->Texture->texture_id == Text->texture_id) {
				++AmountOfUsesTexture;
			}
		}

		++It;

	}
}




void ModuleEditor::ItChildrenObjMeshCount(Game_Object* Object, MeshInfo* Mesh)
{
	std::vector<Game_Object*>::iterator It = Object->Children_List.begin();

	for (int size = 0; size < Object->Children_List.size(); ++size) {

		Game_Object* Item = *It;

		ItChildrenObjMeshCount(Item, Mesh);

		Component_Mesh* MeshDraw = (Component_Mesh*)Item->GetComponent(Component_Types::Mesh);


		if (MeshDraw != nullptr) {
			if (MeshDraw->Mesh->Name == Mesh->Name) {
				++AmountOfUsesMesh;
			}
		}

		++It;

	}
}


