#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleEditorConsole.h"
#include "ModuleRenderer3D.h"
#include "ModuleTextureImporter.h"
#include "ModuleMeshImporter.h"

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
	LOGFIX("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);
	ExitEngine = false;

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOGFIX("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
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
				
				//App->camera->Position.x -= posx;
				
			}

			if (e.wheel.y < 0) {
				float posx = 3;

				//App->camera->Position.x -= posx;

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

						LOGFIX("Importing Mesh(fbx) with DropFile: Path-> %s", Drop_Path);
						const char* path_file = Drop_Path.c_str();
						App->meshimporter->LoadMesh(path_file);
						SDL_free((char*)path_file);

				}
				//FBX IN CAPS
				else if (CheckImportedFileType(".FBX", Drop_Path) != -1) {

					LOGFIX("Importing Mesh(FBX) with DropFile: Path-> %s", Drop_Path);
					const char* path_file = Drop_Path.c_str();
					App->meshimporter->LoadMesh(path_file);
					SDL_free((char*)path_file);

				}

				//PNG IN LOWERCASE

				else if (CheckImportedFileType(".png", Drop_Path) != -1) {
					
					const char* path_file = Drop_Path.c_str();
					LOGFIX("Importing Texture(png) with DropFile: Path-> %s", Drop_Path);
					ImportedTexture = App->textureImporter->LoadTextureImage(path_file);
					

					App->textureImporter->AvailableTextures.push_back(&ImportedTexture);

					std::vector<GameObject*>::iterator MeshTextureIterator = App->meshimporter->MeshesOnScene.begin();
					for (int a = 0; a < App->meshimporter->MeshesOnScene.size(); ++a) {

						GameObject* TexturedMesh;

						TexturedMesh = *MeshTextureIterator;
						if (TexturedMesh->ToBeDrawInspector == true) {

							TexturedMesh->TextureData.texture_id = ImportedTexture.texture_id;

							if (TexturedMesh->ChildObjects.size() > 0) {

								std::vector<GameObject*>::iterator ChildMeshTextureIterator = TexturedMesh->ChildObjects.begin();
								for (int b = 0; b < TexturedMesh->ChildObjects.size(); ++b) {

									GameObject* ChildTexturedMesh;

									ChildTexturedMesh = *ChildMeshTextureIterator;

									ChildTexturedMesh->TextureData.texture_id = ImportedTexture.texture_id;

									++ChildMeshTextureIterator;
								}
							}
						}
						else {

							std::vector<GameObject*>::iterator ChildMeshTextureIterator2 = TexturedMesh->ChildObjects.begin();
							for (int b = 0; b < TexturedMesh->ChildObjects.size(); ++b) {

								GameObject* ChildTexturedMesh;


								ChildTexturedMesh = *ChildMeshTextureIterator2;

								if (ChildTexturedMesh->ToBeDrawInspector == true) {
									ChildTexturedMesh->TextureData.texture_id = ImportedTexture.texture_id;
								}

								++ChildMeshTextureIterator2;
							}
						}

						++MeshTextureIterator;

					}

					SDL_free((char*)path_file);
					
				}

				//PNG IN CAPS
				else if (CheckImportedFileType(".PNG", Drop_Path) != -1) {

					LOGFIX("Importing Texture(PNG) with DropFile: Path-> %s", Drop_Path);
					const char* path_file = Drop_Path.c_str();
					ImportedTexture = App->textureImporter->LoadTextureImage(path_file);

						App->textureImporter->AvailableTextures.push_back(&ImportedTexture);

						std::vector<GameObject*>::iterator MeshTextureIterator = App->meshimporter->MeshesOnScene.begin();
						for (int a = 0; a < App->meshimporter->MeshesOnScene.size(); ++a) {

							GameObject* TexturedMesh;

							TexturedMesh = *MeshTextureIterator;
							if (TexturedMesh->ToBeDrawInspector == true) {

								TexturedMesh->TextureData.texture_id = ImportedTexture.texture_id;

								if (TexturedMesh->ChildObjects.size() > 0) {

									std::vector<GameObject*>::iterator ChildMeshTextureIterator = TexturedMesh->ChildObjects.begin();
									for (int b = 0; b < TexturedMesh->ChildObjects.size(); ++b) {

										GameObject* ChildTexturedMesh;

										ChildTexturedMesh = *ChildMeshTextureIterator;

										ChildTexturedMesh->TextureData.texture_id = ImportedTexture.texture_id;

										++ChildMeshTextureIterator;
									}
								}
							}
							else {

								std::vector<GameObject*>::iterator ChildMeshTextureIterator2 = TexturedMesh->ChildObjects.begin();
								for (int b = 0; b < TexturedMesh->ChildObjects.size(); ++b) {

									GameObject* ChildTexturedMesh;

									ChildTexturedMesh = *ChildMeshTextureIterator2;

									if (ChildTexturedMesh->ToBeDrawInspector == true) {
										ChildTexturedMesh->TextureData.texture_id = ImportedTexture.texture_id;
									}

									++ChildMeshTextureIterator2;
								}
							}

							++MeshTextureIterator;

						}

						SDL_free((char*)path_file);
					
				}

				//DDS IN LOWERCASE
				else if (CheckImportedFileType(".dds", Drop_Path) != -1) {
				LOGFIX("Importing Texture(dds) with DropFile: Path-> %s", Drop_Path);
					const char* path_file = Drop_Path.c_str();
					ImportedTexture = App->textureImporter->LoadTextureImage(path_file);
				
						App->textureImporter->AvailableTextures.push_back(&ImportedTexture);
						std::vector<GameObject*>::iterator MeshTextureIterator = App->meshimporter->MeshesOnScene.begin();
						for (int a = 0; a < App->meshimporter->MeshesOnScene.size(); ++a) {

							GameObject* TexturedMesh;

							TexturedMesh = *MeshTextureIterator;
							if (TexturedMesh->ToBeDrawInspector == true) {

								TexturedMesh->TextureData.texture_id = ImportedTexture.texture_id;

								if (TexturedMesh->ChildObjects.size() > 0) {

									std::vector<GameObject*>::iterator ChildMeshTextureIterator = TexturedMesh->ChildObjects.begin();
									for (int b = 0; b < TexturedMesh->ChildObjects.size(); ++b) {

										GameObject* ChildTexturedMesh;

										ChildTexturedMesh = *ChildMeshTextureIterator;

										ChildTexturedMesh->TextureData.texture_id = ImportedTexture.texture_id;

										++ChildMeshTextureIterator;
									}

								}
							}
							else {

								std::vector<GameObject*>::iterator ChildMeshTextureIterator2 = TexturedMesh->ChildObjects.begin();
								for (int b = 0; b < TexturedMesh->ChildObjects.size(); ++b) {

									GameObject* ChildTexturedMesh;


									ChildTexturedMesh = *ChildMeshTextureIterator2;

									if (ChildTexturedMesh->ToBeDrawInspector == true) {
										ChildTexturedMesh->TextureData.texture_id = ImportedTexture.texture_id;
									}

									++ChildMeshTextureIterator2;
								}
							}

							++MeshTextureIterator;

						}

						SDL_free((char*)path_file);
					
				}

				//DDS IN CAPS
				else if (CheckImportedFileType(".DDS", Drop_Path) != -1) {
				LOGFIX("Importing Texture(DDS) with DropFile: Path-> %s", Drop_Path);
					   const char* path_file = Drop_Path.c_str();
					   ImportedTexture = App->textureImporter->LoadTextureImage(path_file);

						 App->textureImporter->AvailableTextures.push_back(&ImportedTexture);
						 std::vector<GameObject*>::iterator MeshTextureIterator = App->meshimporter->MeshesOnScene.begin();
						 for (int a = 0; a < App->meshimporter->MeshesOnScene.size(); ++a) {

							GameObject* TexturedMesh;

							TexturedMesh = *MeshTextureIterator;
							if (TexturedMesh->ToBeDrawInspector == true) {

								TexturedMesh->TextureData.texture_id = ImportedTexture.texture_id;

								if (TexturedMesh->ChildObjects.size() > 0) {

									std::vector<GameObject*>::iterator ChildMeshTextureIterator = TexturedMesh->ChildObjects.begin();
									for (int b = 0; b < TexturedMesh->ChildObjects.size(); ++b) {

										GameObject* ChildTexturedMesh;

										ChildTexturedMesh = *ChildMeshTextureIterator;

										ChildTexturedMesh->TextureData.texture_id = ImportedTexture.texture_id;

										++ChildMeshTextureIterator;
									}

								}
							}
							else {

								std::vector<GameObject*>::iterator ChildMeshTextureIterator2 = TexturedMesh->ChildObjects.begin();
								for (int b = 0; b < TexturedMesh->ChildObjects.size(); ++b) {

									GameObject* ChildTexturedMesh;


									ChildTexturedMesh = *ChildMeshTextureIterator2;

									if (ChildTexturedMesh->ToBeDrawInspector == true) {
										ChildTexturedMesh->TextureData.texture_id = ImportedTexture.texture_id;
									}

									++ChildMeshTextureIterator2;
								}
							}

							++MeshTextureIterator;

						 }

						SDL_free((char*)path_file);
					
				}
				



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
	LOGFIX("Quitting SDL input event subsystem");
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

void ModuleInput::CreateConsolelog(const char file[], int line, const char* format, ...)
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
