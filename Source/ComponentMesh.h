#pragma once
#ifndef __ComponentMesh_H__
#define __ComponentMesh_H__

#include "Component.h"
#include "ModuleGeometryManager.h"
#include "ModuleGeometryManager.h"
#include "ModuleGeometryManager.h"

struct MeshData;



class Component_Mesh : public Component {

public:

	MeshData* Mesh;
	std::string File_Path;

	void Enable() override;
	void Disable() override;
	void Update() override;
	void CleanUp() override;
	

	MeshData* GetMesh() const { return Mesh; };
	std::string GetPath()const { return File_Path; };

	void CreateMesh(MeshData* mesh);
	void CreatePath(std::string path);


	Component_Mesh(Game_Object* owner);
	Component_Mesh(Game_Object* owner, const char* file_path, MeshData* meshInfo = nullptr);


	
};

#endif