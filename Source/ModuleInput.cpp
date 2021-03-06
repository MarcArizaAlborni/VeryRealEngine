#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleTextureImporter.h"
#include "ModuleMeshImporter.h"
#include "ModuleEditor.h"

#include "GameObject.h"
#include "Component.h"
#include "ComponentTexture.h"
#include "ModuleCamera3D.h"


#include "libraries/ImGUI/imgui.h"
#include "libraries/ImGUI/imgui_internal.h"
#include "libraries/ImGUI/imgui_impl_sdl.h"
#include "libraries/ImGUI/imgui_impl_opengl3.h"

#include "libraries/Glew/include/GL/glew.h" 
#include "libraries/SDL/include/SDL_opengl.h"


#define MAX_KEYS 300

ModuleInput::ModuleInput(Application* app, const char* name, bool start_enabled) : Module(app,"Input", start_enabled)
{
	keyboard = new KEY_STATE[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
}

// Destructor
ModuleInput::~ModuleInput()
{
	delete[] keyboard;
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);
	ExitEngine = false;

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate(float dt)
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

	mouse_x /= SCREEN_SIZE;
	mouse_y /= SCREEN_SIZE;
	mouse_z = 0;

	for (int i = 0; i < 5; ++i)
	{
		if (buttons & SDL_BUTTON(i))
		{
			if (mouse_buttons[i] == KEY_IDLE)
				mouse_buttons[i] = KEY_DOWN;
			else
				mouse_buttons[i] = KEY_REPEAT;
		}
		else
		{
			if (mouse_buttons[i] == KEY_REPEAT || mouse_buttons[i] == KEY_DOWN)
				mouse_buttons[i] = KEY_UP;
			else
				mouse_buttons[i] = KEY_IDLE;
		}
	}

	mouse_x_motion = mouse_y_motion = 0;
	
	
	bool quit = false;
	SDL_Event e;
	
	while (SDL_PollEvent(&e))
	{
		ImGui_ImplSDL2_ProcessEvent(&e);
		switch (e.type)
		{
		case SDL_MOUSEWHEEL:
			mouse_z = e.wheel.y;

			if (e.wheel.y > 0) {
				float posx = 3;
				
			}

			if (e.wheel.y < 0) {
				float posx = 3;

			}

			if (e.wheel.y < 0) {

			}
			break;

		case SDL_MOUSEMOTION:
			mouse_x = e.motion.x / SCREEN_SIZE;
			mouse_y = e.motion.y / SCREEN_SIZE;

			mouse_x_motion = e.motion.xrel / SCREEN_SIZE;
			mouse_y_motion = e.motion.yrel / SCREEN_SIZE;
			break;

		case SDL_QUIT:
			quit = true;
			break;

		case SDL_WINDOWEVENT:
		{
			if (e.window.event == SDL_WINDOWEVENT_RESIZED)
				App->renderer3D->OnResize(e.window.data1, e.window.data2);
			break;
		}
		case SDL_DROPFILE:

			// FILE TYPE DIFFERENTATION IS NOT WORKING, WE ARE USING IF TEXTURE.HEIGHT/WIDTH==0 
			TextureInfo ImportedTexture;
			
			Drop_Path = e.drop.file;
			if (Drop_Path != "") {

				//FBX IN LOWERCASE
				if (CheckImportedFileType(".fbx", Drop_Path) != -1) {

					std::string FinalText = "[IMPORT]Importing Mesh(fbx) :" + Drop_Path;


					LOG(FinalText.c_str());
						const char* path_file = Drop_Path.c_str();
						App->meshimporter->LoadFile_Mesh(path_file);
						SDL_free((char*)path_file);

				}
				//FBX IN CAPS
				else if (CheckImportedFileType(".FBX", Drop_Path) != -1) {
					std::string FinalText = "[IMPORT]Importing Mesh(FBX) :" + Drop_Path;
					LOG(FinalText.c_str());
					const char* path_file = Drop_Path.c_str();
					App->meshimporter->LoadFile_Mesh(path_file);
					SDL_free((char*)path_file);

				}

				//PNG IN LOWERCASE

				else if (CheckImportedFileType(".png", Drop_Path) != -1) {
					
					const char* path_file = Drop_Path.c_str();

					std::string FinalText = "[IMPORT]Importing Mesh(png) :" + Drop_Path;
					LOG(FinalText.c_str());
					ImportedTexture = App->textureImporter->LoadTextureImage(path_file);

					App->textureImporter->AvailableTextures.push_back(&ImportedTexture);
					
					std::vector<Game_Object*>::iterator It= App->geometrymanager->ObjectsOnScene.begin();
					Game_Object* Item=*It;

					CheckSelectedChild(Item, ImportedTexture);

					SDL_free((char*)path_file);

				}

				//PNG IN CAPS
				else if (CheckImportedFileType(".PNG", Drop_Path) != -1) {


					const char* path_file = Drop_Path.c_str();
					std::string FinalText = "[IMPORT]Importing Mesh(PNG) :" + Drop_Path;
					LOG(FinalText.c_str());
					ImportedTexture = App->textureImporter->LoadTextureImage(path_file);

					App->textureImporter->AvailableTextures.push_back(&ImportedTexture);

					std::vector<Game_Object*>::iterator It = App->geometrymanager->ObjectsOnScene.begin();
					Game_Object* Item = *It;

					CheckSelectedChild(Item, ImportedTexture);

					SDL_free((char*)path_file);
					
				}

				//DDS IN LOWERCASE
				else if (CheckImportedFileType(".dds", Drop_Path) != -1) {
					const char* path_file = Drop_Path.c_str();
					std::string FinalText = "[IMPORT]Importing Mesh(dds) :" + Drop_Path;
					LOG(FinalText.c_str());
					ImportedTexture = App->textureImporter->LoadTextureImage(path_file);

					App->textureImporter->AvailableTextures.push_back(&ImportedTexture);

					std::vector<Game_Object*>::iterator It = App->geometrymanager->ObjectsOnScene.begin();
					Game_Object* Item = *It;

					CheckSelectedChild(Item, ImportedTexture);

					SDL_free((char*)path_file);
					
				}

				//DDS IN CAPS
				else if (CheckImportedFileType(".DDS", Drop_Path) != -1) {
					const char* path_file = Drop_Path.c_str();
					std::string FinalText = "[IMPORT]Importing Mesh(DDS) :" + Drop_Path;
					LOG(FinalText.c_str());
					ImportedTexture = App->textureImporter->LoadTextureImage(path_file);

					App->textureImporter->AvailableTextures.push_back(&ImportedTexture);

					std::vector<Game_Object*>::iterator It = App->geometrymanager->ObjectsOnScene.begin();
					Game_Object* Item = *It;

					CheckSelectedChild(Item, ImportedTexture);

					SDL_free((char*)path_file);
					
				}
			}

			else {
			    std::string FinalText = "[ERROR]Sorry, Could Not Load Object:%s" + Drop_Path;
			    LOG(FinalText.c_str());
				

			}

			break;
		}
	}

	if (quit == true || keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP || ExitEngine==true)

		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

update_status ModuleInput::Update(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	return update_status::UPDATE_CONTINUE;
}



// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

int ModuleInput::CheckImportedFileType(std::string string1, std::string string2)
{
	int M = string1.length();
	int N = string2.length();

	
	for (int i = 0; i <= N - M; i++) {

		int j;

		for (j = 0; j < M; j++) {
			if (string2[i + j] != string1[j]) {
				break;
			}
		}

		if (j == M) {
			return i;
		}
	}

	return -1;
}

void ModuleInput::CheckSelectedChild(Game_Object* Object,TextureInfo Texture)
{

	Component_Texture* MeshComp = (Component_Texture*)Object->GetComponent(Component_Types::Texture);

	if (Object->ToBeDrawInspector) {

		MeshComp->Texture->texture_id = Texture.texture_id;


		std::vector<Game_Object*>::iterator It = Object->Children_List.begin();
		for (int size = 0; size < Object->Children_List.size(); ++size) {
			Game_Object* Object = *It;

			CheckSelectedChild(Object, Texture);

				++It;
		}
	}
	else {

		std::vector<Game_Object*>::iterator It = Object->Children_List.begin();
		for (int size = 0; size < Object->Children_List.size(); ++size) {
			Game_Object* Object = *It;

			CheckSelectedChild(Object, Texture);

			++It;
		}
	}


}


