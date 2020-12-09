#include "Globals.h"
#include "Application.h"
#include "Definitions.h"
#include "FileSystem.h"
#include "Component.h"
#include "ComponentTexture.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"
#include "ModuleMeshImporter.h"
#include "ModuleTextureImporter.h"
#include "GameObject.h"
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
		
	//// Check if standard paths exist
	//const char* paths[] = {
	//	LIBRARY_FOLDER, LIBRARY_TEXTURES_FOLDER, LIBRARY_MESH_FOLDER, LIBRARY_MODELS_FOLDER,LIBRARY_SCENE_FOLDER
	//};

	//for (uint i = 0; i < sizeof(paths) / sizeof(const char*); ++i)
	//{
	//	// Adds to the existing dirs your path
	//	if (PHYSFS_exists(paths[i]) == 0)
	//	{
	//		PHYSFS_mkdir(paths[i]);
	//	}
	//		
	//}


	CreateLibraryDirectories();

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

// Checks if a file exists
bool ModuleFileSystem::Exists(const char* file) const
{
	return PHYSFS_exists(file) != 0;
}

bool ModuleFileSystem::CreateDir(const char* dir)
{
	if (IsDirectory(dir) == false)
	{
		PHYSFS_mkdir(dir);
		return true;
	}
	return false;
}

// Checks if a file is inside a directory
bool ModuleFileSystem::IsDirectory(const char* file) const
{
	return PHYSFS_isDirectory(file) != 0;
}

// Adds a directory
void ModuleFileSystem::CreateDirectory(const char* directory)
{
	PHYSFS_mkdir(directory);
}

//Gets a file listing of a search path's directory.

void ModuleFileSystem::DiscoverFiles(const char* directory, std::vector<std::string>& file_list, std::vector<std::string>& direction_list) const
{
	char** rc = PHYSFS_enumerateFiles(directory);

	std::string dir(directory);

	for (char** i = rc; *i != nullptr; i++)
	{
		if (PHYSFS_isDirectory((dir + *i).c_str()))
		{
			direction_list.push_back(*i);
		}
		else
		{
			file_list.push_back(*i);
		}
	}

	PHYSFS_freeList(rc);
}

bool ModuleFileSystem::CopyFromOutsideFS(const char* full_path, const char* destination)
{
	// Only place we acces non virtual filesystem (defined functions)
	bool ret = false;

	char buf[8192];
	size_t size;

	FILE* source = nullptr;
	fopen_s(&source, full_path, "rb");
	PHYSFS_file* dest = PHYSFS_openWrite(destination);

	if (source && dest)
	{
		while (size = fread_s(buf, 8192, 1, 8192, source))
		{
			PHYSFS_write(dest, buf, 1, size);
		}
			
		fclose(source);
		PHYSFS_close(dest);
		ret = true;

		LOG("File System copied from [%s] to [%s]", full_path, destination);
	}
	else
	{
		LOG("File System error while copying from [%s] to [%s]", full_path, destination);
	}

	return ret;
}

