#pragma once
#ifndef __ModuleFileMana_H__
#define __ModuleFileMana_H__
#include "Module.h"
#include "Globals.h"
#include <iomanip>
#include <fstream>

struct aiScene;
struct aiNode;
struct Vertex_Sub;
struct LoadedFile_Mesh_Faces {

	uint AmountIndex;
	std::vector<uint> Index;


};
struct LoadedFile_Mesh {

	
	uint AmountVertex;
	/*std::vector<float> VertexX;
	std::vector<float> VertexY;
	std::vector<float> VertexZ;*/
	std::vector<Vertex_Sub> Vertex;
	uint AmountFaces;
	std::vector<LoadedFile_Mesh_Faces> FaceInfo;

	std::vector<Vertex_Sub> TextureCoords;

};


struct LoadedFile {

	int File_Id;
	std::string FileType;
	uint AmountMeshes;
	std::vector<LoadedFile_Mesh> MeshInfo;
	
};


struct StoredFile {

	const aiScene* Scene;
	
	
	//////

	int File_Id;
	std::string FileType;
	uint AmountMeshes;

	//std::vector<StoredFile_Mesh> MeshInfo;


	bool is_EmptyParent = false;
	int unique_id = 0;
	std::string TypeOfItem = "";

};




struct FileSystemPaths {



};

class ModuleFileSystem : public Module
{
public:

	ModuleFileSystem(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleFileSystem();

	int CheckExistence_Mesh(StoredFile Information);
	bool GenerateLibraryFile(int id);

	void GenerateLibraryFile_Mesh(int id,  StoredFile Information);
	StoredFile LoadLibraryFile_Mesh(int id);

	bool Start();
	
	std::vector<StoredFile> StoredFilesListed;
	update_status Update(float dt);
	
	void TestingReadErrors(const char* filename,StoredFile File);
	

	void SaveInformationFile_Mesh(int id,StoredFile FileToSave);
	LoadedFile* LoadInformationFile_Mesh();


	std::vector<LoadedFile> LoadedResources;
	

	bool CleanUp();

public:
	
	std::vector<std::string>ConvertedVec;
	void ToBinary_String(std::string stringname);
	void ToBinary_Number(int val );

	


private:
	

public:

	//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
};

#endif

//#ifndef __ModuleFileMana_H__
//#define __ModuleFileMana_H__
//#include "Module.h"
//#include "Globals.h"
//#include <iomanip>
//#include <fstream>

//class Configuration;
//struct PathNode;
//
//enum class PHYSFS_RESULT																	// Every PhysFS method that returns 1 or 0 upon success/failure will be cast to this type.
//{
//	FAILURE,
//	SUCCESS
//};
//
//class ModuleFileSystem : public Module
//{
//public:
//	ModuleFileSystem(bool is_active = true);
//	~ModuleFileSystem();
//
//	bool Init(Configuration& config) override;
//	bool CleanUp() override;
//
//	bool SaveConfiguration(Configuration& root) const override;								// Necessary?
//	bool LoadConfiguration(Configuration& root) override;									// ----------
//
//public:
//	// Utility functions
//	bool AddPath(const char* path_or_zip);													// Will add a new zip file or folder. Whichever it is, it will be used by PhysFS.
//	bool Exists(const char* file) const;													// Will check whether or not a file exists in the PHYSFS search path.
//
//	void CreateLibraryDirectories();														// Will call CreateDir() to create all the required directories in the same method.
//	bool CreateDir(const char* directory);													// Will create a directory. This directory will be used by PhysFS.
//	bool IsDirectory(const char* file) const;												// Will check whether or not the given directory is a PhysFS directory already (See above).
//	const char* GetBaseDirectory() const;
//	const char* GetWriteDirectory() const;													// Will return a path where PhysFS will allow file writing. Gets the current write directory.
//	const char* GetReadDirectories() const;
//	void GetRealDirectory(const char* path, std::string& output) const;						// Will return the real directory path of the given path as the output.
//	std::string GetPathRelativeToAssets(const char* original_path) const;					// Will get the path relative to the assets from the given path.
//
//	void DiscoverFiles(const char* directory, std::vector<std::string>& file_list, std::vector<std::string>& dir_list) const;	// Will return two lists with every file in a given directory.
//	void GetAllFilesWithExtension(const char* directory, const char* extension, std::vector<std::string>& file_list) const;		// Will return a list with all files with the given extension.
//	PathNode GetAllFiles(const char* directory, std::vector<std::string>* filter_ext = nullptr, std::vector<std::string>* ignore_ext = nullptr) const;
//
//	bool HasExtension(const char* path) const;												// Will check whether or not the given path has any extension in it.
//	bool HasExtension(const char* path, std::string extension) const;						// Will check whether or not the given path has the given extension in it.
//	bool HasExtension(const char* path, std::vector<std::string> extensions) const;			// Will check whether or not the given path has any of the extensions given in the list in it.
//
//	std::string NormalizePath(const char* full_path) const;									// Normalizes the dashes in the given path from '\\' to '/'.
//	void SplitFilePath(const char* full_path, std::string* path, std::string* file = nullptr, std::string* extension = nullptr) const;	// Will "return" 3 separate strs: path, file & ext.
//
//	// Open for Read/Write
//	uint Load(const char* path, const char* file, char** buffer) const;						// Adds the file string to the path string and calls the below Load method.
//	uint Load(const char* file, char** buffer) const;										// Will open the given file for reading and will store the read data in the given buffer.
//
//	uint Save(const char* file, const void* buffer, uint size, bool append = false) const;	// Will open the given file for writing and will write in it the data stored in the given buffer.
//
//	bool DuplicateFile(const char* file, const char* destination_folder, std::string& relative_path);	// Will get the dst file string to which duplicate the file and call the method below.
//	bool DuplicateFile(const char* source_file, const char* destination_file);							// Reads all the data inside the source file and writes it in the destination file.
//
//	bool Remove(const char* file);															// Deletes the given file. If it is a directory all files inside it are deleted before it.
//
//	uint64 GetLastModTime(const char* filename) const;										// Returns the last time that the given file was modified.
//	std::string GetUniqueName(const char* path, const char* name) const;					// Gets a unique name for a file with the same base name as other files in the same directory.
//	std::string GetFileExtension(const char* path);
//};
//
//#endif // !__M_FILE_SYSTEM_H__