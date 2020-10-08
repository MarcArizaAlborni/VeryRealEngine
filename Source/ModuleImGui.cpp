#include "Globals.h"
#include "Application.h"
#include "ModuleImGui.h"

#include "libraries/ImGUI/imgui.h"
#include "libraries/ImGUI/imgui_internal.h"
#include "libraries/ImGUI/imgui_impl_sdl.h"
#include "libraries/ImGUI/imgui_impl_opengl3.h"

#include "libraries/Glew/include/GL/glew.h" 
#include "libraries/SDL/include/SDL_opengl.h"






ModuleImGui::ModuleImGui(Application* app, bool start_enabled) : Module(app,start_enabled)
{
}

ModuleImGui::~ModuleImGui()
{}

// Load assets
bool ModuleImGui::Start()
{
	
	LOG("Loading Intro assets");
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


	clear_color = ImVec4(0.40f, 0.10f, 0.20f, 1.00f); 

	OnInit = true;

	active_window = true;



	// HARDWARE DETECTION






	return ret;
}

// Load assets
bool ModuleImGui::CleanUp()
{
	LOG("Unloading Intro scene");


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(App->window->window);
	SDL_Quit();

	return true;
}



// Update
update_status ModuleImGui::Update(float dt)
{
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
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	

	//// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	//{
	//	static float f = 0.0f;
	//	static int counter = 0;

	//	ImGui::Begin("IMGUI IS FINALLY WORKING :)");                          // Create a window called "Hello, world!" and append into it.

	//	ImGui::Text("WELCOME TO VERY REAL ENGINE");               // Display some text (you can use a format strings too)
	//	ImGui::NextColumn();
	//	ImGui::Text("Created by Marc Ariza & Gerard Romeu");
	//	ImGui::Checkbox("Show Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
	//	ImGui::Checkbox("Exit Menu", &show_window_2);

	//	ImGui::SliderFloat("float", &f, 0.0f, 5.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	//	ImGui::ColorEdit4("color 1", (float*)&clear_color);		// Edit 3 floats representing a color

	//	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
	//		counter++;
	//	
	//	if (ImGui::Button("Click Me")) {
	//		
	//		if (on) {
	//			on=false;
	//		}
	//		else {
	//			on=true;
	//		}
	//		
	//			
	//	}

	//	if (on == true) {
	//		ImGui::Text("Best Engine");
	//	}


	//	ImGui::NextColumn();						// Backspace
	//	ImGui::Text("counter = %d", counter);

	//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//	ImGui::End();
	//}

	//// 3. Show another simple window.
	//if (show_window_2)
	//{
	//	ImGui::Begin("Exit Menu", &show_window_2);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	//	ImGui::Text("Exit Menu");
	//	if (ImGui::Button("Close VeryRealEngine")) {
	//		App->input->ExitEngine = true;
	//	}
	//	ImGui::End();
	//}


	CreateMainMenuBar();

	CreateConfigWindow();

	CreateAboutWindow();

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
void ModuleImGui::CreateMainMenuBar() {

	//MenuEditor
	if (ImGui::BeginMainMenuBar())
	{
		CreateMainMenuBar_File();
		CreateMainMenuBar_Edit();
		CreateMainMenuBar_View();
		CreateMainMenuBar_Help();

		ImGui::EndMainMenuBar();
	}


}

//CREATION OF SUBMENUS
//---------FILE--------

void ModuleImGui::CreateMainMenuBar_File() {

	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Quit", "ESC")) {

			App->input->ExitEngine = true;
		}
		ImGui::EndMenu();
	}
}

