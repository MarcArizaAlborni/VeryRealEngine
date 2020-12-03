// family Move

	/*GameObject* MoveAsFamily;
	GameObject* MoveAsFamilyChild;
	std::vector<GameObject*>::iterator IteratorPositionModifierFamily = App->meshimporter->MeshesOnScene.begin();
	for (int t = 0; t < App->meshimporter->MeshesOnScene.size(); ++t) {

		MoveAsFamily = *IteratorPositionModifierFamily;

		if (MoveAsFamily->Modifier.is_FamilyMove){

			std::vector<GameObject*>::iterator IteratorModifierFamilyChild = MoveAsFamily->ChildObjects.begin();
			for (int u = 0; u < MoveAsFamily->ChildObjects.size(); ++u) {

				MoveAsFamilyChild = *IteratorModifierFamilyChild;

				MoveAsFamilyChild->Mesh_Transform_Modifiers.VectorRotation = MoveAsFamily->Mesh_Transform_Modifiers.VectorRotation;
				MoveAsFamilyChild->Mesh_Transform_Modifiers.VectorScale = MoveAsFamily->Mesh_Transform_Modifiers.VectorScale;
				MoveAsFamilyChild->Mesh_Transform_Modifiers.VectorTranslation = MoveAsFamily->Mesh_Transform_Modifiers.VectorTranslation;

				++IteratorModifierFamilyChild;
			}
		}
		++IteratorPositionModifierFamily;
	}*/

// 



//UpdateGameObjectTransforms();

	// CHECK

	/*GameObject* MoveAsFamily;
	GameObject* MoveAsFamilyChild;
	std::vector<GameObject*>::iterator IteratorPositionModifierFamily = App->meshimporter->MeshesOnScene.begin();
	for (int t = 0; t < App->meshimporter->MeshesOnScene.size(); ++t) {

		MoveAsFamily = *IteratorPositionModifierFamily;

		if (MoveAsFamily->Modifier.is_FamilyMove){

			std::vector<GameObject*>::iterator IteratorModifierFamilyChild = MoveAsFamily->ChildObjects.begin();
			for (int u = 0; u < MoveAsFamily->ChildObjects.size(); ++u) {

				MoveAsFamilyChild = *IteratorModifierFamilyChild;

				MoveAsFamilyChild->Mesh_Transform_Modifiers.VectorRotation = MoveAsFamily->Mesh_Transform_Modifiers.VectorRotation;
				MoveAsFamilyChild->Mesh_Transform_Modifiers.VectorScale = MoveAsFamily->Mesh_Transform_Modifiers.VectorScale;
				MoveAsFamilyChild->Mesh_Transform_Modifiers.VectorTranslation = MoveAsFamily->Mesh_Transform_Modifiers.VectorTranslation;

				++IteratorModifierFamilyChild;
			}
		}
		++IteratorPositionModifierFamily;
	}*/


//TRYING OUT STUFF

	/*Game_Object* Object1;
	Game_Object* Object2;

	std::vector< Game_Object*>::iterator IteratorObjects = ObjectsOnScene.begin();
	for (int a = 0; a < ObjectsOnScene.size(); ++a) {

		Object1 = *IteratorObjects;

		if (Object1->Children_List.size() > 0) {

			if (Object1->Mesh->is_Drawn == true) {

				DrawMeshTextured(*IteratorObjects);
			}
		}
		else {

			std::vector<Game_Object*>::iterator IteratorChildObjects = Object1->Children_List.begin();
			for (int c = 0; c < Object1->Children_List.size(); ++c) {

				Object2 = *IteratorChildObjects;

				if (Object2->Mesh->is_Drawn == true) {
					DrawMeshTextured(*IteratorChildObjects);
				}
				++IteratorChildObjects;
			}
		}

		++IteratorObjects;
	}*/


//HIERARCHY 

	//void ModuleHierarchyGameObject::CreateHierarchyWindow()
	//{
	//	if (App->editor->show_hierarchy_window) {
	//
	//        bool itemRemoved;
	//        int uid2 = 0;
	//
	//        ImGui::Begin("HierarchyWindow", &App->editor->show_hierarchy_window);
	//
	//        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
	//     
	//        ImGui::Separator();
	//
	//        std::vector<GameObject*>::iterator IteratorLoaded = App->meshimporter->MeshesOnScene.begin();
	//        for (int count = 0; count < App->meshimporter->MeshesOnScene.size(); ++count) {
	//
	//            GameObject* Mesh = *IteratorLoaded;
	//           
	//
	//            itemRemoved=InspectorInfo(Mesh, count);
	//
	//            if (itemRemoved == true) {
	//                count = App->meshimporter->MeshesOnScene.size();
	//                uid2 = count+1;
	//            }
	//            else {
	//                ++IteratorLoaded;
	//            }
	//        }
	//
	//        //Delete Object
	//        if (App->editor->delete_object == true)
	//        {
	//            ImGui::SetNextWindowSize({ 320,150 });
	//            ImGui::SetNextWindowPos({ 625, 300 });
	//
	//            ImGui::Begin("VeryReal Engine", &App->editor->delete_object, ImGuiWindowFlags_NoCollapse
	//                | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	//
	//            ImGui::Separator();
	//            ImGui::Text("Are you sure you want to delete the Object?");
	//
	//            ImGui::Spacing();
	//            ImGui::Text("This proces can't be undone");
	//            ImGui::Spacing();
	//            ImGui::Text("");
	//            ImGui::Spacing();
	//            ImGui::Text("");
	//            ImGui::Spacing();
	//            ImGui::Spacing();
	//            if (ImGui::Button("Yes", { 80,20 }))
	//            {
	//                App->meshimporter->MeshesOnScene.erase(App->meshimporter->MeshesOnScene.begin() + (uid2));
	//                App->editor->delete_object = false;
	//                itemRemoved = true;
	//            }
	//
	//            ImGui::SameLine(0.0F, 125.0f);
	//            if (ImGui::Button("No", { 80,20 }))
	//            {
	//                App->editor->delete_object = false;
	//            }
	//
	//            ImGui::End();
	//        }
	//
	//       // ImGui::Columns(1);
	//        ImGui::Separator();
	//        ImGui::PopStyleVar();
	//        ImGui::End();
	//
	//	}
	//}


