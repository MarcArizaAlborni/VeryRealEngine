#include "Globals.h"
#include "Application.h"
#include "ModuleMeshImporter.h"

#include "libraries/Assimp/Assimp/include/cimport.h"
#include "libraries/Assimp/Assimp/include/scene.h"
#include "libraries/Assimp/Assimp/include/postprocess.h"
#pragma comment (lib, "libraries/Assimp/Assimp/libx86/assimp.lib")

ModuleMeshImporter::ModuleMeshImporter(Application* app, const char* name, bool start_enabled) : Module(app,"Importer", start_enabled)
{

}

ModuleMeshImporter::~ModuleMeshImporter()
{}

// -----------------------------------------------------------------
bool ModuleMeshImporter::Start()
{
	bool ret = true;

	

	return ret;
}

// -----------------------------------------------------------------
bool ModuleMeshImporter::CleanUp()
{
	return true;
}

// -----------------------------------------------------------------
update_status ModuleMeshImporter::Update(float dt)
{
	return UPDATE_CONTINUE;
}

// Load a mesh with index and vertex
MeshInfo* ModuleMeshImporter::LoadMesh(char* file_path)
{
	LOGFIX("Importing Model");
	MeshInfo* ourMesh = new MeshInfo();
	GameObject* ourGameObject = new GameObject();
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes()) {

		int MESH_TOTAL_AMOUNT = scene->mNumMeshes;



		for (int i = 0; i < MESH_TOTAL_AMOUNT; ++i) {

			aiMesh* MeshToLoad = scene->mMeshes[i];

			ourMesh->num_vertex = MeshToLoad->mNumVertices;
			ourMesh->vertex = new float[ourMesh->num_vertex * 3];
			memcpy(ourMesh->vertex, MeshToLoad->mVertices, sizeof(float) * ourMesh->num_vertex * 3);

			/*ourGameObject->MeshData.mesh_values = MeshToLoad;

			if (file_path == "Assets/Models/Primitives/Pyramid.FBX") {
				aiVector3D coords = { 0,0,0 };
				ourGameObject->MeshData.mesh_values->mVertices = 0;
			}*/

			if (MeshToLoad->HasFaces()) {

				ourMesh->num_index = MeshToLoad->mNumFaces * 3;
				ourMesh->index = new uint[ourMesh->num_index];

				for (int c = 0; c < MeshToLoad->mNumFaces; ++c) {

					//IF MESHES HAVE TRIS
					if (MeshToLoad->mFaces[c].mNumIndices == 3) {

						memcpy(&ourMesh->index[c * 3], MeshToLoad->mFaces[c].mIndices, 3 * sizeof(uint));
					}

				}

			}
			//CALLED TO CREATE A VERTEX BUFFER SO WE CAN DRAW MULTIPLE OBJECTS
			App->renderer3D->GenerateVertexBuffer(ourMesh->id_vertex, ourMesh->num_vertex, ourMesh->vertex);


			if (ourMesh->index != nullptr) {
				//siCalled to create an Index Buffer so we can draw multiple objects
				App->renderer3D->GenerateIndexBuffer(ourMesh->id_index, ourMesh->num_index, ourMesh->index);
			}

			ourGameObject->MeshData = *ourMesh;
			//Add to mesh list for when we draw each mesh
			bool ParentFound = false;
			std::vector<GameObject*>::iterator IteratorToAddMesh = App->meshimporter->MeshesOnScene.begin();
			for (int count = 0; count < MeshesOnScene.size(); ++count) {

				
				GameObject* meshParent = *IteratorToAddMesh;

				if (meshParent->is_Selected == true) {
					ParentFound = true;
					AddMeshToListMeshesOnScene(ourGameObject, true, meshParent);
					count = App->meshimporter->MeshesOnScene.size();
				}
				else {
					ParentFound = false;
					++IteratorToAddMesh;

				}
			}

			
			if (ParentFound == false) {
				AddMeshToListMeshesOnScene(ourGameObject, false, NULL);
			}
		}

		//Free memory
		aiReleaseImport(scene);
	}

	return ourMesh;
}

void ModuleMeshImporter::AddMeshToListMeshesOnScene(GameObject* Object, bool isChildfrom, GameObject* parent)
{
	if (isChildfrom == true && parent !=NULL) {
		
			std::vector<GameObject*>::iterator IteratorToAdd = App->meshimporter->MeshesOnScene.begin();
			for (int count = 0; count < MeshesOnScene.size(); ++count) {

				GameObject* parentObj = *IteratorToAdd;
				if (parent->item_id == parentObj->item_id) {

					parentObj->ChildObjects.push_back(Object);
				}
			}
	}
	else {
		int size = MeshesOnScene.size();

		Object->item_id = size;

		Object->is_Selected = false;
		Object->is_Textured = false;
		
		

		MeshesOnScene.push_back(Object);
	}



}

void ModuleMeshImporter::CreateConsolelog(const char file[], int line, const char* format, ...)
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

