#pragma once
#ifndef __Hierarchy_H__
#define __Hierarchy_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class ModuleHierarchyGameObject : public Module
{
public:
	ModuleHierarchyGameObject(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleHierarchyGameObject();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	//Hierarchy Window Functions

	void CreateHierarchyWindow();
	bool DrawHierarchyChildren(Game_Object* Item,bool Val);
	void SelectItemHierarchy(Game_Object* SelectedItem);
	void SelectItemHierarchyChildren(Game_Object* SelectedItem,Game_Object* ItemToCheck);
	
	bool InspectorInfo(Game_Object* Object, int uid);
	

	int RootNodeCount=0; //We use this to modify the name of the root node so that the hierarchy works properly.
	bool IconDrawHierarchy=true;
	bool ITEM_TO_BE_DELETED = false;
	//------------ CONSOLE STUFF

};

#endif