#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"


#include "libraries/ImGUI/imgui.h"
#include "libraries/ImGUI/imgui_internal.h"
#include "libraries/ImGUI/imgui_impl_sdl.h"
#include "libraries/ImGUI/imgui_impl_opengl3.h"

#include "libraries/Glew/include/GL/glew.h" 
#include "libraries/SDL/include/SDL_opengl.h"




ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app,start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));



	glewInit();

	const char* glsl_version = "#version 130";

	

	
	gl_context = SDL_GL_CreateContext(App->window->window);
	SDL_GL_MakeCurrent(App->window->window, gl_context);
	SDL_GL_SetSwapInterval(1);


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	

	
	
	ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
	// Our state
	show_demo_window = true;
	show_another_window = false;
	exit_engine_window = true;

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, gl_context);
	ImGui_ImplOpenGL3_Init(glsl_version);



	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
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
update_status ModuleSceneIntro::Update()
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

	

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("IMGUI IS FINALLY FUCKING WORKING :)");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("G2,FNC,RGE>TSM,TL,FLY");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Show Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Window2", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color


		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		
		if (ImGui::Button("Botton 2")) {
			
			if (on) {
				on=false;
			}
			else {
				on=true;
			}
			
				
		}

		if (on == true) {
			ImGui::Text("Me pego un tiro");
		}
		
		if (ImGui::Button("Close Engine")) {
			App->input->ExitEngine = true;
		}

		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}
	bool closeEngineBut;


	/*ImGui::Begin("Close Engine Window",&exit_engine_window);

	ImGui::Button("Exit Engine"); {

		App->input->ExitEngine = true;
		
	}

	ImGui::End();*/


	//Render
	ImGui::Render();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
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


	

	return UPDATE_STOP;
}

