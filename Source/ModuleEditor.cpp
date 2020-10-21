#include "Globals.h"
#include "Application.h"
#include "ModuleEditorMainMenuBar.h"

#include "libraries/ImGUI/imgui.h"
#include "libraries/ImGUI/imgui_internal.h"
#include "libraries/ImGUI/imgui_impl_sdl.h"
#include "libraries/ImGUI/imgui_impl_opengl3.h"

#include "libraries/Glew/include/GL/glew.h" 
#include "libraries/SDL/include/SDL_opengl.h"

#include "SaveAndLoad.h"

#include "GoodClass.h"

// Class1 Clase2; Define Class

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

	App->configWindow->active_window = true;

	App->mainMenubar->drawplane = false;
	App->mainMenubar->drawcube = false;
	App->mainMenubar->drawpyramid = false;
	App->mainMenubar->drawcylinder = false;
	App->mainMenubar->drawsphere = false;
	// HARDWARE DETECTION
	App->configWindow->GetHardwareStatus();
	App->console->LogsAmount = 0;

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

	if (App->mainMenubar->drawplane)
	{
		App->geometryloader->DrawPlane();
		App->mainMenubar->drawplane = false;
	}

	if (App->mainMenubar->drawcube)
	{
		App->geometryloader->DrawCube();
		App->mainMenubar->drawcube = false;
	}

	if (App->mainMenubar->drawpyramid)
	{
		App->geometryloader->DrawPyramid();
		App->mainMenubar->drawpyramid = false;
	}

	if (App->mainMenubar->drawcylinder)
	{
		App->geometryloader->DrawCylinder();
		App->mainMenubar->drawcylinder = false;
	}

	if (App->mainMenubar->drawsphere)
	{
		App->geometryloader->DrawSphere();
		App->mainMenubar->drawsphere = false;
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


	App->mainMenubar->CreateMainMenuBar();
	App->configWindow->CreateConfigWindow();
	CreateAboutWindow();
	App->console->CreateConsoleWindow();
	App->hierarchy->CreateHierarchyWindow();
	App->inspector->CreateInspectorWindow();

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





// ------------------------ABOUT--------------------
void ModuleEditor::CreateAboutWindow()
{
	if (App->mainMenubar->show_about_window) {
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


	App->console->ConsoleLogs.push_back(tmp_string2);
}

