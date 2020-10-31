#include "Globals.h"
#include "Application.h"
#include "FileManager.h"
#include "libraries/Assimp/Assimp/include/cimport.h"
#include "libraries/Assimp/Assimp/include/scene.h"
#include "libraries/Assimp/Assimp/include/postprocess.h"
#pragma comment (lib, "libraries/Assimp/Assimp/libx86/assimp.lib")

ModuleFileManager::ModuleFileManager(Application* app, const char* name, bool start_enabled) : Module(app,"SaveLoad", start_enabled)
{
	
}

ModuleFileManager::~ModuleFileManager()
{
	
}

bool ModuleFileManager::Init()
{
	return true;
}

bool ModuleFileManager::CleanUp()
{
	return true;
}

update_status ModuleFileManager::Update(float dt)
{
	return UPDATE_CONTINUE;
}

void ModuleFileManager::StoreImportedFile(char* filepath)
{
	/*uint size=sizeof(filepath);
	
	
	SavedFiles InfoScene;

	InfoScene.id_File = ImportedFilesList.size() +1 ;
	
	InfoScene.Information=aiImportFileFromMemory(filepath, size, aiProcessPreset_TargetRealtime_MaxQuality,nullptr);

	ImportedFilesList.push_back(&InfoScene);*/


}

void ModuleFileManager::CreateConsolelog(const char file[], int line, const char* format, ...)
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

