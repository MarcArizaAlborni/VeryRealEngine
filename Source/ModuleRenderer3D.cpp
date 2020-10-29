#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
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
	LOGFIX("Creating 3D Renderer context");
	bool ret = true;

	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if (context == NULL)
	{
		LOGFIX("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (ret == true)
	{
		//Use Vsync
		if (VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOGFIX("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			LOGFIX("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			LOGFIX("Error initializing OpenGL! %s\n", gluErrorString(error));
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
			LOGFIX("Error initializing OpenGL! %s\n", gluErrorString(error));
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
	
	//App->console->CreateConsolelog();
	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	return ret;
}

bool ModuleRenderer3D::Start()
{
	glEnable(GL_DEPTH_TEST);

	App->textureImporter->TextureHouse = App->textureImporter->LoadTextureImage("Assets/Textures/Baker_house.png");
	//App->textureImporter->TextureHousita = App->textureImporter->LoadTextureImage("Assets/Textures/house2tex.png");
	//App->textureImporter->TextureEarth = App->textureImporter->LoadTextureImage("Assets/Textures/earthtex.png");

	App->textureImporter->TextureCheckers = App->textureImporter->LoadCheckersTexture();
	App->meshimporter->LoadMesh("Assets/Models/House/BakerHouse.fbx");
	//App->meshimporter->LoadMesh("Assets/Models/house2.fbx");
	//App->meshimporter->LoadMesh("Assets/Models/earth.fbx");


	App->meshimporter->MeshesOnScene.at(0)->TextureData = App->textureImporter->TextureHouse;
	App->meshimporter->MeshesOnScene.at(1)->TextureData = App->textureImporter->TextureHouse;
	//App->meshimporter->MeshesOnScene.at(2)->TextureData = App->textureImporter->TextureHousita;
	//App->meshimporter->MeshesOnScene.at(3)->TextureData = App->textureImporter->TextureEarth;




		//App->meshimporter->LoadMesh("Assets/Models/Warrior/warrior.FBX");
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	return true;
}

void ModuleRenderer3D::GenerateVertexBuffer(Vertex_Sub* vertex, uint& size, uint& id_vertex)
{
	glGenBuffers(1, (GLuint*)&(id_vertex));
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_Sub) * size, vertex, GL_STATIC_DRAW);
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

void ModuleRenderer3D::GenerateNormalBuffer(GameObject* mesh, float& normals)
{
	uint val = 0;
	glGenBuffers(1, (GLuint*)&(mesh->MeshData.id_normals));
	glBindBuffer(GL_ARRAY_BUFFER, (GLuint)&(mesh->MeshData.id_normals));
	glBufferData(GL_ARRAY_BUFFER, sizeof(uint) * mesh->MeshData.id_normals * 3, mesh->MeshData.normals, GL_STATIC_DRAW);
}



// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	//glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for (uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();
	

	return UPDATE_CONTINUE;
}

update_status ModuleRenderer3D::Update(float dt)
{
	//glEnable(GL_DEPTH_TEST);
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	return UPDATE_CONTINUE;
}


// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	//glEnable(GL_DEPTH_TEST);

	
	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOGFIX("Destroying 3D Renderer");

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


//void ModuleRenderer3D::GenerateVertexBuffer(uint& id_vertex, const int& size, Vertex_Sub* vertex)
//{
//	glGenBuffers(1, (GLuint*)&(id_vertex));
//	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size * 3, vertex, GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}
//
//void ModuleRenderer3D::GenerateIndexBuffer(uint& id_index, const int& size, const uint* index)
//{
//	glGenBuffers(1, (GLuint*)&(id_index));
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * size, index, GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}
//
//void ModuleRenderer3D::GenerateVertexTexBuffer(uint& id_vertexTex, const int& sizeTex, const float* vertexTex) //Textures
//{
//	glGenBuffers(1, (GLuint*)&(id_vertexTex));
//	glBindBuffer(GL_ARRAY_BUFFER, id_vertexTex);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeTex, vertexTex, GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}

void ModuleRenderer3D::CreateConsolelog(const char file[], int line, const char* format, ...)
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
