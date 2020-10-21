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
	hierarchy = new ModuleHierarchy(this);
	editor = new ModuleEditor(this);
	mainMenubar = new ModuleEditorMainMenuBar(this);
	configWindow = new ModuleEditorConfiguration(this);
	console = new ModuleEditorConsole(this);

	textureImporter = new ModuleTextureImporter(this);
	meshimporter = new ModuleMeshImporter(this);

	LoadSave = new LoadSaveMod(this);

	geometryloader = new ModuleGeometryLoader(this);
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

	AddModule(textureImporter);
	AddModule(meshimporter);
	AddModule(hierarchy);
	AddModule(LoadSave);
	
	AddModule(renderer3D);
	AddModule(geometryloader);
	
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

}

// ---------------------------------------------
void Application::FinishUpdate()
{

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
