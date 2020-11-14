#include "Globals.h"
#include "Application.h"
#include "FileSystem.h"
#include "libraries/Assimp/Assimp/include/cimport.h"
#include "libraries/Assimp/Assimp/include/scene.h"
#include "libraries/Assimp/Assimp/include/postprocess.h"
#pragma comment (lib, "libraries/Assimp/Assimp/libx86/assimp.lib")
#include <fstream>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;



ModuleFileSystem::ModuleFileSystem(Application* app, const char* name, bool start_enabled) : Module(app, "SaveLoad", start_enabled)
{
	// WE ARE FINE FORMAT: THE FUTURE, TODAY
}

ModuleFileSystem::~ModuleFileSystem()
{
	

}

int ModuleFileSystem::CheckExistence_Mesh(StoredFile Information)
{
	//CHECKS IF THE FILE IS ALREADY STORED IN THE LIBARY

	// Returns 0 if it doesnt exist
	// FALSE IF ITS NOT
	int unique_id;
	int RetUnique_id;
	if (StoredFilesListed.size() != 0) {

		std::vector<StoredFile>::iterator IteratorFile = StoredFilesListed.begin();
		for (int pos = 0; pos < StoredFilesListed.size(); ++pos) {

			StoredFile File = *IteratorFile;
			unique_id = File.unique_id;
			if (File.TypeOfItem == "mesh") {

				if (File.Scene->mNumMeshes != Information.Scene->mNumMeshes) {

					for (int item = 0; item < Information.Scene->mNumMeshes; ++item) {

						aiMesh* MeshToCheck = Information.Scene->mMeshes[item];

						aiMesh* MeshInList = File.Scene->mMeshes[item];

						if (MeshInList->mNumVertices != MeshToCheck->mNumVertices) {

							if (MeshInList->mNumFaces != MeshToCheck->mNumFaces) {

								if (MeshInList->mVertices != MeshToCheck->mVertices) {

									if (MeshInList->mFaces != MeshToCheck->mFaces) {

										if (MeshInList->mTextureCoords != MeshToCheck->mTextureCoords) {

										}
										else {

											item = Information.Scene->mNumMeshes;
											pos = StoredFilesListed.size();
											return unique_id;
										}
									}
									else {

										item = Information.Scene->mNumMeshes;
										pos = StoredFilesListed.size();
										return unique_id;
									}
								}
								else {

									item = Information.Scene->mNumMeshes;
									pos = StoredFilesListed.size();
									return unique_id;
								}
							}
							else {

								item = Information.Scene->mNumMeshes;
								pos = StoredFilesListed.size();
								return unique_id;
							}
						}
						else {

							item = Information.Scene->mNumMeshes;
							pos = StoredFilesListed.size();
							return unique_id;
						}
					}
				}
				else {

					pos = StoredFilesListed.size();
					return unique_id;
				}
			}
			++IteratorFile;
		}
	}
	else {
		FILE* fptr2;
		StoredFile ToCheckInfo2;
		int a;
		std::string type;
		if ((fptr2 = fopen("Assets/Library/22597.waf", "rb")) == NULL) {

		}
		else {
			//fread(&ToCheckInfo2, sizeof(StoredFile), sizeof(StoredFile), fptr2);

			//fread(&a, sizeof(int), sizeof(int), fptr2);
			//fread(&type, sizeof(std::string), sizeof(std::string), fptr2);

			//fread(&Information.Scene, sizeof(const aiScene*), sizeof(const aiScene*), fptr2);

			//fread(&Information.Scene, sizeof(const aiScene*), sizeof(const aiScene*), fptr2);
		}
		
		std::string path = "Assets/Library/";
		for (const auto& entry : fs::directory_iterator(path)) {

			StoredFile ToCheckInfo;
			
			//Existing File
			std::string PathName = entry.path().string();
			const char* PathName_C = PathName.c_str();

			//Generating File
			//std::string Id_C = std::to_string(RetUnique_id);
			std::string Direction = "Assets/Library/";
			
			std::string FinalPath =  PathName;
			const char* FinalPath_C = FinalPath.c_str();

			//TestingReadErrors(FinalPath_C, Information); 
			
			if ((fptr2 = fopen(FinalPath_C, "rb")) == NULL) {

			}
			else {

				fread(&ToCheckInfo, sizeof(StoredFile), sizeof(StoredFile), fptr2);


				
				RetUnique_id = ToCheckInfo.unique_id;

				if (ToCheckInfo.Scene->mNumMeshes != Information.Scene->mNumMeshes) {

					for (int item = 0; item < Information.Scene->mNumMeshes; ++item) {

						aiMesh* MeshToCheck = Information.Scene->mMeshes[item];

						aiMesh* MeshInList = ToCheckInfo.Scene->mMeshes[item];

						if (MeshInList->mNumVertices != MeshToCheck->mNumVertices) {

							if (MeshInList->mNumFaces != MeshToCheck->mNumFaces) {

								if (MeshInList->mVertices != MeshToCheck->mVertices) {

									if (MeshInList->mFaces != MeshToCheck->mFaces) {

										if (MeshInList->mTextureCoords != MeshToCheck->mTextureCoords) {

										}
										else {

											item = Information.Scene->mNumMeshes;
											
											return RetUnique_id;
										}
									}
									else {

										item = Information.Scene->mNumMeshes;
										
										return RetUnique_id;
									}
								}
								else {

									item = Information.Scene->mNumMeshes;
									
									return RetUnique_id;
								}
							}
							else {

								item = Information.Scene->mNumMeshes;
								
								return RetUnique_id;
							}
						}
						else {

							item = Information.Scene->mNumMeshes;
							
							return RetUnique_id;
						}
					}
				}
				else {

					return RetUnique_id;
				}
			}

			fclose(fptr2);
		}
	}
	
	return 0;
}

