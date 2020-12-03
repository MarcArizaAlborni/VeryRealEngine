#include "Globals.h"
#include "Application.h"
#include "ModuleHierarchy.h"
#include "ModuleMeshImporter.h"
#include "ModuleTextureImporter.h"
#include "ModuleEditor.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentTexture.h"
#include "ComponentMesh.h"


#include "libraries/ImGUI/imgui.h"
#include "libraries/ImGUI/imgui_internal.h"
#include "libraries/ImGUI/imgui_impl_sdl.h"
#include "libraries/ImGUI/imgui_impl_opengl3.h"

#include "libraries/Glew/include/GL/glew.h" 
#include "libraries/SDL/include/SDL_opengl.h"

#include "libraries/mmgr/mmgr.h"

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
    GameObject* itemp;
    GameObject* itemp2;

    std::vector<GameObject*>::iterator IteratorLoadedFamily = App->meshimporter->MeshesOnScene.begin();
    for (int countb = 0; countb < App->meshimporter->MeshesOnScene.size(); ++countb) {
    
       itemp = *IteratorLoadedFamily;

       if (itemp->Modifier.is_FamilyMove) {

           std::vector<GameObject*>::iterator IteratorLoadedFamilyChild = itemp->ChildObjects.begin();
           for (int counta = 0; counta < itemp->ChildObjects.size(); ++counta) {

               itemp2 = *IteratorLoadedFamilyChild;

               itemp2->Mesh_Transform_Modifiers.VectorRotation = itemp->Mesh_Transform_Modifiers.VectorRotation;
               itemp2->Mesh_Transform_Modifiers.VectorScale = itemp->Mesh_Transform_Modifiers.VectorScale;
               itemp2->Mesh_Transform_Modifiers.VectorTranslation = itemp->Mesh_Transform_Modifiers.VectorTranslation;

              
           }
       }

        ++IteratorLoadedFamily;
    }

	return UPDATE_CONTINUE;
}

bool ModuleHierarchyGameObject::CleanUp()
{
	return true;
}


void ModuleHierarchyGameObject::CreateHierarchyWindow()
{
    if (App->editor->show_hierarchy_window) {

        bool itemRemoved;
        int uid2 = 0;

        ImGui::Begin("HierarchyWindow", &App->editor->show_hierarchy_window);

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));

        ImGui::Separator();

        std::vector<Game_Object*>::iterator ObjectIterator = App->geometrymanager->ObjectsOnScene.begin();

        for (int count = 0; count < App->geometrymanager->ObjectsOnScene.size(); ++count) {

            Game_Object* Mesh = *ObjectIterator;

            itemRemoved = InspectorInfo(Mesh, count);

            if (itemRemoved == true) {
                count = App->geometrymanager->ObjectsOnScene.size();
                uid2 = count + 1;
            }
            else {
                ++ObjectIterator;
            }
        }

        //Delete Object
        if (App->editor->delete_object == true)
        {
            ImGui::SetNextWindowSize({ 320,150 });
            ImGui::SetNextWindowPos({ 625, 300 });

            ImGui::Begin("VeryReal Engine", &App->editor->delete_object, ImGuiWindowFlags_NoCollapse
                | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

            ImGui::Separator();
            ImGui::Text("Are you sure you want to delete the Object?");

            ImGui::Spacing();
            ImGui::Text("This proces can't be undone");
            ImGui::Spacing();
            ImGui::Text("");
            ImGui::Spacing();
            ImGui::Text("");
            ImGui::Spacing();
            ImGui::Spacing();

            if (ImGui::Button("Yes", { 80,20 }))
            {
                App->geometrymanager->ObjectsOnScene.erase(App->geometrymanager->ObjectsOnScene.begin() + (uid2));
                App->editor->delete_object = false;
                itemRemoved = true;
            }

            ImGui::SameLine(0.0F, 125.0f);
            if (ImGui::Button("No", { 80,20 }))
            {
                App->editor->delete_object = false;
            }

            ImGui::End();
        }

        ImGui::Separator();
        ImGui::PopStyleVar();
        ImGui::End();

    }
}


