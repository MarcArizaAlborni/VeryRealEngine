#include "Globals.h"
#include "Application.h"
#include "ModuleHierarchy.h"

#include "libraries/ImGUI/imgui.h"
#include "libraries/ImGUI/imgui_internal.h"
#include "libraries/ImGUI/imgui_impl_sdl.h"
#include "libraries/ImGUI/imgui_impl_opengl3.h"

#include "libraries/Glew/include/GL/glew.h" 
#include "libraries/SDL/include/SDL_opengl.h"


ModuleHierarchyGameObject::ModuleHierarchyGameObject(Application* app, const char* name, bool start_enabled) : Module(app, name, start_enabled)
{
	

	
}

ModuleHierarchyGameObject::~ModuleHierarchyGameObject()
{}


bool ModuleHierarchyGameObject::Start()
{
	
	return true;
}

update_status ModuleHierarchyGameObject::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleHierarchyGameObject::CleanUp()
{

	return true;
}

void ModuleHierarchyGameObject::CreateHierarchyWindow()
{
	if (App->mainMenubar->show_hierarchy_window) {

        ImGui::Begin("HierarchyWindow", &App->mainMenubar->show_hierarchy_window);

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
     
        ImGui::Separator();

        std::vector<GameObject*>::iterator IteratorLoaded = App->meshimporter->MeshesOnScene.begin();
        for (int count = 0; count < App->meshimporter->MeshesOnScene.size(); ++count) {

            GameObject* Mesh = *IteratorLoaded;
           
           InspectorInfo(Mesh, count);

            IteratorLoaded++;
        }

       // ImGui::Columns(1);
        ImGui::Separator();
        ImGui::PopStyleVar();
        ImGui::End();

	}
}

void ModuleHierarchyGameObject::InspectorInfo(GameObject* Object, int uid)
{
    ImGui::PushID(uid);

    const char* prefix;

    prefix = Object->mesh_name.c_str();

    // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to make the tree lines equal high.
    ImGui::AlignTextToFramePadding();
    bool node_open;
    if (node_open = ImGui::TreeNode("Node ID", "%s_%u", prefix, uid)) {

    }
    ImGui::NextColumn();
    ImGui::AlignTextToFramePadding();
    ImGui::NextColumn();
    ImGui::SameLine(0, 20.0f);

    GameObject* Item2 = new GameObject();
    GameObject* Item4 = new GameObject();
    bool has_been_found = false;
    if (ImGui::Checkbox("Draw in Inspector", &Object->ToBeDrawInspector)) {

        std::vector<GameObject*>::iterator IteratorLoaded = App->meshimporter->MeshesOnScene.begin();
        for (int a = 0; a < App->meshimporter->MeshesOnScene.size(); ++a) {

            Item2 = *IteratorLoaded;

            if (Object->item_id != Item2->item_id) {
                Item2->ToBeDrawInspector = false;
            }

            if (Item2->ChildObjects.size() > 0) {
                GameObject* Item3 = new GameObject();
                std::vector<GameObject*>::iterator ChildIteratorLoadedIns = Item2->ChildObjects.begin();
                for (int c = 0; c < Item2->ChildObjects.size(); ++c) {

                    Item3 = *ChildIteratorLoadedIns;
                    if (Object->item_id != Item3->item_id) {
                        Item3->ToBeDrawInspector = false;
                        Item2->ToBeDrawInspector = false;
                    }
                    ++ChildIteratorLoadedIns;
                }
            }

            IteratorLoaded++;
        }
    }

    
    ImGui::SameLine();

    if (Object->is_Drawn) {

        if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawIconHierarchyOpen.texture_id, { (float)App->textureImporter->DrawIconHierarchyOpen.width,
             (float)App->textureImporter->DrawIconHierarchyOpen.height })) {

            Object->is_Drawn = false;
        }
    }
    else {
        if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawIconHierarchyClosed.texture_id, { (float)App->textureImporter->DrawIconHierarchyClosed.width,
            (float)App->textureImporter->DrawIconHierarchyClosed.height })) {

            Object->is_Drawn = true;
        }
    }




    if (node_open)
    {
        GameObject* Mesh = new GameObject();
       // App->inspector->ShowSelectedObjectInfo(Object);
        if(Object->ChildObjects.size()>0){
            std::vector<GameObject*>::iterator IteratorChild = Object->ChildObjects.begin();
           
            for (int childNum = 0; childNum < Object->ChildObjects.size(); ++childNum) {
           
                Mesh = *IteratorChild;
          
                ImGui::PushID(childNum);
                if (childNum < Object->ChildObjects.size()+1) // Amount of childrens displayed in the editor
                {
                     InspectorInfo(Mesh, Mesh->item_id);
                }
                else
                {
                  
                    ImGui::AlignTextToFramePadding();
                    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
                    // ImGui::TreeNodeEx("Field", flags, "Field_%d", i);
                    ImGui::NextColumn();
                    ImGui::SetNextItemWidth(-1);
                   
                    ImGui::NextColumn();
                }
                ImGui::PopID();

                
               
                ++IteratorChild;
            }
        
         }

        ImGui::TreePop();
    }
    ImGui::PopID();
}

void ModuleHierarchyGameObject::CreateConsolelog(const char file[], int line, const char* format, ...)
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