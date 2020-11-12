#include "Application.h"
#include <list>
#include <iostream> 
#include <sstream> 
#include "Definitions.h"
#include <fstream>
#include "ModuleCamera3D.h"

Application::Application() : debug(false), renderPrimitives(true), dt(0.0f)
{
	window = new ModuleWindow(this);
	camera = new ModuleCamera3D(this);
	input = new ModuleInput(this );
	hierarchy = new ModuleHierarchyGameObject(this);
	editor = new ModuleEditor(this);
	mainMenubar = new ModuleEditorMainMenuBar(this);
	configWindow = new ModuleEditorConfiguration(this);
	console = new ModuleEditorConsole(this);
	inspector = new ModuleInspectorGameObject(this);

	textureImporter = new ModuleTextureImporter(this);
	meshimporter = new ModuleMeshImporter(this);
	resources = new ResourceManager(this);
	


	filemanager = new ModuleFileSystem(this);


	geometrymanager = new ModuleGeometryManager(this);
	renderer3D = new ModuleRenderer3D(this);
	
	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	
	AddModule(editor);
	AddModule(mainMenubar);
	AddModule(configWindow);
	AddModule(console);
	AddModule(filemanager);
	AddModule(textureImporter);
	AddModule(meshimporter);
	AddModule(hierarchy);
	AddModule(inspector);
	AddModule(resources);

	
	AddModule(renderer3D);
	AddModule(geometrymanager);
	
}

Application::~Application()
{
	std::vector<Module*>::reverse_iterator item = list_modules.rbegin();

	while (item != list_modules.rend())
	{
		RELEASE((*item));
		item++;
	}

	list_modules.clear();
}

bool Application::Init()
{
	bool ret = true;

	dt = 0.5f;
	
	//Call Init() in all modules
	std::vector<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end())
	{
		(*item)->Init();
		item++;
	}



	std::vector<Module*>::iterator item2 = list_modules.begin();
	
	//Call Start() in all modules

	item2 = list_modules.begin();

	while (item2 != list_modules.end())
	{
		(*item2)->Start();
		item2++;
	}


	return ret;
}



// ---------------------------------------------
void Application::PrepareUpdate()
{
	frame_count++;
	last_sec_frame_count++;

	dt = (float)frame_time.ReadSec();
	frame_time.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	if (last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;
	}

	uint last_frame_ms = frame_time.Read();
	uint frames_on_last_update = prev_last_sec_frame_count;

	fps_log.push_back(frames_on_last_update);
	if (fps_log.size() > Bars)
	{
		fps_log.erase(fps_log.begin());
	}
		
	ms_log.push_back(last_frame_ms);
	if (ms_log.size() > Bars)
	{
		ms_log.erase(ms_log.begin());
	}
		

	if (max_framerateCap > 0)
	{
		capped_ms = 1000 / max_framerateCap;
	}
		
	else
	{
		capped_ms = 0;
	}
		

	if (capped_ms > 0 && last_frame_ms < capped_ms)
	{
		SDL_Delay(capped_ms - last_frame_ms);
	}
		
}



// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();

	std::vector<Module*>::iterator item = list_modules.begin();

	update_status State;

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{

		State = (*item)->PreUpdate(dt);

		//this is to allow esc to exit app
		if (State == UPDATE_STOP) {
			return UPDATE_STOP;
		}
		item++;
	}

	item = list_modules.begin();

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		(*item)->Update(dt);
		item++;
	}

	item = list_modules.begin();

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		(*item)->PostUpdate(dt);
		item++;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	std::vector<Module*>::reverse_iterator item = list_modules.rbegin();

	while (item != list_modules.rend() && ret == true)
	{
		ret = (*item)->CleanUp();
		item++;
	}
	return ret;
}


int Application::GiveRandomNum_Undefined()
{

	return 0;
}

int Application::GiveRandomNum_Defined(int Min, int Max)
{

	return 0;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}


void Application::RequestBrowser(const char* url) const
{
	ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}



float Application::GetDT()
{
	return dt;
}

// SAVE & LOAD


extern Application* App;


//
//
