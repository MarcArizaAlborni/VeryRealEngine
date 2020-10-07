#include "Application.h"
#include <list>
#include <iostream> 
#include <sstream> 
#include "Definitions.h"


Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	editor = new ModuleEditor(this);
	ImGui = new ModuleImGui(this);


	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(renderer3D);
	AddModule(editor);
	AddModule(ImGui);
	
}

Application::~Application()
{
	std::list<Module*>::reverse_iterator item = list_modules.rbegin();

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

	//Call Init() in all modules
	std::list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end())
	{
		(*item)->Init();
		item++;
	}



	std::list<Module*>::iterator item2 = list_modules.begin();
	
	//Call Start() in all modules

	item2 = list_modules.begin();

	while (item2 != list_modules.end())
	{
		(*item2)->Start();
		item2++;
	}


	return ret;
}

// ESTO NO VA
//bool Application::Start()
//{
//	std::list<Module*>::iterator item = list_modules.begin();
//
//	//Call Start() in all modules
//
//	item = list_modules.begin();
//
//	while (item != list_modules.end())
//	{
//		(*item)->Start();
//		item++;
//	}
//
//	return true;
//}




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

	std::list<Module*>::iterator item = list_modules.begin();

	update_status State;

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{

		State = (*item)->PreUpdate();

		//this is to allow esc to exit app
		if (State == UPDATE_STOP) {
			return UPDATE_STOP;
		}
		item++;
	}

	item = list_modules.begin();

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		(*item)->Update();
		item++;
	}

	item = list_modules.begin();

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		(*item)->PostUpdate();
		item++;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	std::list<Module*>::reverse_iterator item = list_modules.rbegin();

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

uint Application::GetFramerateLimit() const
{
	if (capped_ms > 0)
		return (uint)((1.0f / (float)capped_ms) * 1000.0f);
	else
		return 0;
}


// SAVE & LOAD

bool Application::LoadSaveFile()
{
	bool ret;





	return ret;
}


bool Application::SaveSaveFile()
{


	bool ret;




	return ret;
}


bool SaveLoad::Save(SaveLoad item, const char* file)
{

	bool ret = true;

	//if (file !=nullptr) {
	//	
	//	std::ofstream stream(file, std::ofstream::out);
	//	SDL_assert(stream.is_open());

	//	stream << std::setw(4) << item << std::endl;
	//
	//	stream.close();
	//}

	return ret;

}

SaveLoad SaveLoad::Load(const char* file)
{

	SaveLoad item;
	/*SDL_assert(file != nullptr);


	std::ifstream stream(file, std::ifstream::in);
	SDL_assert(stream.is_open());


	try {
		item = json::parse(stream);
	}
	catch (json::parse_error& e) {
		LOG("Parse Error while Loading File: %c", e.what());
	}

	stream.close();

	return item;*/



	return item;
}
