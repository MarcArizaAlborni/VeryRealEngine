#include "Globals.h"
#include "Application.h"
#include "FileSystem.h"
#include "ModuleMeshImporter.h"
#include "ModuleEditor.h"
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
	FileToStore.TypeOfItem = "Mesh";

	std::string TypeOfFile = "Mesh";

	FILE* FileW;

	
	
	if ((FileW = fopen(FinalPath_C, "wb")) == NULL) {

	}
	else {

		fwrite(&id, sizeof(int), 1, FileW); // 1
		fwrite(&TypeOfFile, sizeof(std::string), 1, FileW);//2
		
		uint WnumMeshes = FileToStore.Scene->mNumMeshes;
		fwrite(&WnumMeshes, sizeof(uint), 1, FileW); // 3
		
		for (int mMeshesSize = 0; mMeshesSize < WnumMeshes; ++mMeshesSize) {
		
			uint WnumVertices = FileToStore.Scene->mMeshes[mMeshesSize]->mNumVertices;

			fwrite(&WnumVertices, sizeof(uint), 1, FileW); // 4
	
			for (int mVerticesSize = 0; mVerticesSize < WnumVertices; ++mVerticesSize) {

				float WVerticesX = FileToStore.Scene->mMeshes[mMeshesSize]->mVertices[mVerticesSize].x;
				float WVerticesY = FileToStore.Scene->mMeshes[mMeshesSize]->mVertices[mVerticesSize].y;
				float WVerticesZ = FileToStore.Scene->mMeshes[mMeshesSize]->mVertices[mVerticesSize].z;

				fwrite(&WVerticesX, sizeof(float), 1, FileW);  //5
				fwrite(&WVerticesY, sizeof(float), 1, FileW);  //6
				fwrite(&WVerticesZ, sizeof(float), 1, FileW);  //7

				float WVerticesTexX = FileToStore.Scene->mMeshes[mMeshesSize]->mTextureCoords[0][mVerticesSize].x;
				float WVerticesTexY = FileToStore.Scene->mMeshes[mMeshesSize]->mTextureCoords[0][mVerticesSize].y;
				float WVerticesTexZ = FileToStore.Scene->mMeshes[mMeshesSize]->mTextureCoords[0][mVerticesSize].z;

				fwrite(&WVerticesTexX, sizeof(float), 1, FileW);  //5
				fwrite(&WVerticesTexY, sizeof(float), 1, FileW);  //6
				fwrite(&WVerticesTexZ, sizeof(float), 1, FileW);  //7

				float WNormX = FileToStore.Scene->mMeshes[mMeshesSize]->mNormals[mVerticesSize].x;
				float WNormY = FileToStore.Scene->mMeshes[mMeshesSize]->mNormals[mVerticesSize].y;
				float WNormZ = FileToStore.Scene->mMeshes[mMeshesSize]->mNormals[mVerticesSize].z;

				fwrite(&WNormX, sizeof(float), 1, FileW);  //5
				fwrite(&WNormY, sizeof(float), 1, FileW);  //6
				fwrite(&WNormZ, sizeof(float), 1, FileW);  //7

				
			}

			uint WnumFaces = FileToStore.Scene->mMeshes[mMeshesSize]->mNumFaces;

			fwrite(&WnumFaces, sizeof(uint), 1, FileW); // 8

			for (int mFacesSize = 0; mFacesSize < WnumFaces; ++mFacesSize) {

				uint WnumIndex = FileToStore.Scene->mMeshes[mMeshesSize]->mFaces[mFacesSize].mNumIndices;
				fwrite(&WnumIndex, sizeof(uint), 1, FileW); // 9

				/*uint* WIndex = FileToStore.Scene->mMeshes[mMeshesSize]->mFaces[mFacesSize].mIndices;

				uint WindexV = *WIndex; // IT WRITESBUT WHEN READING IT JUST DOESNT WORK

				fwrite(&WindexV, sizeof(uint), 1, FileW);*/

				for (int mIndexSize = 0; mIndexSize < WnumIndex; ++mIndexSize) {

					uint WIndex =FileToStore.Scene->mMeshes[mMeshesSize]->mFaces[mFacesSize].mIndices[mIndexSize];
					fwrite(&WIndex, sizeof(uint), 1, FileW); // 10
				}

			



				
			}
		}

	}

	fclose(FileW);

}

LoadedFile* ModuleFileSystem::LoadInformationFile_Mesh(int id)
{

	LoadedFile* FileToLoad = new LoadedFile();
	std::string Direction = "Assets/Library/";
	std::string Extension = ".waf";
	std::string idconversion;

		idconversion = std::to_string(id);
	
	
	std::string FinalPath = Direction + idconversion + Extension;
	const char* FinalPath_C = FinalPath.c_str();
	
	


	FILE* FileR;
	if ((FileR = fopen(FinalPath_C, "rb")) == NULL) {

	}
	else {
		fread(&FileToLoad->File_Id, sizeof(int), 1, FileR);
		fread(&FileToLoad->FileType, sizeof(std::string), 1, FileR);
		fread(&FileToLoad->AmountMeshes, sizeof(uint), 1, FileR);

		for (int mMeshCount = 0; mMeshCount < FileToLoad->AmountMeshes; ++mMeshCount) {

			LoadedFile_Mesh LoadedMesh;

			fread(&LoadedMesh.AmountVertex, sizeof(uint), 1, FileR);

			for (int mVertexCount = 0; mVertexCount < LoadedMesh.AmountVertex; ++mVertexCount) {

				Vertex_Sub Vertex;

				Vertex_Sub TexCoords;

				Vertex_Sub Normals;
				


				fread(&Vertex.x, sizeof(float), 1, FileR);
				fread(&Vertex.y, sizeof(float), 1, FileR);
				fread(&Vertex.z, sizeof(float), 1, FileR);


				fread(&TexCoords.x, sizeof(float), 1, FileR);
				fread(&TexCoords.y, sizeof(float), 1, FileR);
				fread(&TexCoords.z, sizeof(float), 1, FileR);

				fread(&Normals.x, sizeof(float), 1, FileR);
				fread(&Normals.y, sizeof(float), 1, FileR);
				fread(&Normals.z, sizeof(float), 1, FileR);

				

				LoadedMesh.Vertex.push_back(Vertex);
				LoadedMesh.TextureCoords.push_back(TexCoords);
				LoadedMesh.Normal.push_back(Normals);

			}

			fread(&LoadedMesh.AmountFaces, sizeof(uint), 1, FileR);

			for (int mFaceCount = 0; mFaceCount < LoadedMesh.AmountFaces; ++mFaceCount) {

				LoadedFile_Mesh_Faces LoadedFace;

				fread(&LoadedFace.AmountIndex, sizeof(uint), 1, FileR);

				for (int mIndexCount = 0; mIndexCount < LoadedFace.AmountIndex; ++mIndexCount) {

					uint Index;
					fread(&Index, sizeof(uint), 1, FileR);
					LoadedFace.Index.push_back(Index);
				}

				LoadedMesh.FaceInfo.push_back(LoadedFace);
			}

			FileToLoad->MeshInfo.push_back(LoadedMesh);
		}
		
	}

	FileToLoad;
	

	fclose(FileR);

	LoadedResources.push_back(*FileToLoad);

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


	App->editor->ConsoleLogs.push_back(tmp_string2);
}