bool ModuleFileSystem::GenerateLibraryFile(int id)
{
	FILE* fptr;

    
	std::string Direction = "Assets/Library/";
	std::string Extension = ".waf";



	const char* idconversion_C;
	
	
	std::string idconversion = std::to_string(id);

	

	std::string FinalPath = Direction + idconversion + Extension;
	const char* FinalPath_C = FinalPath.c_str();

	//std::fstream OurFile;
	//
	//OurFile.open(FinalPath_C, std::fstream::out|std::fstream::binary);
	////OurFile << id;
	//std::string textstr = std::to_string(id);
	//const char* text; 
	//
	////ToBinary_String("aaaa");
	//
	//
	////std::vector<std::string>::iterator  IteratorVec = ConvertedVec.begin();

	///*for (int a = 0; a < ConvertedVec.size(); ++a) {
	//	std::string word = *IteratorVec;

	//	const char* word_C = word.c_str();
	//	OurFile.write(word_C, sizeof(word_C));

	//	++IteratorVec;
	//}*/

	//OurFile.write(FinalPath_C, FinalPath.length());
	//
	//OurFile.close();

	
	struct threeNum
	{
		int n1, n2, n3;
	};

	int n;
	int abc = 20000;
	
	int id_index = 3; // index in VRAM
	int num_index = 9765; // amount of indexes in a mesh
	
	int id_vertex = 67; // unique vertex in VRAM
	int num_vertex = 1034; // amount of vertex in a mesh
	

	
	int num_texcoords = 39; // amount of coordinates of the texture in the mesh
	int texcoords_id = 165; // id of the coordinate of the texture in the mesh

	const char* TextureName = "Mesh Object A"; // name of the current texture aplied to the mesh

	
	int id_normals = 9; // id of the normals in the mesh


	struct threeNum num;
	const char* Name = "Square";
	const char* NameRet;


	if ((fptr = fopen(FinalPath_C, "wb")) == NULL) {
		
	}
	else {
		fwrite(&id_index, sizeof(int), 1, fptr);
		fwrite(&num_index, sizeof(int), 1, fptr);
		fwrite(&id_vertex, sizeof(int), 1, fptr);
		fwrite(&num_vertex, sizeof(int), 1, fptr);
fwrite(&num_texcoords, sizeof(int), 1, fptr);
fwrite(&texcoords_id, sizeof(int), 1, fptr);
fwrite(&TextureName, sizeof(const char*), 1, fptr);
fwrite(&id_normals, sizeof(int), 1, fptr);


	}

	fclose(fptr);



	int id_index2;
	int num_index2; // amount of indexes in a mesh

	int id_vertex2;// unique vertex in VRAM
	int num_vertex2; // amount of vertex in a mesh



	int num_texcoords2; // amount of coordinates of the texture in the mesh
	int texcoords_id2; // id of the coordinate of the texture in the mesh

	const char* TextureName2; // name of the current texture aplied to the mesh


	int id_normals2; // id of the normals in the mesh

	if ((fptr = fopen(FinalPath_C, "rb")) == NULL) {

	}
	else {


		fread(&id_index2, sizeof(int), 1, fptr);
		fread(&num_index2, sizeof(int), 1, fptr);
		fread(&id_vertex2, sizeof(int), 1, fptr);
		fread(&num_vertex2, sizeof(int), 1, fptr);
		fread(&num_texcoords2, sizeof(int), 1, fptr);
		fread(&texcoords_id2, sizeof(int), 1, fptr);
		fread(&TextureName2, sizeof(const char*), 1, fptr);
		fread(&id_normals2, sizeof(int), 1, fptr);



	}


	fclose(fptr);


	return true;
}