bool ModuleHierarchyGameObject::InspectorInfo(Game_Object* Object, int uid)
{
    ImGui::PushID(uid);

    bool ItemRemoved = false;
    const char* prefix;

    prefix = Object->name.c_str();

    // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to make the tree lines equal high.
    ImGui::AlignTextToFramePadding();
    bool node_open;
   
    if(Object->Children_List.size()==0){
        if (node_open = ImGui::TreeNode("Node ID", "%s", prefix, uid)) {

        }
    }
    else {
        if (node_open = ImGui::TreeNode("Node ID", "%sChildNum%d", prefix, uid)) {

        }
    }
    
    ImGui::NextColumn();
    ImGui::AlignTextToFramePadding();
    ImGui::NextColumn();
    ImGui::SameLine(0, 20.0f);

    Game_Object* Item2;
    Game_Object* Item4;
    bool has_been_found = false;
    if (ImGui::Checkbox("", &Object->ToBeDrawInspector)) {

        std::vector<Game_Object*>::iterator IteratorLoaded = App->geometrymanager->ObjectsOnScene.begin();
        for (int a = 0; a < App->meshimporter->MeshesOnScene.size(); ++a) {

            Item2 = *IteratorLoaded;

            if (Object->item_id != Item2->item_id) {
                Item2->ToBeDrawInspector = false;
            }

            if (Item2->Children_List.size() > 0) {
                Game_Object* Item3;
                std::vector<Game_Object*>::iterator ChildIteratorLoadedIns = Item2->Children_List.begin();
                for (int c = 0; c < Item2->Children_List.size(); ++c) {

                    Item3 = *ChildIteratorLoadedIns;
                    if (Object->item_id != Item3->item_id) {
                        Item3->ToBeDrawInspector = false;
                    
                    }
                    ++ChildIteratorLoadedIns;
                }
            }

            IteratorLoaded++;
        }
    }

    
    ImGui::SameLine();

   Component_Mesh* MeshComp= (Component_Mesh*)Object->GetComponent(Component_Types::Mesh);
   if (MeshComp != nullptr) {
       if (MeshComp->is_Drawn) {


           if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawIconHierarchyOpen.texture_id, { (float)App->textureImporter->DrawIconHierarchyOpen.width,
                (float)App->textureImporter->DrawIconHierarchyOpen.height })) {

               MeshComp->is_Drawn = false;

               if (Object->Children_List.size() > 0) {

                   Game_Object* Mesh;
                   std::vector<Game_Object*>::iterator Item = Object->Children_List.begin();
                   for (int count = 0; count < Object->Children_List.size(); ++count) {
                       Mesh = *Item;

                       MeshComp->is_Drawn = false;

                       ++Item;

                   }
               }
           }
       }
       else {
           if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawIconHierarchyClosed.texture_id, { (float)App->textureImporter->DrawIconHierarchyOpen.width,
               (float)App->textureImporter->DrawIconHierarchyOpen.height })) {

               MeshComp->is_Drawn = true;

               Game_Object* Mesh;
               std::vector<Game_Object*>::iterator Item = Object->Children_List.begin();
               for (int count = 0; count < Object->Children_List.size(); ++count) {
                   Mesh = *Item;

                   MeshComp->is_Drawn = true;
                   ++Item;


               }
           }
       }
   }

    ImGui::SameLine();

    if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawTrashCanIcon.texture_id, {14.0f,14.0f})) {

        

        App->editor->delete_object = true;
      
    }

    

    if (node_open)
    {
        Game_Object* Mesh;
       // App->inspector->ShowSelectedObjectInfo(Object);
        if(Object->Children_List.size()>0){
            std::vector<Game_Object*>::iterator IteratorChild = Object->Children_List.begin();
           
            for (int childNum = 0; childNum < Object->Children_List.size(); ++childNum) {
           
                Mesh = *IteratorChild;
          
                ImGui::PushID(childNum);
                if (childNum < Object->Children_List.size()+1) // Amount of childrens displayed in the editor
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


    return ItemRemoved;

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

	App->editor->ConsoleLogs.push_back(tmp_string2);
}