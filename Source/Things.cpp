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


//Inspector

//if (App->editor->show_inspector_window)
//	{
//		ImGui::Begin("Inspector", &App->editor->show_inspector_window);
//
//		//std::vector<GameObject*>::iterator IteratorLoaded = App->meshimporter->MeshesOnScene.begin();
//		bool SomethingDrawn = false; // if there isnt an object in the list or if none of them
//
//		//has ToBeDrawInspector==true we print a message saying theres nothing to draw
//		GameObject* ItemToDraw;
//		for (std::vector<GameObject*>::iterator IteratorLoaded = App->meshimporter->MeshesOnScene.begin(); IteratorLoaded != App->meshimporter->MeshesOnScene.end(); ++IteratorLoaded) {
//			ItemToDraw = *IteratorLoaded;
//
//			if (ItemToDraw->Modifier.ToBeDrawInspector == true) {
//				SomethingDrawn = true;
//				DrawInspectorWindowInfo(ItemToDraw);
//			}
//			else if (ItemToDraw->ChildObjects.size() > 0) {
//
//				GameObject* ChildFoundDraw;
//				std::vector<GameObject*>::iterator ChildIteratorLoaded = ItemToDraw->ChildObjects.begin();
//				for (int itB=0; itB < ItemToDraw->ChildObjects.size(); ++itB) {
//
//					ChildFoundDraw = *ChildIteratorLoaded;
//
//					if (ChildFoundDraw->Modifier.ToBeDrawInspector == true) {
//
//						SomethingDrawn = true;
//
//						DrawInspectorWindowInfo(ChildFoundDraw);
//
//						itB = ItemToDraw->ChildObjects.size();
//					}
//					else{ 
//						++ChildIteratorLoaded; 
//					}
//				}
//			}
//		}
//	
//		if (SomethingDrawn == false) {
//
//
//
//			ImGui::SetWindowFontScale(1.5);
//			ImGui::Text("No Objects Selected");
//			ImGui::SetWindowFontScale(1.0);
//		}
//
//		ImGui::End();
//	}


//inspector 2