//MORE HIERARRCHY


//bool ModuleHierarchyGameObject::InspectorInfo(Game_Object* Object, int uid)
//{
//    ImGui::PushID(uid);
//
//    bool ItemRemoved = false;
//    const char* prefix;
//
//    prefix = Object->mesh_name.c_str();
//
//    // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to make the tree lines equal high.
//    ImGui::AlignTextToFramePadding();
//    bool node_open;
//   
//    if(Object->Modifier.is_EmptyParent==true){
//        if (node_open = ImGui::TreeNode("Node ID", "%s", prefix, uid)) {
//
//        }
//    }
//    else {
//        if (node_open = ImGui::TreeNode("Node ID", "%sChildNum%d", prefix, uid)) {
//
//        }
//    }
//    
//    ImGui::NextColumn();
//    ImGui::AlignTextToFramePadding();
//    ImGui::NextColumn();
//    ImGui::SameLine(0, 20.0f);
//
//    GameObject* Item2;
//    GameObject* Item4;
//    bool has_been_found = false;
//    if (ImGui::Checkbox("", &Object->Modifier.ToBeDrawInspector)) {
//
//        std::vector<GameObject*>::iterator IteratorLoaded = App->meshimporter->MeshesOnScene.begin();
//        for (int a = 0; a < App->meshimporter->MeshesOnScene.size(); ++a) {
//
//            Item2 = *IteratorLoaded;
//
//            if (Object->Identifiers.item_id != Item2->Identifiers.item_id) {
//                Item2->Modifier.ToBeDrawInspector = false;
//            }
//
//            if (Item2->ChildObjects.size() > 0) {
//                GameObject* Item3;
//                std::vector<GameObject*>::iterator ChildIteratorLoadedIns = Item2->ChildObjects.begin();
//                for (int c = 0; c < Item2->ChildObjects.size(); ++c) {
//
//                    Item3 = *ChildIteratorLoadedIns;
//                    if (Object->Identifiers.item_id != Item3->Identifiers.item_id) {
//                        Item3->Modifier.ToBeDrawInspector = false;
//                       //Item2->ToBeDrawInspector = false; 
//                    }
//                    ++ChildIteratorLoadedIns;
//                }
//            }
//
//            IteratorLoaded++;
//        }
//    }
//
//    
//    ImGui::SameLine();
//
//    if (Object->Modifier.is_Drawn) {
//
//        if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawIconHierarchyOpen.texture_id, { (float)App->textureImporter->DrawIconHierarchyOpen.width,
//             (float)App->textureImporter->DrawIconHierarchyOpen.height })) {
//
//            Object->Modifier.is_Drawn = false;
//
//            if (Object->ChildObjects.size() > 0) {
//
//                GameObject* Mesh;
//                std::vector<GameObject*>::iterator Item = Object->ChildObjects.begin();
//                for (int count = 0; count < Object->ChildObjects.size(); ++count) {
//                    Mesh = *Item;
//
//                    Mesh->Modifier.is_Drawn = false;
//
//                    ++Item;
//
//                }
//            }
//        }
//    }
//    else {
//        if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawIconHierarchyClosed.texture_id, { (float)App->textureImporter->DrawIconHierarchyOpen.width,
//            (float)App->textureImporter->DrawIconHierarchyOpen.height })) {
//
//            Object->Modifier.is_Drawn = true;
//
//            GameObject* Mesh;
//            std::vector<GameObject*>::iterator Item = Object->ChildObjects.begin();
//            for (int count = 0; count < Object->ChildObjects.size(); ++count) {
//                Mesh = *Item;
//
//                Mesh->Modifier.is_Drawn = true;
//                ++Item;
//
//
//            }
//        }
//    }
//
//    ImGui::SameLine();
//
//    if (ImGui::ImageButton((void*)(intptr_t)App->textureImporter->DrawTrashCanIcon.texture_id, {14.0f,14.0f})) {
//
//        
//
//        App->editor->delete_object = true;
//      
//    }
//
//    
//
//    if (node_open)
//    {
//        GameObject* Mesh;
//       // App->inspector->ShowSelectedObjectInfo(Object);
//        if(Object->ChildObjects.size()>0){
//            std::vector<GameObject*>::iterator IteratorChild = Object->ChildObjects.begin();
//           
//            for (int childNum = 0; childNum < Object->ChildObjects.size(); ++childNum) {
//           
//                Mesh = *IteratorChild;
//          
//                ImGui::PushID(childNum);
//                if (childNum < Object->ChildObjects.size()+1) // Amount of childrens displayed in the editor
//                {
//                     InspectorInfo(Mesh, Mesh->Identifiers.item_id);
//                }
//                else
//                {
//                  
//                    ImGui::AlignTextToFramePadding();
//                    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
//                    // ImGui::TreeNodeEx("Field", flags, "Field_%d", i);
//                    ImGui::NextColumn();
//                    ImGui::SetNextItemWidth(-1);
//                   
//                    ImGui::NextColumn();
//                }
//                ImGui::PopID();
//
//                
//               
//                ++IteratorChild;
//            }
//        
//         }
//
//        ImGui::TreePop();
//    }
//    ImGui::PopID();
//
//
//    return ItemRemoved;
//
//}