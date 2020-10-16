#include "Globals.h"
#include "Application.h"
#include "ModuleImGui.h"

#include "libraries/ImGUI/imgui.h"
#include "libraries/ImGUI/imgui_internal.h"
#include "libraries/ImGUI/imgui_impl_sdl.h"
#include "libraries/ImGUI/imgui_impl_opengl3.h"

#include "libraries/Glew/include/GL/glew.h" 
#include "libraries/SDL/include/SDL_opengl.h"

#include "SaveAndLoad.h"

#include "GoodClass.h"

ModuleEditor::ModuleEditor(Application* app, const char* name, bool start_enabled) : Module(app,"Editor", start_enabled)
{
	
}

ModuleEditor::~ModuleEditor()
{}

// -----------------------------------------------------------------
bool ModuleEditor::Start()
{
	//Class1::Addition(); IF STATIC


 //      Class1 ClaseTest;   //IF NOT STATIC

	//ClaseTest.Addition();
	



	
	
	


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
	show_window_2 = false;
	exit_engine_window = true;

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, gl_context);
	ImGui_ImplOpenGL3_Init(glsl_version);


	clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

	OnInit = true;

	active_window = true;

	drawcube = false;
	drawpyramid = false;
	drawcylinder = false;
	// HARDWARE DETECTION
	GetHardwareStatus();
	LogsAmount = 0;

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

	

	return UPDATE_STOP;
}

update_status ModuleEditor::PostUpdate(float dt)
{
	if (drawcube)
	{
		App->renderer3D->DrawCube();
		!drawcube;
	}

	if (drawpyramid)
	{
		App->renderer3D->DrawPyramid();
		!drawpyramid;
	}

	if (drawcylinder)
	{
		App->renderer3D->DrawCylinder();
		!drawcylinder;
	}


	bool closeEngine = false;

	if (App->input->keyboard[SDL_SCANCODE_P]) {

		App->LoadSave->SaveintoFileConfig();

	}

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
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);


	CreateMainMenuBar();
	CreateConfigWindow();
	CreateAboutWindow();
	CreateConsoleWindow();

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

	return UPDATE_STOP;
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

			App->input->ExitEngine = true;
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
			if (ImGui::MenuItem("Cube"))
			{
				drawcube = true;
			}
			ImGui::MenuItem("Sphere");
			if (ImGui::MenuItem("Pyramid"))
			{
				drawpyramid = true;
			}
			if (ImGui::MenuItem("Cylinder"))
			{
				drawcylinder = true;
			}
			ImGui::MenuItem("Import A mesh");
			ImGui::EndMenu();
			
		}

		ImGui::EndMenu();
	}
}



// ----------------------------CONFIG WINDOW-------------------------------------
//Creation
void ModuleEditor::CreateConfigWindow() {

	if (show_config_window) {

		ImGui::Begin("Configuration", &show_config_window);

		CreateConfigWindow_Options();
		CreateConfigWindow_Application();
		CreateConfigWindow_Window();
		CreateConfigWindow_FileSystem();
		CreateConfigWindow_Input();
		CreateConfigWindow_Hardware();
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


		ImGui::SliderInt("MAX FPS", &App->max_FPS, 0, 120);
		if (ImGui::Checkbox("VSync", &App->editor->vSync)) {
			if (App->editor->vSync) {
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
		ImGui::TextColored({ 255,255,0,1 }, "%d", HardwareStat.CPU.isActive_3D );

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

// -----------------------CONSOLE------------------------
void ModuleEditor::CreateConsoleWindow()
{
	if (show_console_window) {

		ImGui::Begin("Console", &show_console_window);
		std::list<char*>::iterator Iterator = ConsoleLogs.begin();

		

			for (Iterator; Iterator != ConsoleLogs.end(); Iterator++) {


				ImGui::TextUnformatted(*Iterator);

			}

		

		ImGui::End();

	}

	LogsAmount = ConsoleLogs.size();


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

	


	 
	App->editor->ConsoleLogs.push_back(tmp_string2);

}

void ModuleEditor::GetHardwareStatus()
{
	App->editor->HardwareStat.CPU.CPU_Count = SDL_GetCPUCount();
	App->editor->HardwareStat.CPU.Cache_size = SDL_GetCPUCacheLineSize();
	App->editor->HardwareStat.CPU.System_Ram = SDL_GetSystemRAM() / 1000;
	App->editor->HardwareStat.GPU.model_name = (char*)glGetString(GL_VENDOR);
	App->editor->HardwareStat.GPU.renderer_name = (char*)glGetString(GL_RENDERER);
	App->editor->HardwareStat.GPU.version = (char*)glGetString(GL_VERSION);
	App->editor->HardwareStat.CPU.isActive_3D = SDL_Has3DNow();
	App->editor->HardwareStat.CPU.isActive_AVX2 = SDL_HasAVX2();
	App->editor->HardwareStat.CPU.isActive_AVX = SDL_HasAVX();
	App->editor->HardwareStat.CPU.isActive_AltiVec = SDL_HasAltiVec();
	App->editor->HardwareStat.CPU.isActive_MMX = SDL_HasMMX();
	App->editor->HardwareStat.CPU.isActive_RDTSC = SDL_HasRDTSC();
	App->editor->HardwareStat.CPU.isActive_SSE = SDL_HasSSE();
	App->editor->HardwareStat.CPU.isActive_SSE2 = SDL_HasSSE2();
	App->editor->HardwareStat.CPU.isActive_SSE3 = SDL_HasSSE3();
	App->editor->HardwareStat.CPU.isActive_SSE41 = SDL_HasSSE41();
	App->editor->HardwareStat.CPU.isActive_SSE42 = SDL_HasSSE42();
}