//const char* Name;
//Name = item->mesh_name.c_str();
//
//ImGui::Text(Name);
////GENERAL INFORMATION
//if (ImGui::CollapsingHeader("General Information"))
//{
//	int ChildAmount;
//
//	ImGui::InputText(" ", (char*)item->mesh_name.c_str(), 100, ImGuiInputTextFlags_EnterReturnsTrue);
//
//	ImGui::Text("Child Amount  %d", ChildAmount = item->ChildObjects.size());
//
//	ImGui::Text("Currently Textured:");
//	ImGui::SameLine(0.0f, 10.0f);
//
//	if (item->Modifier.is_Textured == true) {
//
//		ImGui::Text("True");
//	}
//	else {
//		ImGui::Text("False");
//	}
//
//	ImGui::Checkbox("Wireframed", &item->Modifier.is_Wireframed);
//
//	ImGui::Checkbox("Draw", &item->Modifier.is_Drawn);
//
//	ImGui::Text("Item Id:");
//	ImGui::SameLine(0.0f, 10.0f);
//	ImGui::Text("%d", item->Identifiers.item_id);
//
//	ImGui::Separator();
//}
//
/////TRANSFORMATIONS
//if (ImGui::CollapsingHeader("Transformation")) {
//
//	if (ImGui::DragFloat3("Position", { &item->Mesh_Transform_Modifiers.VectorTranslation.x }, 0.2f, 0.0, 0.0, "%.2f")) { item->Mesh_Transform_Modifiers.TransformsUpdated = true; }
//
//	Quat val;
//
//
//	val = Quat::FromEulerXYZ(item->Mesh_Transform_Modifiers.VectorEulerRotation.x,
//		item->Mesh_Transform_Modifiers.VectorEulerRotation.y, item->Mesh_Transform_Modifiers.VectorEulerRotation.z);
//
//
//
//
//
//	if (ImGui::DragFloat3("Rotation", { &item->Mesh_Transform_Modifiers.VectorEulerRotation.x }, 0.02f, 0.0, 1.0, "%.3f")) {
//
//
//		item->Mesh_Transform_Modifiers.TransformsUpdated = true;
//		item->Mesh_Transform_Modifiers.VectorRotation.x = val.x;
//		item->Mesh_Transform_Modifiers.VectorRotation.y = val.y;
//		item->Mesh_Transform_Modifiers.VectorRotation.z = val.z;
//		item->Mesh_Transform_Modifiers.VectorRotation.angle = val.w;
//
//	}
//	if (ImGui::DragFloat3("Scale", { &item->Mesh_Transform_Modifiers.VectorScale.x }, 0.2f, 0.0, 0.0, "%.2f")) { item->Mesh_Transform_Modifiers.TransformsUpdated = true; }
//
//	ImGui::Checkbox("Move Family", &item->Modifier.is_FamilyMove);
//
//	ImGui::Separator();
//}
//
////MESH INFO
//if (ImGui::CollapsingHeader("Mesh")) {
//
//	ImGui::Text("Index Amount:");
//	ImGui::SameLine(0.0f, 10.0f);
//	ImGui::Text("%d", item->MeshData.num_index);
//
//	ImGui::Text("Vertex Amount:");
//	ImGui::SameLine(0.0f, 10.0f);
//	ImGui::Text("%d", item->MeshData.num_vertex);
//
//	ImGui::Text("Id Index:");
//	ImGui::SameLine(0.0f, 10.0f);
//	ImGui::Text("%d", item->MeshData.id_index);
//
//	ImGui::Text("Id Vertex:");
//	ImGui::SameLine(0.0f, 10.0f);
//	ImGui::Text("%d", item->MeshData.id_vertex);
//
//	ImGui::Separator();
//	ImGui::Text("Mesh Path:");
//	ImGui::SameLine();
//	ImGui::TextColored({ 255,255,0,1 }, "%s", &item->Identifiers.path);
//
//	if (ImGui::TreeNodeEx("Vertex Normals:", ImGuiTreeNodeFlags_DefaultOpen)) {
//
//		ImGui::Checkbox("Show Vertex Normals", &item->Modifier.showVertexNormals);
//		ImGui::TreePop();
//	}
//}
//
//
////TEXTURES INFO
//if (ImGui::CollapsingHeader("Texture")) {
//
//	ImGui::Checkbox("Checkered", &item->Modifier.is_Checkered);
//
//	if (item->Modifier.is_Checkered == true) {
//		item->Modifier.is_Textured = false;
//	}
//
//	ImGui::Checkbox("Textured", &item->Modifier.is_Textured);
//
//	if (item->Modifier.is_Textured == true) {
//		item->Modifier.is_Checkered = false;
//	}
//
//	ImGui::Text("Texture Name: ");
//	ImGui::SameLine(0.0f, 10.0f);
//	const char* nameTexture = item->TextureData.texture_name.c_str();
//	ImGui::TextColored({ 255,255,0,1 }, "%s", nameTexture);
//
//	if (item->Modifier.is_Textured) {
//		ImGui::Text("Texture Path:");
//		ImGui::SameLine(0.0f, 10.0f);
//		const char* pathnameTexture = item->TextureData.texture_path.c_str();
//		ImGui::TextColored({ 255,255,0,1 }, "%s", pathnameTexture);
//	}
//	else if (item->Modifier.is_Checkered) {
//		ImGui::Text("Texture Path:");
//		ImGui::SameLine(0.0f, 10.0f);
//
//		ImGui::Text("Checkered Texture");
//	}
//	else {
//		ImGui::Text("Texture Path:");
//		ImGui::SameLine(0.0f, 10.0f);
//
//		ImGui::Text("No texture Selected");
//	}
//
//	ImGui::Text("Texture Width");
//	ImGui::SameLine(0.0f, 10.0f);
//	ImGui::TextColored({ 255,255,0,1 }, "%d", item->TextureData.width);
//
//	ImGui::Text("Texture Height");
//	ImGui::SameLine(0.0f, 10.0f);
//	ImGui::TextColored({ 255,255,0,1 }, "%d", item->TextureData.height);
//
//	ImGui::Text("Texture id");
//	ImGui::SameLine(0.0f, 10.0f);
//	ImGui::TextColored({ 255,255,0,1 }, "%d", item->TextureData.texture_id);
//
//	ImGui::Image((void*)(intptr_t)item->TextureData.texture_id, { 200,200 });
//}