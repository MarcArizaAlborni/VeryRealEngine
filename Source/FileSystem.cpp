#include "Globals.h"
#include "Application.h"
#include "Definitions.h"
#include "FileSystem.h"
#include "libraries/PhysFS/include/physfs.h"
#include "libraries/Assimp/Assimp/include/cfileio.h"
#include "libraries/Assimp/Assimp/include/types.h"

#pragma comment( lib, "libraries/PhysFS/libx86/physfs.lib" )

ModuleFileSystem::ModuleFileSystem(Application* app, const char* name, bool start_enabled) : Module(app, "FileSystem", start_enabled)
{
	// Init PhysFS
	char* base_path = SDL_GetBasePath();
	PHYSFS_init(base_path);
	SDL_free(base_path);

	// Default Path
	AddPath(".");

	if (0 && name != nullptr)
	{
		AddPath(name);
	}

	// Creates an empty file if the dir is not found
	if (PHYSFS_setWriteDir(".") == 0)
	{
		LOG("File System error while creating write dir: %s\n", PHYSFS_getLastError());
	}
		
	// Check if standard paths exist
	const char* paths[] = {
		LIBRARY_FOLDER, LIBRARY_TEXTURES_FOLDER, LIBRARY_MESH_FOLDER, LIBRARY_MODELS_FOLDER,LIBRARY_SCENE_FOLDER
	};

	for (uint i = 0; i < sizeof(paths) / sizeof(const char*); ++i)
	{
		// Adds to the existing dirs your path
		if (PHYSFS_exists(paths[i]) == 0)
		{
			PHYSFS_mkdir(paths[i]);
		}
			
	}

}

// Destructor
ModuleFileSystem::~ModuleFileSystem()
{
	PHYSFS_deinit();
}

// Called before quitting
bool ModuleFileSystem::CleanUp()
{
	LOG("Freeing File System subsystem");

	return true;
}

bool ModuleFileSystem::AddPath(const char* path_or_zip)
{
	bool ret = false;

	//Add an archive or directory to the search path.

	if (PHYSFS_mount(path_or_zip, nullptr, 1) == 0)
	{
		LOG("File System error while adding a path or zip: %s\n", PHYSFS_getLastError());
	}
	else
	{
		ret = true;
	}
		
	return ret;
}

// Force to always use lowercase and / as folder separator
char normalize_char(char c)
{
	if (c == '\\')
	{
		return '/';
	}

	return tolower(c);
}

std::string ModuleFileSystem::NormalizeNodePath(const char* full_path)
{
	std::string normalized_path(full_path);

	for (uint i = 0; i < normalized_path.size(); ++i)
	{
		if (normalized_path[i] == '\\')
		{
			normalized_path[i] = '/';
		}
	}

	return normalized_path;
}

void ModuleFileSystem::NormalizePath(std::string& full_path) const
{
	for (std::string::iterator it = full_path.begin(); it != full_path.end(); ++it)
	{
		if (*it == '\\')
		{
			*it = '/';
		}
			
		else
		{
			*it = tolower(*it);
		}	
	}
}

void ModuleFileSystem::SplitFilePath(const char* full_path, std::string* path, std::string* file, std::string* extension) const
{
	if (full_path != nullptr)
	{
		std::string full(full_path);
		NormalizePath(full);
		size_t pos_separator = full.find_last_of("\\/");
		size_t pos_dot = full.find_last_of(".");

		if (path != nullptr)
		{
			if (pos_separator < full.length())
				*path = full.substr(0, pos_separator + 1);
			else
				path->clear();
		}

		if (file != nullptr)
		{
			if (pos_separator < full.length())
				*file = full.substr(pos_separator + 1);
			else
				*file = full;
		}

		if (extension != nullptr)
		{
			if (pos_dot < full.length())
			{
				*extension = full.substr(pos_dot + 1);
				if (file != nullptr)
					file->resize(file->length() - extension->length() - 1);
			}
			else
				extension->clear();
		}
	}
}

int close_sdl_rwops(SDL_RWops* rw)
{
	RELEASE_ARRAY(rw->hidden.mem.base);
	SDL_FreeRW(rw);
	return 0;
}

std::string ModuleFileSystem::GetFileAndExtension(const char* path)
{
	std::string full_path = path;
	std::string file = "";
	std::string extension = "";															// Just for safety check purposes.

	full_path = NormalizeNodePath(full_path.c_str());											// Will swap all '\\' for '/'.														

	size_t file_start = full_path.find_last_of("/");									// Gets the position of the last '/' of the string. Returns npos if none was found.
	size_t extension_start = full_path.find_last_of(".");									// Gets the position of the last '.' of the string. Returns npos if none was found.

	if (file_start != std::string::npos)
	{
		file = full_path.substr(file_start + 1, full_path.size());							// Will get the string past the last slash
	}
	else
	{
		LOG("[WARNING] Path %s does not have any file!", path);
	}

	if (extension_start != std::string::npos)
	{
		extension = full_path.substr(extension_start + 1, full_path.size());				// Will get the string past the last dot of the path string. Ex: File.ext --> ext

		if (extension == "")
		{
			LOG("[WARNING] Path %s does not have any file extension!", path);
		}
	}

	return full_path;
}