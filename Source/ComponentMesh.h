#pragma once
#ifndef __ComponentMesh_H__
#define __ComponentMesh_H__

#include "Component.h"
#include "ModuleGeometryManager.h"
#include <string>
#include "libraries/MathGeoLib/include/MathGeoLib.h"


struct MeshInfo;

class Component_Mesh : public Component {

public:

	~Component_Mesh();

	MeshInfo* Mesh;
	std::string File_Path;

	void Enable() override;
	void Disable() override;
	void Update() override;
	void CleanUp() override;
	
	MeshInfo* GetMesh() const;
	std::string GetPath()const;

	void CreateMesh(MeshInfo* mesh);
	void CreatePath(std::string path);

	Component_Mesh(Game_Object* ComponentOwner);
	Component_Mesh(Game_Object* ComponentOwner, const char* file_path, MeshInfo* meshInfo = nullptr);

	bool is_Drawn = true;

	//BB properties 
	void GenerateBBBufers();
	AABB CreateLocalAABB();
	AABB GetGlobalAABB();
	OBB GetOBB();

	void DrawBB();
	void UpdateOnTransformOBB();

	AABB local_AABB;
	AABB global_AABB;
	OBB global_OBB;

	uint id_vertexAABB = 0;
	uint id_vertexOBB = 0;
	uint id_indexBB = 0;

	std::vector<float3> vertices_AABB;
	std::vector<float3> vertices_OBB;
	std::vector<uint> index_BB;

	bool show_aabb = false;
	bool show_obb = false;

	//Stencil properties
	void DrawOutlineMesh(Component_Transform* transform);

	//Cull
	bool CullCheck();

	vec4 outline_color;
	int outline_width;
};

#endif