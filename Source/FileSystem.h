#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include "Module.h"
#include <vector>
#include <string>

// Allows you to use pointers to memory instead of files
struct SDL_RWops;
int close_sdl_rwops(SDL_RWops* rwops);

struct aiMesh;
class ModuleFileSystem : public Module
{
public:

	ModuleFileSystem(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleFileSystem();
	bool CleanUp() override;

	bool AddPath(const char* path_or_zip);
	bool Exists(const char* file) const;
	bool CreateDir(const char* dir);
	bool IsDirectory(const char* file) const;
	void CreateDirectory(const char* directory);
	void DiscoverFiles(const char* directory, std::vector<std::string>& file_list, std::vector<std::string>& direction_list) const;
	bool CopyFromOutsideFS(const char* full_path, const char* destination);
	bool Copy(const char* source, const char* destination);
	void SplitFilePath(const char* full_path, std::string* path, std::string* file = nullptr, std::string* extension = nullptr) const;
	std::string NormalizeNodePath(const char* full_path);
	void NormalizePath(std::string& full_path) const;
	bool IsInDirectory(const char* directory, const char* p);
	void CreateLibraryDirectories();
	bool RemovePath(std::string* directory, const char* p);

	// Read/Write
	unsigned int Load(const char* path, const char* file, char** buffer) const;
	unsigned int Load(const char* file, char** buffer) const;
	SDL_RWops* Load(const char* file) const;
	unsigned int Save(const char* file, const void* buffer, unsigned int size, bool append = false) const;
	bool Remove(const char* file);

	std::string GetFileAndExtension(const char* path);

////////////////////////////////////////////////////////////////////
	// Mine

	void SaveMeshInto_WAF(MeshInfo* Mesh,aiMesh* RawMesh);
	
	MeshInfo* LoadMeshFrom_WAF(int FileID);
	uint GenerateSafeBuffer_Mesh(MeshInfo* Mesh);




	//META FILES

	void CreateMesh_META(int id, std::string FilePath);
	std::string CurrentlyDetectedMETA = "";
};

#endif  
