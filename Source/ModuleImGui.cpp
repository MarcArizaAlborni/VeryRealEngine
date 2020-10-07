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
	ImGui::StyleColorsLight();
	//ImGui::StyleColorsDark();

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


	clear_color = ImVec4(0.8f, 0.15f, 0.60f, 1.00f); //PINK

	OnInit = true;

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
update_status ModuleImGui::Update()
{
	bool closeEngine = false;
	
	ImVec4 clear_color = ImVec4(0.8f, 0.15f, 0.60f, 1.00f); //PINK
	

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

	

	if (show_configuration_window) {

		static int val = 1000;
		static int val2;
		static int val3;
		static int volume;

		if (OnInit) {
			ImGui::SetNextWindowSize({ 300,300 }, ImGuiCond_Once);
		}
		else {
			ImGui::SetNextWindowSize({ (float)val3,(float)val2 });
		}

		ImGui::Begin("Configuration Window", &show_configuration_window);

		ImGui::SliderInt("Brightness", &val, 0.0f,100.0f);
		ImGui::SliderInt("Size V", &val2,0.0f, 300.0f);
		ImGui::SliderInt("Size H", &val3,0.0f, 300.0f);

		
		
		ImGui::Checkbox("Vsync", &vsync_active);

		
		


		ImGui::SliderInt("Volume", &volume, 0.0f, 100.0f);

		ImGui::Text("Input Active: ");

		ImGui::SameLine(0.0f,10.0f);
		
		if (App->input->keyboard[SDL_SCANCODE_W]) {

			ImGui::Text("GO UP BUTTON ");

		}
		if (App->input->keyboard[SDL_SCANCODE_S]) {

			ImGui::Text("GO DOWN BUTTON ");

		}
		if (App->input->keyboard[SDL_SCANCODE_A]) {

			ImGui::Text("GO LEFT BUTTON ");

		}
		if (App->input->keyboard[SDL_SCANCODE_D]) {

			ImGui::Text("GO RIGHT BUTTON ");

		}



		if (App->input->mouse_buttons[SDL_BUTTON_LEFT]) {

			ImGui::Text("GO LEFT BUTTON ");

		}

		if (App->input->mouse_buttons[SDL_BUTTON_RIGHT]) {

			ImGui::Text("GO RIGHT BUTTON ");

		}
		ImGui::End();
	}















	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Quit", "ESC")) {
			
				App->input->ExitEngine = true;
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			ImGui::MenuItem("Console", "1"); // Console Window
			ImGui::MenuItem("Configuration", "4", &show_config_window); // We need to get 4 as input to close It
		
			if (App->input->keyboard[SDL_SCANCODE_4]) {
				
				// Condition to enable/disable when clicking 4
								
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}
			if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false)) {}  // Disabled item
			if (ImGui::MenuItem("Cut", "Ctrl+X")) {}
			if (ImGui::MenuItem("Copy", "Ctrl+C")) {}
			if (ImGui::MenuItem("Paste", "Ctrl+V")) {}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Gui Demo")) {}
			if (ImGui::MenuItem("Documentation")) {}
			if (ImGui::MenuItem("Download Latest")) {}
			if (ImGui::MenuItem("Report a bug")) {}
			if (ImGui::MenuItem("About")) {}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	
	if (show_config_window) {

		ImGui::Begin("Configuration", &show_config_window);

		ImGui::End();

	}


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

