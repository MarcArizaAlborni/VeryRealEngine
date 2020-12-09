#ifndef __MODULEFILESYSTEM_H__
#define __MODULEFILESYSTEM_H__

#include "Module.h"
#include <vector>
#include <string>

// Allows you to use pointers to memory instead of files
struct SDL_RWops;
int close_sdl_rwops(SDL_RWops* rwops);


class ModuleFileSystem : public Module
{
public:

	ModuleFileSystem(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleFileSystem();
	bool CleanUp() override;

	bool AddPath(const char* path_or_zip);



	void SplitFilePath(const char* full_path, std::string* path, std::string* file = nullptr, std::string* extension = nullptr) const;
	std::string NormalizeNodePath(const char* full_path);
	void NormalizePath(std::string& full_path) const;
	




	std::string GetFileAndExtension(const char* path);
};

#endif // __MODULEFILESYSTEM_H__
