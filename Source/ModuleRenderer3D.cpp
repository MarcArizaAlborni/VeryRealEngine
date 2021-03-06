#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleScene.h"
#include "ModuleCamera3D.h"
#include "ComponentCamera.h"
#include "ModuleTextureImporter.h"
#include "ComponentMesh.h"
#include "ModuleEditor.h"
#include "libraries/Glew/include/GL/glew.h"
#include "libraries/SDL/include/SDL_opengl.h"
#include "Primitive.h"
#include "ModuleMeshImporter.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ModuleTextureImporter.h"

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleRenderer3D::ModuleRenderer3D(Application* app, const char* name, bool start_enabled) : Module(app,"Render3D", start_enabled)
{
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG("Creating 3D Renderer context");
	bool ret = true;

	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if (context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (ret == true)
	{
		//Use Vsync
		if (VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;


		}

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);

		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		GLfloat LightModelAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);

		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();

		GLfloat MaterialAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
	}
	
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	return ret;
}

bool ModuleRenderer3D::Start()
{
	glEnable(GL_DEPTH_TEST);

	LoadIconsTextures();

	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	return true;
}

void ModuleRenderer3D::GenerateVertexBuffer(float3* vertex, uint& size, uint& id_vertex)
{
	glGenBuffers(1, (GLuint*)&(id_vertex));
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float3) * size, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModuleRenderer3D::GenerateIndexBuffer(uint* index, uint& size, uint& id_index)
{
	glGenBuffers(1, (GLuint*)&(id_index));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * size, index, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModuleRenderer3D::GenerateTextBuffer(float* text_coords, uint& num_text_coords, uint& id_text_coords)
{
	glGenBuffers(1, (GLuint*)&(id_text_coords));
	glBindBuffer(GL_ARRAY_BUFFER, id_text_coords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_text_coords * 2, text_coords, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModuleRenderer3D::GenerateNormalBuffer(MeshInfo* Mesh, float3* normals)
{
	if (Mesh->normals != nullptr) {
		if (Mesh->id_normals != NULL) {

			uint val = 0;
			glGenBuffers(1, (GLuint*)&(Mesh->id_normals));
			glBindBuffer(GL_ARRAY_BUFFER, (GLuint) & (Mesh->id_normals));
			glBufferData(GL_ARRAY_BUFFER, sizeof(uint) * Mesh->id_normals * 3, Mesh->normals, GL_STATIC_DRAW);
		}
	}
}



// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	//glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->scene_camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->scene_camera->Position.x, App->camera->scene_camera->Position.y, App->camera->scene_camera->Position.z);

	for (uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();
	
	App->camera->scene_camera->DrawFrustum(App->camera->scene_camera->GetFrustumPoints(), Color(0.30, 0.85, 0.96, 0));

	return UPDATE_CONTINUE;
}

update_status ModuleRenderer3D::Update(float dt)
{
	return UPDATE_CONTINUE;
}


// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{

	
	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");

	SDL_GL_DeleteContext(context);

	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



void ModuleRenderer3D::LoadIconsTextures()
{
	App->textureImporter->DrawIconHierarchyOpen = App->textureImporter->LoadTextureImage("Assets/Textures/icons/draw_open_hierarchy_icon.png");
	App->textureImporter->DrawIconHierarchyClosed = App->textureImporter->LoadTextureImage("Assets/Textures/icons/draw_closed_hierarchy_icon.png");
	App->textureImporter->cat_crying = App->textureImporter->LoadTextureImage("Assets/Textures/icons/cat.png ");
	App->textureImporter->MeshIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/mesh.png");
	App->textureImporter->TextureIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/texture.png");
	App->textureImporter->FolderIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/folder.png");
	App->textureImporter->BackIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/back.png");
	App->textureImporter->AddFolderIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/addfolder.png");
	App->textureImporter->RemoveFolderIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/removefolder.png");
	App->textureImporter->RenameFolderIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/renamefolder.png");
	App->textureImporter->DrawTrashCanIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/trash.png");

	App->textureImporter->DrawTickIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/tick_icon.png");
	App->textureImporter->DrawPlayIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/play_icon.png");
	App->textureImporter->DrawPauseIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/pause_icon.png");
	App->textureImporter->DrawStopIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/stop_icon.png");
	App->textureImporter->DrawResumeIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/Resume_Icon.png");
	App->textureImporter->DrawReloadIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/Reload.png");

	App->textureImporter->DrawListenerIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/Listener Icon.png");
	App->textureImporter->DrawMuteIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/volume off.png");
	App->textureImporter->DrawFullVoIcon = App->textureImporter->LoadTextureImage("Assets/Textures/Icons/Volume on.png");
}
