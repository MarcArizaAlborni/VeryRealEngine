#pragma once
#ifndef __ComponentMesh_H__
#define __ComponentMesh_H__

#include "Component.h"
#include "ModuleGeometryManager.h"
#include "ModuleGeometryManager.h"
#include "ModuleGeometryManager.h"

struct MeshInfo;


class Component_Mesh : public Component {

public:


	MeshInfo* Mesh;
	std::string File_Path;

	void Enable() override;
	void Disable() override;
	void Update() override;
	void CleanUp() override;
	

	MeshInfo* GetMesh() const { return Mesh; };
	std::string GetPath()const { return File_Path; };

	void CreateMesh(MeshInfo* mesh);
	void CreatePath(std::string path);


	Component_Mesh(Game_Object* ComponentOwner);
	Component_Mesh(Game_Object* ComponentOwner, const char* file_path, MeshInfo* meshInfo = nullptr);


	
};

#endif