void ModuleFileSystem::GenerateLibraryFile_Mesh(int id, StoredFile Information)
{
	

	//Generating the Name/Path of the file
	std::string Direction = "Assets/Library/";
	std::string Extension = ".waf";
	std::string idconversion = std::to_string(id);
	std::string FinalPath = Direction + idconversion + Extension;
	const char* FinalPath_C = FinalPath.c_str();
	Information.unique_id = id;
	Information.TypeOfItem = "We are Fine";
	


	FILE* FileW;
	if ((FileW = fopen(FinalPath_C, "wb")) == NULL) {

	}
	else {
		
	}

	fclose(FileW);

	

	

	
	
	
	
	

	StoredFilesListed.push_back(Information);


	

	
}

StoredFile ModuleFileSystem::LoadLibraryFile_Mesh(int id)
{
	StoredFile FileToReturn;
	FILE* fptr;
	std::string Direction = "Assets/Library/";
	std::string Extension = ".waf";
	std::string idconversion = std::to_string(id);
	std::string FinalPath = Direction + idconversion + Extension;
	const char* FinalPath_C = FinalPath.c_str();

	

	if ((fptr = fopen(FinalPath_C, "rb")) == NULL) {

	}
	else {


		fread(&FileToReturn, sizeof(StoredFile), 1, fptr);

	}

	fclose(fptr);

	return FileToReturn;
}

bool ModuleFileSystem::Start()
{
	

	return true;
}

update_status ModuleFileSystem::Update(float dt)
{
	
	return UPDATE_CONTINUE;
}

void ModuleFileSystem::TestingReadErrors(const char* filename, StoredFile FileToSave)
{
	FILE* FileR;


	
}

void ModuleFileSystem::SaveInformationFile_Mesh(int id, StoredFile FileToStore)
{

	//Generating the Name/Path of the file
	std::string Direction = "Assets/Library/";
	std::string Extension = ".waf";
	std::string idconversion = std::to_string(id);
	std::string FinalPath = Direction + idconversion + Extension;
	const char* FinalPath_C = FinalPath.c_str();
	FileToStore.unique_id = id;
	FileToStore.TypeOfItem = "We are Fine";

	FILE* FileW;
	




	
	uint a=sizeof(*FileToStore.Scene->mMeshes[0]->mVertices);
	if ((FileW = fopen(FinalPath_C, "wb")) == NULL) {

	}
	else {
		
		

		
		

	}

	fclose(FileW);




}

