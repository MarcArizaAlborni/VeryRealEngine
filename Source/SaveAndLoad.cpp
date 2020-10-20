#include "Globals.h"
#include "Application.h"
#include "SaveAndLoad.h"

LoadSaveMod::LoadSaveMod(Application* app, const char* name, bool start_enabled) : Module(app,"SaveLoad", start_enabled)
{
	
}

LoadSaveMod::~LoadSaveMod()
{
	
}

bool LoadSaveMod::Init()
{
	return true;
}

bool LoadSaveMod::CleanUp()
{
	return true;
}


bool LoadSaveMod::Save(json& obj, const char* file) 
{
	bool ret = true;

	if (file == nullptr) {
		SDL_assert(false);	
	}
	else {
		std::ofstream stream(file, std::ofstream::out);
		SDL_assert(stream.is_open());

		stream << std::setw(2) << obj << std::endl;
		stream.close();
	}

	return ret;
}

json LoadSaveMod::Load(const char* file) 
{
	SDL_assert(file != nullptr);	

	json obj;
	std::ifstream stream(file, std::ifstream::in);
	SDL_assert(stream.is_open());

	try {
		obj = json::parse(stream);
	}
	catch (json::parse_error& e) {
		LOGFIX("Parse Error while Loading File: %c", e.what());
	}

	stream.close();

	return obj;
}

void LoadSaveMod::LoadFromFile(json& item)
{

	App->camera->Position.x = item["Camera"]["PositionX"].get<float>();
	App->camera->Position.y = item["Camera"]["PositionY"].get<float>();
	App->camera->Position.z = item["Camera"]["Position<"].get<float>();


}

void LoadSaveMod::SaveintoFileConfig()
{
	bool ret = true;


	json config = {
		{"App", {
			{"Title","Very Real Engine"},
		}},

		{"Window", {
			{"Width", "error" },
			{"Height","error"},
			{"Fullscreen", "error"},
			{"Resizable", "error"},
			{"Borderless", "error"},
			{"FullscreenDesktop", "error"}
		}},


		{"GUI", {
			{"ConfigurationWindow", "bon dia"},

		}},

		{"Camera", {
			{"PositionX",App->camera->Position.x},
			{"PositionY",App->camera->Position.y},
			{"PositionZ",App->camera->Position.z},
		}},
	};

	Save(config, SaveFileName.c_str());

	
}

void LoadSaveMod::CreateConsolelog(const char file[], int line, const char* format, ...)
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