bool ModuleFileSystem::Copy(const char* source, const char* destination)
{
	bool ret = false;

	char buf[8192];

	PHYSFS_file* src = PHYSFS_openRead(source);
	PHYSFS_file* dst = PHYSFS_openWrite(destination);

	PHYSFS_sint32 size;

	if (src && dst)
	{
		while (size = (PHYSFS_sint32)PHYSFS_read(src, buf, 1, 8192))
		{
			PHYSFS_write(dst, buf, 1, size);
		}

		PHYSFS_close(src);
		PHYSFS_close(dst);
		ret = true;

		LOG("File System copied form [%s] to [%s]", source, destination);
	}
	else
	{
		LOG("File System error while copy from [%s] to [%s]", source, destination);
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

bool ModuleFileSystem::IsInDirectory(const char* directory, const char* p)
{
	bool ret = true;

	std::string dir = directory;
	std::string path = p;

	std::size_t found = path.find(dir);
	if (found != std::string::npos)
	{
		ret = true;
	}
	else
	{
		ret = false;
	}

	return ret;
}

void ModuleFileSystem::CreateLibraryDirectories()
{
	
	CreateDir(LIBRARY_FOLDER);
	CreateDir(LIBRARY_TEXTURES_FOLDER);
	CreateDir(LIBRARY_MESH_FOLDER);
	CreateDir(LIBRARY_MODELS_FOLDER);
	CreateDir(LIBRARY_SCENE_FOLDER);
	
}

bool ModuleFileSystem::RemovePath(std::string* directory, const char* p)
{
	bool ret = true;

	std::size_t found = directory->find(p);

	if (found != std::string::npos)
	{
		directory->erase(found, 6);
		ret = true;
	}
	else
	{
		ret = false;
	}
		
	return ret;
}

unsigned int ModuleFileSystem::Load(const char* path, const char* file, char** buffer) const
{
	std::string full_path(path);
	full_path += file;
	return Load(full_path.c_str(), buffer);
}

// Read a file and writes it on a buffer
uint ModuleFileSystem::Load(const char* file, char** buffer) const
{
	uint ret = 0;
	PHYSFS_file* fs_file = PHYSFS_openRead(file);

	if (fs_file != nullptr)
	{
		PHYSFS_sint32 size = (PHYSFS_sint32)PHYSFS_fileLength(fs_file);

		if (size > 0)
		{
			*buffer = new char[size];
			uint readed = (uint)PHYSFS_read(fs_file, *buffer, 1, size);
			if (readed != size)
			{
				LOG("File System error while reading %s: %s\n", file, PHYSFS_getLastError());
				RELEASE(buffer);
			}
			else
			{
				ret = readed;
			}
		}

		if (PHYSFS_close(fs_file) == 0)
		{
			LOG("File System error while closing  %s: %s\n", file, PHYSFS_getLastError());
		}
	}
	else
	{
		LOG("File System error while opening %s: %s\n", file, PHYSFS_getLastError());
	}
		
	return ret;
}

SDL_RWops* ModuleFileSystem::Load(const char* file) const
{
	char* buffer;
	int size = Load(file, &buffer);

	if (size > 0)
	{
		SDL_RWops* r = SDL_RWFromConstMem(buffer, size);
		if (r != nullptr)
		{
			r->close = close_sdl_rwops;
		}
		
		return r;
	}
	else
	{
		return nullptr;
	}
		
}

int close_sdl_rwops(SDL_RWops* rw)
{
	RELEASE_ARRAY(rw->hidden.mem.base);
	SDL_FreeRW(rw);
	return 0;
}


// Saves all buffers to disk
uint ModuleFileSystem::Save(const char* file, const void* buffer, unsigned int size, bool append) const
{
	unsigned int ret = 0;

	bool overwrite = PHYSFS_exists(file) != 0;
	PHYSFS_file* fs_file = (append) ? PHYSFS_openAppend(file) : PHYSFS_openWrite(file);

	if (fs_file != nullptr)
	{
		uint written = (uint)PHYSFS_write(fs_file, (const void*)buffer, 1, size);
		if (written != size)
		{
			LOG("File System error while writing to file %s: %s", file, PHYSFS_getLastError());
		}
		else
		{
			if (append == true)
			{
				LOG("Added %u data to [%s%s]", size, PHYSFS_getWriteDir(), file);
			}
			else if (overwrite == false)
			{
				LOG("New file created [%s%s] of %u bytes", PHYSFS_getWriteDir(), file, size);
			}
				
			ret = written;
		}

		if (PHYSFS_close(fs_file) == 0)
		{
			LOG("File System error while closing file %s: %s", file, PHYSFS_getLastError());
		}
			
	}
	else
	{
		LOG("File System error while opening file %s: %s", file, PHYSFS_getLastError());
	}
		
	return ret;
}

bool ModuleFileSystem::Remove(const char* file)
{
	bool ret = false;

	if (file != nullptr)
	{
		if (PHYSFS_delete(file) == 0)
		{
			LOG("File deleted: [%s]", file);
			ret = true;
		}
		else
			LOG("File System error while trying to delete [%s]: ", file, PHYSFS_getLastError());
	}

	return ret;
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

void ModuleFileSystem::SaveMeshInto_WAF(MeshInfo* Mesh)
{

	//Generate Random Value
	int NewId = App->GiveRandomNum_Undefined();

	uint ranges[2] = { Mesh->num_index,Mesh->num_vertex };

	uint size = sizeof(ranges) + sizeof(uint) * Mesh->num_index + sizeof(float) * Mesh->num_vertex * 3;

	char* buffer = new char[size];

	char* cursor = buffer;

	uint bytes = sizeof(ranges);

	memcpy(cursor, ranges, bytes);

	cursor += bytes;

	std::string NewId_C=std::to_string(NewId);
	std::string Extension = ".waf";
	std::string GeneralPath = "Library/Meshes/";

	std::string FinalPath = GeneralPath + NewId_C+Extension;


     PHYSFS_File* WFile = PHYSFS_openWrite(FinalPath.c_str());


	PHYSFS_sint64 AmountWritten= PHYSFS_write(WFile, (const void*)buffer, 1, size);


	PHYSFS_close(WFile);

	

	
	//KEEP THIS ORDER OF OPERATIONS!!

	PHYSFS_File* RFile = PHYSFS_openRead(FinalPath.c_str());

	PHYSFS_sint32 Rsize = (PHYSFS_sint32)PHYSFS_fileLength(RFile);

	char* Rbuffer = new char[Rsize];

	char* Rcursor = Rbuffer;

	PHYSFS_sint64 AmountRead = PHYSFS_read(RFile, Rbuffer, 1, Rsize);


	
	uint Rranges[2];

	uint Rbytes = sizeof(Rranges);

	memcpy(Rranges, Rcursor, Rbytes);

	Rcursor += Rbytes;

	uint NumIndex = Rranges[0];
	uint NumVertex = Rranges[1];



}
