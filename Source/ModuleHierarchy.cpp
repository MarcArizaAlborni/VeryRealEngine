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
#include "ModuleInput.h"
#include "ModuleScene.h"


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
    

	return UPDATE_CONTINUE;
}

bool ModuleHierarchyGameObject::CleanUp()
{
	return true;
}


void ModuleHierarchyGameObject::CreateHierarchyWindow()
{
    std::vector<Game_Object*>::iterator It = App->geometrymanager->ObjectsOnScene.begin();
    if (App->editor->show_hierarchy_window) {
        ImGui::Begin("HierarchyWindow", &App->editor->show_hierarchy_window);
        for (int size = 0; size < App->geometrymanager->ObjectsOnScene.size(); ++size) {
            Game_Object* Item = *It;
            
            if (!DrawHierarchyChildren(Item, false)) {

              ++It;

            }
            else{
                size = App->geometrymanager->ObjectsOnScene.size();
            }
        }
        ChildOfGeneralParented = false;
        ImGui::End();
    }
}

bool ModuleHierarchyGameObject::DrawHierarchyChildren(Game_Object* Item, bool Reparented)
{
    ImGuiTreeNodeFlags FlagsNodes =   ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth| ImGuiTreeNodeFlags_OpenOnArrow;

    if (Item->Children_List.size() == 0) {
        FlagsNodes |= ImGuiTreeNodeFlags_Leaf;
    }

    if (Item->ToBeDrawInspector) {
        FlagsNodes |= ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_Framed;
    }

    ImGui::AlignTextToFramePadding();

   

    if (ImGui::TreeNodeEx(Item->name.c_str(), FlagsNodes)) {

        if (ImGui::BeginDragDropSource()) {
            

ImGui::SetDragDropPayload("Dragged_Object", Item, sizeof(Game_Object));
App->editor->DragedItem = Item;
ImGui::EndDragDropSource();
        }

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Dragged_Object"))
            {
                if (App->editor->DragedItem->Parent->name == "MainScene") {
                    ChildOfGeneralParented = true;
                }
                Item->ChangeParentFromObject(App->editor->DragedItem);
                App->editor->DragedItem = nullptr;
                Reparented = true;
            }
            ImGui::EndDragDropTarget();
        }

        if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
        {
            if ((Component_Camera*)Item->GetComponent(Component_Types::Camera) != nullptr)
            {
                SelectItemHierarchy(Item);

            }

            if ((Component_Mesh*)Item->GetComponent(Component_Types::Mesh) != nullptr) {

                SelectItemHierarchy(Item);
                

            }

        }



        if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
        {
                ImGui::OpenPopup("Delete Game Object");

               
                
                
        }

        if (ImGui::BeginPopup("Delete Game Object"))
        {
            if (ImGui::Selectable("Delete Game Object"))
            {
                Item->ToBeDrawInspector = true;
                App->hierarchy->ITEM_TO_BE_DELETED = true;
                App->scene->ObjectToBeDeleted = Item;
            }

            if (ImGui::Selectable("Create Child"))
            {
                Game_Object* EmptyChildren = new Game_Object("Empty Children");

                std::vector < Game_Object* >::iterator it = App->geometrymanager->ObjectsOnScene.begin();
                Game_Object* SelectedItem;

                for (int i = 0; i < App->geometrymanager->ObjectsOnScene.size(); ++i)
                {
                    SelectedItem = *it;
                    SelectedItem = App->scene->LookForSelectedChild(SelectedItem);

                    if (SelectedItem != nullptr)
                    {
                        if (SelectedItem->ToBeDrawInspector)
                        {
                            SelectedItem->Children_List.push_back(EmptyChildren);
                            i = App->geometrymanager->ObjectsOnScene.size();
                        }
                    }
                    ++it;
                }
            }

            ImGui::EndPopup();
        }
        
            

        std::vector<Game_Object*>::iterator It = Item->Children_List.begin();
        for (int size = 0; size < Item->Children_List.size(); ++size) {

            Game_Object* Child = *It;

            if (!DrawHierarchyChildren(Child, Reparented)) {
                if (ChildOfGeneralParented) {

                    size = Item->Children_List.size();
                    break;
                }
                else {
                    ++It;
                }

            }
            else {
                size = Item->Children_List.size();
            }

        }
        ImGui::TreePop();
    }
    return Reparented;
}

void ModuleHierarchyGameObject::SelectItemHierarchy(Game_Object* SelectedItem)
{
    std::vector<Game_Object*>::iterator It = App->geometrymanager->ObjectsOnScene.begin();

    for (int size = 0; size < App->geometrymanager->ObjectsOnScene.size(); ++size) {

        Game_Object* Object = *It;

        if (SelectedItem == Object) {

            if (Object->ToBeDrawInspector == true) {
                Object->ToBeDrawInspector = false;
            }
            else {
                Object->ToBeDrawInspector = true;
            }

        }
        else {
            Object->ToBeDrawInspector = false;
        }

        if (Object->Children_List.size() > 0) {
            std::vector<Game_Object*>::iterator ItC = Object->Children_List.begin();
            for (int sizeC = 0; sizeC < Object->Children_List.size(); ++sizeC) {
                Game_Object* ChildObject = *ItC;

                SelectItemHierarchyChildren(SelectedItem, ChildObject);

                if (SelectedItem == ChildObject) {

                    if (ChildObject->ToBeDrawInspector == true) {
                        ChildObject->ToBeDrawInspector = false;
                    }
                    else {

                        ChildObject->ToBeDrawInspector = true;

                        
                    }

                }
                else {
                    ChildObject->ToBeDrawInspector = false;
                }
                ++ItC;
            }
        }

        ++It;
    }

}

void ModuleHierarchyGameObject::SelectItemHierarchyChildren(Game_Object* SelectedItem, Game_Object* ItemToCheck)
{
    
    std::vector<Game_Object*>::iterator It = ItemToCheck->Children_List.begin();

    for (int size = 0; size < ItemToCheck->Children_List.size(); ++size) {

        Game_Object* Object = *It;

        if (SelectedItem == Object) {

            if (Object->ToBeDrawInspector == true) {
                Object->ToBeDrawInspector = false;
                App->scene->ObjectToBeDeleted = nullptr;
            }
            else {
                Object->ToBeDrawInspector = true;
                App->scene->ObjectToBeDeleted = Object;
            }
        }
        else {
            Object->ToBeDrawInspector = false;
           // App->scene->ObjectToBeDeleted = nullptr;
        }

        if (Object->Children_List.size() > 0) {
            std::vector<Game_Object*>::iterator ItC = Object->Children_List.begin();
            for (int sizeC = 0; sizeC < Object->Children_List.size(); ++sizeC) {
                Game_Object* ChildObject = *ItC;

                SelectItemHierarchyChildren(SelectedItem,ChildObject);

                if (SelectedItem == ChildObject) {

                    if (ChildObject->ToBeDrawInspector == true) {
                        ChildObject->ToBeDrawInspector = false;
                        App->scene->ObjectToBeDeleted = nullptr;
                    }
                    else {
                        ChildObject->ToBeDrawInspector = true;
                        App->scene->ObjectToBeDeleted = ChildObject;
                    }
                }
                else {
                    ChildObject->ToBeDrawInspector = false;
                   
                }

                ++ItC;
            }
        }

        ++It;
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
        for (int a = 0; a < App->geometrymanager->ObjectsOnScene.size(); ++a) {

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