StoredFile ModuleFileSystem::LoadInformationFile_Mesh()
{
	StoredFile FileToLoad;
	StoredFile* FileToLoadR = new StoredFile();
	std::string Direction = "Assets/Library/";
	std::string Extension = ".waf";
	std::string idconversion = std::to_string(22597);
	std::string FinalPath = Direction + idconversion + Extension;
	const char* FinalPath_C = FinalPath.c_str();
	
	aiVector3D* Vec2;
	uint size;

	FILE* FileR;
	if ((FileR = fopen(FinalPath_C, "rb")) == NULL) {

	}
	else {


		fread(&Vec2, 12, 1, FileR);
	}

	

	fclose(FileR);

	return FileToLoad;
}




bool ModuleFileSystem::CleanUp()
{
	return true;
}

void ModuleFileSystem::ToBinary_String(std::string stringname)
{
	
	ConvertedVec.clear();
	int n = stringname.length();
	
	std::string item = "";
	for (int i = 0; i <= n; i++)
	{
		// convert each char to 
		// ASCII value 
		int val = int(stringname[i]);

		// Convert ASCII value to binary 
		
		while (val > 0)
		{
			(val % 2) ? item.push_back('1') :
				item.push_back('0');
			val /= 2;
		}
		
		reverse(item.begin(), item.end());
		


		LOGFIX(item.c_str());

		ConvertedVec.push_back(item);
		

	}
	
}

void ModuleFileSystem::CreateConsolelog(const char file[], int line, const char* format, ...)
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



