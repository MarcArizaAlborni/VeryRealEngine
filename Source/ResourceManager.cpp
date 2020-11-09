#include "Globals.h"
#include "Application.h"
#include "ResourceManager.h"



ResourceManager::ResourceManager(Application* app, const char* name, bool start_enabled) : Module(app, "ResourceManager", start_enabled)
{

}

ResourceManager::~ResourceManager()
{

}

bool ResourceManager::Start()
{
	return true;
}

update_status ResourceManager::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ResourceManager::CleanUp()
{
	return true;
}

void ResourceManager::CreateResourcesWindow()
{
	if (App->mainMenubar->show_resources_window) {

		ImGui::Begin("Resouces", &App->mainMenubar->show_resources_window);

		if (App->meshimporter->LoadedTexturesList.size() > 0) {

			TextureInfo* TextureToPrint;
			std::vector<TextureInfo*>::iterator ItTex = App->meshimporter->LoadedTexturesList.begin();
			for (int i = 0; i < App->meshimporter->LoadedTexturesList.size(); ++i) {

				TextureToPrint = *ItTex;

				ImGui::ImageButton((void*)(intptr_t)TextureToPrint->texture_id, { 50,50 });
				
					ImGui::SameLine();
				
				++ItTex;
			}

            

		}


		ImGui::End();
	}
}

void ResourceManager::CreateConsolelog(const char file[], int line, const char* format, ...)
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

