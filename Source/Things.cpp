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