//#include "Globals.h"
//#include "Engine.h"
//#include "M_FileSystem.h"
//#include "PathNode.h"
//
//#include "PhysFS/include/physfs.h"
//#include <fstream>
//#include <filesystem>
//
//#include "Assimp/include/cfileio.h"
//#include "Assimp/include/types.h"
//
//#pragma comment( lib, "PhysFS/libx86/physfs.lib" )
//
//M_FileSystem::M_FileSystem(bool start_enabled) : Module("FileSystem", true)
//{
//	// needs to be created before Init so other modules can use it
//	char* base_path = SDL_GetBasePath();
//	PHYSFS_init(nullptr);
//	SDL_free(base_path);
//
//	//Setting the working directory as the writing directory
//	if (PHYSFS_setWriteDir(".") == 0)
//		LOG("File System error while creating write dir: %s\n", PHYSFS_getLastError());
//
//	AddPath("."); //Adding ProjectFolder (working directory)
//	AddPath("Assets");
//	CreateLibraryDirectories();
//}
//
//// Destructor
//M_FileSystem::~M_FileSystem()
//{
//	PHYSFS_deinit();
//}
//
//// Called before render is available
//bool M_FileSystem::Init(Config& config)
//{
//	LOG("Loading File System");
//	bool ret = true;
//
//	// Ask SDL for a write dir
//	char* write_path = SDL_GetPrefPath(Engine->GetOrganizationName(), Engine->GetTitleName());
//
//	// Trun this on while in game mode
//	//if(PHYSFS_setWriteDir(write_path) == 0)
//	//	LOG("File System error while creating write dir: %s\n", PHYSFS_getLastError());
//
//	SDL_free(write_path);
//
//	return ret;
//}
//
//// Called before quitting
//bool M_FileSystem::CleanUp()
//{
//	//LOG("Freeing File System subsystem");
//
//	return true;
//}
//
//void M_FileSystem::CreateLibraryDirectories()
//{
//	CreateDir(LIBRARY_PATH);
//	CreateDir(FOLDERS_PATH);
//	CreateDir(MESHES_PATH);
//	CreateDir(TEXTURES_PATH);
//	CreateDir(MATERIALS_PATH);
//	CreateDir(MODELS_PATH);
//	CreateDir(ANIMATIONS_PATH);
//	CreateDir(PARTICLES_PATH);
//	CreateDir(SHADERS_PATH);
//	CreateDir(SCENES_PATH);
//}
//
//// Add a new zip file or folder
//bool M_FileSystem::AddPath(const char* path_or_zip)
//{
//	bool ret = false;
//
//	if (PHYSFS_mount(path_or_zip, nullptr, 1) == 0)
//	{
//		LOG("File System error while adding a path or zip: %s\n", PHYSFS_getLastError());
//	}
//	else
//		ret = true;
//
//	return ret;
//}
//
//// Check if a file exists
//bool M_FileSystem::Exists(const char* file) const
//{
//	return PHYSFS_exists(file) != 0;
//}
//
//bool M_FileSystem::CreateDir(const char* dir)
//{
//	if (IsDirectory(dir) == false)
//	{
//		PHYSFS_mkdir(dir);
//		return true;
//	}
//	return false;
//}
//
//// Check if a file is a directory
//bool M_FileSystem::IsDirectory(const char* file) const
//{
//	return PHYSFS_isDirectory(file) != 0;
//}
//
//const char * M_FileSystem::GetWriteDir() const
//{
//	//TODO: erase first annoying dot (".")
//	return PHYSFS_getWriteDir();
//}
//
//void M_FileSystem::DiscoverFiles(const char* directory, std::vector<std::string> & file_list, std::vector<std::string> & dir_list) const
//{
//	char **rc = PHYSFS_enumerateFiles(directory);
//	char **i;
//
//	for (i = rc; *i != nullptr; i++)
//	{
//		std::string str = std::string(directory) + std::string("/") + std::string(*i);
//		if (IsDirectory(str.c_str()))
//			dir_list.push_back(*i);
//		else
//			file_list.push_back(*i);
//	}
//
//	PHYSFS_freeList(rc);
//}
//
//void M_FileSystem::GetAllFilesWithExtension(const char* directory, const char* extension, std::vector<std::string>& file_list) const
//{
//	std::vector<std::string> files;
//	std::vector<std::string> dirs;
//	DiscoverFiles(directory, files, dirs);
//
//	for (uint i = 0; i < files.size(); i++)
//	{
//		std::string ext;
//		SplitFilePath(files[i].c_str(), nullptr, nullptr, &ext);
//
//		if (ext == extension)
//			file_list.push_back(files[i]);
//	}
//}
//
//PathNode M_FileSystem::GetAllFiles(const char* directory, std::vector<std::string>* filter_ext, std::vector<std::string>* ignore_ext) const
//{
//	PathNode root;
//	if (Exists(directory))
//	{
//		root.path = directory;
//		Engine->fileSystem->SplitFilePath(directory, nullptr, &root.localPath);
//		if (root.localPath == "")
//			root.localPath = directory;
//
//		std::vector<std::string> file_list, dir_list;
//		DiscoverFiles(directory, file_list, dir_list);	
//		
//		//Adding all child directories
//		for (uint i = 0; i < dir_list.size(); i++)
//		{
//			std::string str = directory;
//			str.append("/").append(dir_list[i]);
//			root.children.push_back(GetAllFiles(str.c_str(), filter_ext, ignore_ext));
//		}
//		//Adding all child files
//		for (uint i = 0; i < file_list.size(); i++)
//		{
//			//Filtering extensions
//			bool filter = true, discard = false;
//			if (filter_ext != nullptr)
//			{
//				filter = HasExtension(file_list[i].c_str(), *filter_ext);
//			}
//			if (ignore_ext != nullptr)
//			{
//				discard = HasExtension(file_list[i].c_str(), *ignore_ext);
//			}
//			if (filter == true && discard == false)
//			{
//				std::string str = directory;
//				str.append("/").append(file_list[i]);
//				root.children.push_back(GetAllFiles(str.c_str(), filter_ext, ignore_ext));
//			}
//		}
//		root.isFile = HasExtension(root.path.c_str());
//		root.isLeaf = root.children.empty() == true;
//	}
//	return root;
//}
//
//void M_FileSystem::GetRealDir(const char* path, std::string& output) const
//{
//	output = PHYSFS_getBaseDir();
//
//	std::string baseDir = PHYSFS_getBaseDir();
//	std::string searchPath = *PHYSFS_getSearchPath();
//	std::string realDir = PHYSFS_getRealDir(path);
//
//	output.append(*PHYSFS_getSearchPath()).append("/");
//	output.append(PHYSFS_getRealDir(path)).append("/").append(path);
//}
//
//std::string M_FileSystem::GetPathRelativeToAssets(const char* originalPath) const
//{
//	std::string ret;
//	GetRealDir(originalPath, ret);
//
//	return ret;
//}
//
//bool M_FileSystem::HasExtension(const char* path) const
//{
//	std::string ext = "";
//	SplitFilePath(path, nullptr, nullptr, &ext);
//	return ext != "";
//}
//
//bool M_FileSystem::HasExtension(const char* path, std::string extension) const
//{
//	std::string ext = "";
//	SplitFilePath(path, nullptr, nullptr, &ext);
//	return ext == extension;
//}
//
//bool M_FileSystem::HasExtension(const char* path, std::vector<std::string> extensions) const
//{
//	std::string ext = "";
//	SplitFilePath(path, nullptr, nullptr, &ext);
//	if (ext == "")
//		return true;
//	for (uint i = 0; i < extensions.size(); i++)
//	{
//		if (extensions[i] == ext)
//			return true;
//	}
//	return false;
//}
//
//std::string M_FileSystem::NormalizePath(const char * full_path) const
//{
//	std::string newPath(full_path);
//	for (int i = 0; i < newPath.size(); ++i)
//	{
//		if (newPath[i] == '\\')
//			newPath[i] = '/';
//	}
//	return newPath;
//}
//
//void M_FileSystem::SplitFilePath(const char * full_path, std::string * path, std::string * file, std::string * extension) const
//{
//	if (full_path != nullptr)
//	{
//		std::string full(full_path);
//		size_t pos_separator = full.find_last_of("\\/");
//		size_t pos_dot = full.find_last_of(".");
//
//		if (path != nullptr)
//		{
//			if (pos_separator < full.length())
//				*path = full.substr(0, pos_separator + 1);
//			else
//				path->clear();
//		}
//
//		if (file != nullptr)
//		{
//			if (pos_separator < full.length())
//				*file = full.substr(pos_separator + 1, pos_dot - pos_separator - 1);
//			else
//				*file = full.substr(0, pos_dot);
//		}
//
//		if (extension != nullptr)
//		{
//			if (pos_dot < full.length())
//				*extension = full.substr(pos_dot + 1);
//			else
//				extension->clear();
//		}
//	}
//}
//
//unsigned int M_FileSystem::Load(const char * path, const char * file, char ** buffer) const
//{
//	std::string full_path(path);
//	full_path += file;
//	return Load(full_path.c_str(), buffer);
//}
//
//// Read a whole file and put it in a new buffer
//uint M_FileSystem::Load(const char* file, char** buffer) const
//{
//	uint ret = 0;
//
//	PHYSFS_file* fs_file = PHYSFS_openRead(file);
//
//	if (fs_file != nullptr)
//	{
//		PHYSFS_sint32 size = (PHYSFS_sint32)PHYSFS_fileLength(fs_file);
//
//		if (size > 0)
//		{
//			*buffer = new char[size+1];
//			uint readed = (uint)PHYSFS_read(fs_file, *buffer, 1, size);
//			if (readed != size)
//			{
//				LOG("File System error while reading from file %s: %s\n", file, PHYSFS_getLastError());
//				RELEASE_ARRAY(buffer);
//			}
//			else
//			{
//				ret = readed;
//				//Adding end of file at the end of the buffer. Loading a shader file does not add this for some reason
//				(*buffer)[size] = '\0';
//			}
//		}
//
//		if (PHYSFS_close(fs_file) == 0)
//			LOG("File System error while closing file %s: %s\n", file, PHYSFS_getLastError());
//	}
//	else
//		LOG("File System error while opening file %s: %s\n", file, PHYSFS_getLastError());
//
//	return ret;
//}
//
//bool M_FileSystem::DuplicateFile(const char* file, const char* dstFolder, std::string& relativePath)
//{
//	std::string fileStr, extensionStr;
//	SplitFilePath(file, nullptr, &fileStr, &extensionStr);
//
//	relativePath = relativePath.append(dstFolder).append("/") + fileStr.append(".") + extensionStr;
//	std::string finalPath = std::string(*PHYSFS_getSearchPath()).append("/") + relativePath;
//
//	return DuplicateFile(file, finalPath.c_str());
//
//}
//
//bool M_FileSystem::DuplicateFile(const char* srcFile, const char* dstFile)
//{
//	//TODO: Compare performance to calling Load(srcFile) and then Save(dstFile)
//	std::ifstream src;
//	src.open(srcFile, std::ios::binary);
//	bool srcOpen = src.is_open();
//	std::ofstream  dst(dstFile, std::ios::binary);
//	bool dstOpen = dst.is_open();
//
//	dst << src.rdbuf();
//
//	src.close();
//	dst.close();
//
//	if (srcOpen && dstOpen)
//	{
//		LOG("[success] File Duplicated Correctly");
//		return true;
//	}
//	else
//	{
//		LOG("[error] File could not be duplicated");
//		return false;
//	}
//}
//
//int close_sdl_rwops(SDL_RWops *rw)
//{
//	RELEASE_ARRAY(rw->hidden.mem.base);
//	SDL_FreeRW(rw);
//	return 0;
//}
//
//// Save a whole buffer to disk
//uint M_FileSystem::Save(const char* file, const void* buffer, unsigned int size, bool append) const
//{
//	unsigned int ret = 0;
//
//	bool overwrite = PHYSFS_exists(file) != 0;
//	PHYSFS_file* fs_file = (append) ? PHYSFS_openAppend(file) : PHYSFS_openWrite(file);
//
//	if (fs_file != nullptr)
//	{
//		uint written = (uint)PHYSFS_write(fs_file, (const void*)buffer, 1, size);
//		if (written != size)
//		{
//			LOG("[error] File System error while writing to file %s: %s", file, PHYSFS_getLastError());
//		}
//		else
//		{
//			if (append == true)
//				LOG("Added %u data to [%s%s]", size, GetWriteDir(), file);
//			else if (overwrite == true)
//				LOG("File [%s%s] overwritten with %u bytes", GetWriteDir(), file, size);
//			else
//				LOG("New file created [%s%s] of %u bytes", GetWriteDir(), file, size);
//
//			ret = written;
//		}
//
//		if (PHYSFS_close(fs_file) == 0)
//			LOG("[error] File System error while closing file %s: %s", file, PHYSFS_getLastError());
//	}
//	else
//		LOG("[error] File System error while opening file %s: %s", file, PHYSFS_getLastError());
//
//	return ret;
//}
//
//bool M_FileSystem::Remove(const char * file)
//{
//	bool ret = false;
//
//	if (file != nullptr)
//	{
//		//If it is a directory, we need to recursively remove all the files inside
//		if (IsDirectory(file))
//		{
//			std::vector<std::string> containedFiles, containedDirs;
//			PathNode rootDirectory = GetAllFiles(file);
//			
//			for (uint i = 0; i < rootDirectory.children.size(); ++i)
//				Remove(rootDirectory.children[i].path.c_str());
//		}
//		
//		if (PHYSFS_delete(file) != 0)
//		{
//			LOG("File deleted: [%s]", file);
//			ret = true;
//		}
//		else
//			LOG("File System error while trying to delete [%s]: %s", file, PHYSFS_getLastError());
//	}
//
//	return ret;
//}
//
//uint64 M_FileSystem::GetLastModTime(const char* filename)
//{
//	return PHYSFS_getLastModTime(filename);
//}
//
//std::string M_FileSystem::GetUniqueName(const char* path, const char* name) const
//{
//	//TODO: modify to distinguix files and dirs?
//	std::vector<std::string> files, dirs;
//	DiscoverFiles(path, files, dirs);
//
//	std::string finalName(name);
//	bool unique = false;
//
//	for (uint i = 0; i < 50 && unique == false; ++i)
//	{
//		unique = true;
//
//		//Build the compare name (name_i)
//		if (i > 0)
//		{
//			finalName = std::string(name).append("_");
//			if (i < 10)
//				finalName.append("0");
//			finalName.append(std::to_string(i));
//		}
//
//		//Iterate through all the files to find a matching name
//		for (uint f = 0; f < files.size(); ++f)
//		{
//			if (finalName == files[f])
//			{
//				unique = false;
//				break;
//			}
//		}
//	}
//	return finalName;
//}