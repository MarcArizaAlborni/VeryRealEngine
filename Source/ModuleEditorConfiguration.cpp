#include "Globals.h"
#include "Application.h"
#include "ModuleEditorConfiguration.h"

#include "libraries/ImGUI/imgui.h"
#include "libraries/ImGUI/imgui_internal.h"
#include "libraries/ImGUI/imgui_impl_sdl.h"
#include "libraries/ImGUI/imgui_impl_opengl3.h"

#include "libraries/Glew/include/GL/glew.h" 
#include "libraries/SDL/include/SDL_opengl.h"

#include "SaveAndLoad.h"


ModuleEditorConfiguration::ModuleEditorConfiguration(Application* app, const char* name, bool start_enabled) : Module(app, "ModuleConfiguration", start_enabled)
{

}

ModuleEditorConfiguration::~ModuleEditorConfiguration()
{}

// ----------------------------CONFIG WINDOW-------------------------------------
//Creation
void ModuleEditorConfiguration::CreateConfigWindow() {

	if (App->mainMenubar->show_config_window) {

		ImGui::Begin("Configuration", &App->mainMenubar->show_config_window);

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
void ModuleEditorConfiguration::CreateConfigWindow_Options() {

	if (ImGui::BeginMenu("Options")) {

		ImGui::MenuItem("Set Defaults");
		ImGui::MenuItem("Load");
		ImGui::MenuItem("Save");

		ImGui::EndMenu();
	}
}

//---------APPLICATION--------
void ModuleEditorConfiguration::CreateConfigWindow_Application() {

	if (ImGui::CollapsingHeader("Application")) {

		static char str1[128] = "";
		ImGui::InputTextWithHint("App Name", "Enter Text Here", str1, IM_ARRAYSIZE(str1));
		ImGui::InputTextWithHint("Organization", "Enter Text Here", str1, IM_ARRAYSIZE(str1));


		ImGui::SliderInt("MAX FPS", &App->max_FPS, 0, 120);
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

		// Memory --------------------
	}
}

//------------WINDOW-----------------------
void ModuleEditorConfiguration::CreateConfigWindow_Window()
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
void ModuleEditorConfiguration::CreateConfigWindow_FileSystem()
{

	if (ImGui::CollapsingHeader("File System")) {


	}
}

//---------------------INPUT-------------------------
void ModuleEditorConfiguration::CreateConfigWindow_Input()
{

	if (ImGui::CollapsingHeader("Input")) {


	}
}

//---------------------HARDWARE-------------------------
void ModuleEditorConfiguration::CreateConfigWindow_Hardware()
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

void ModuleEditorConfiguration::GetHardwareStatus()
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

void ModuleEditorConfiguration::CreateConsolelog(const char file[], int line, const char* format, ...)
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
