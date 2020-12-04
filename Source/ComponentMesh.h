#pragma once
#ifndef __ComponentMesh_H__
#define __ComponentMesh_H__

#include "Component.h"
#include "ModuleGeometryManager.h"
#include <string>
#include "libraries/MathGeoLib/include/Geometry/AABB.h"
#include "libraries/MathGeoLib/include/Geometry/OBB.h"
#include "glmath.h"

struct MeshInfo;

class Component_Mesh : public Component {

public:

	MeshInfo* Mesh;
	std::string File_Path;

	void Enable() override;
	void Disable() override;
	void Update() override;
	void CleanUp() override;
	
	std::vector<float3> vertices;

	MeshInfo* GetMesh() const;
	std::string GetPath()const;

	void CreateMesh(MeshInfo* mesh);
	void CreatePath(std::string path);

	Component_Mesh(Game_Object* ComponentOwner);
	Component_Mesh(Game_Object* ComponentOwner, const char* file_path, MeshInfo* meshInfo = nullptr);

	bool is_Drawn = true;

	//AABB properties (temporal location)
	AABB local_AABB;
	AABB global_AABB;
	OBB global_OBB;

	uint id_vertexAABB = 0;
	uint id_indexAABB = 0;
	uint id_vertexOBB = 0;
	uint id_indexOBB = 0;

	std::vector<float3> vertices_AABB;
	std::vector<float3> vertices_OBB;
	std::vector<uint> index_AABB;
	std::vector<uint> index_OBB;

	void GenerateBBBufers();
	AABB CreateLocalAABB();
	AABB GetGlobalAABB();
	OBB GetOBB();

	void DrawAABB();
	void DrawOBB();
	
};

#endif