//----------EDIT-----------
void ModuleImGui::CreateMainMenuBar_Edit() {

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
void ModuleImGui::CreateMainMenuBar_View() {

	if (ImGui::BeginMenu("View"))
	{
		ImGui::MenuItem("Console", "1"); // Console Window
		ImGui::MenuItem("Configuration", "4", &show_config_window); // We need to get 4 as input to close It

		if (App->input->keyboard[SDL_SCANCODE_4]) {

			// Condition to enable/disable when clicking 4

		}

		ImGui::EndMenu();
	}
}

//---------------------HELP-----------------
void ModuleImGui::CreateMainMenuBar_Help() {

	if (ImGui::BeginMenu("Help"))
	{
		if (ImGui::MenuItem("Gui Demo")) {};

		if (ImGui::MenuItem("Documentation"))
			App->RequestBrowser("https://github.com/MarcArizaAlborni/VeryRealEngine"); // Missing wiki

		if (ImGui::MenuItem("Download Latest"))
			App->RequestBrowser("https://github.com/MarcArizaAlborni/VeryRealEngine"); // Missing release

		if (ImGui::MenuItem("Report a bug"))
			App->RequestBrowser("https://github.com/MarcArizaAlborni/VeryRealEngine/issues");

		if (ImGui::MenuItem("About")) {}

		ImGui::EndMenu();
	}
}



// ----------------------------CONFIG WINDOW-------------------------------------
//Creation
void ModuleImGui::CreateConfigWindow() {

	// Configuration menu gerard
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
void ModuleImGui::CreateConfigWindow_Options() {

	if (ImGui::BeginMenu("Options")) {

		ImGui::MenuItem("Set Defaults");
		ImGui::MenuItem("Load");
		ImGui::MenuItem("Save");

		ImGui::EndMenu();
	}
}

//---------APPLICATION--------
void ModuleImGui::CreateConfigWindow_Application() {

	if (ImGui::CollapsingHeader("Application")) {
	
		static char str1[128] = "";
		ImGui::InputTextWithHint("App Name", "Enter Text Here", str1, IM_ARRAYSIZE(str1));
		ImGui::InputTextWithHint("Organization", "Enter Text Here", str1, IM_ARRAYSIZE(str1));

		int fps_max = App->GetFramerateLimit();
		if (ImGui::SliderInt("Max FPS", &fps_max, 0, 120));
		App->SetFramerateLimit(fps_max);

		ImGui::Text("Limit Framerate:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f), "%i", App->GetFramerateLimit());

		/*char title[25];
		sprintf_s(title, 25, "Framerate %.1f", fps_log[fps_log.size() - 1]);
		ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		sprintf_s(title, 25, "Milliseconds %0.1f", ms_log[ms_log.size() - 1]);
		ImGui::PlotHistogram("##milliseconds", &ms_log[0], ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));*/

		// Memory --------------------
	}
}

//------------WINDOW-----------------------
void ModuleImGui::CreateConfigWindow_Window()
{
	if (ImGui::CollapsingHeader("Window")) {

		ImGui::Checkbox("Active", &active_window);

		//Icon Stuff

		static int val = 1000;
		static int val2;
		static int val3;
		static int volume;

		ImGui::SliderInt("Brightness", &val, 0.0f, 100.0f);
		ImGui::SliderInt("Size V", &val2, 0.0f, 300.0f);
		ImGui::SliderInt("Size H", &val3, 0.0f, 300.0f);

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
		
		ImGui::Text("Refresh Rate");

		ImGui::SameLine(0.0f, 30.0f);

		ImGui::Text("Current fps");

		/*if (ImGui::Checkbox("Fullscreen", &fullscreen))
			App->window->SetFullscreen(fullscreen);

		ImGui::SameLine();
		if (ImGui::Checkbox("Resizable", &resizable))
			App->window->SetResizable(resizable);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Restart to apply");*/

		ImGui::Checkbox("Borderless", &active_Borderless);
		ImGui::SameLine(0, 50.0f);
		ImGui::Checkbox("Full Desktop", &active_Full_Desktop);

	}
}

//----------------------FILE VIEW----------------------
void ModuleImGui::CreateConfigWindow_FileSystem()
{

	if (ImGui::CollapsingHeader("File System")) {


	}
}

//---------------------INPUT-------------------------
void ModuleImGui::CreateConfigWindow_Input()
{

	if (ImGui::CollapsingHeader("Input")) {


	}
}

//---------------------HARDWARE-------------------------
void ModuleImGui::CreateConfigWindow_Hardware()
{

	if (ImGui::CollapsingHeader("Hardware")) {

		HardwareStat.CPU.CPU_Count = SDL_GetCPUCount();
		HardwareStat.CPU.Cache_size = SDL_GetCPUCacheLineSize();
		HardwareStat.CPU.System_Ram = SDL_GetSystemRAM() / 1000;
		HardwareStat.GPU.model_name = (char*)glGetString(GL_VENDOR);
		HardwareStat.GPU.renderer_name = (char*)glGetString(GL_RENDERER);
		HardwareStat.GPU.version = (char*)glGetString(GL_VERSION);
		

		ImGui::TextColored({ 255,255,0,1 }, "CPUs:");
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "%d", HardwareStat.CPU.CPU_Count);
		ImGui::SameLine();
		ImGui::TextColored({ 255,255,0,1 }, "(Cache: %d kb)", HardwareStat.CPU.Cache_size);

		ImGui::TextColored({ 255,255,0,1 },"System Ram: %d GBs", HardwareStat.CPU.System_Ram);

		ImGui::TextColored({ 255,255,0,1 }, HardwareStat.GPU.model_name);
		ImGui::TextColored({ 255,255,0,1 }, HardwareStat.GPU.renderer_name);
		ImGui::TextColored({ 255,255,0,1 }, HardwareStat.GPU.version);

		
	}

}

void ModuleImGui::CreateAboutWindow()
{
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
