#pragma once
#ifndef __ModuleLoader_H__
#define __ModuleLoader_H__
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Primitive.h"
#include "Light.h"
#include "libraries/Glew/include/GL/glew.h"
#include "libraries/MathGeoLib/include/Geometry/Frustum.h"
#include "libraries/MathGeoLib/include/MathGeoLib.h"


#define MAX_LIGHTS 8

struct MeshInfo;

class Game_Object;
class Components;
class Component_Transform;
class Component_Camera;
struct VectorTransformations {

	GLfloat angle,x,y,z;

};
class ModuleGeometryManager : public Module
{
public:
	ModuleGeometryManager(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleGeometryManager();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();


public:
	// Insert Primitives
	void DrawPlane();
	void DrawCube();
	void DrawPyramid();
	void DrawSphere();
	void DrawCylinder();

	//Transformations

	
	void Transform_Mesh_Draw(Component_Transform* mesh);



	void UpdateGameObjectTransforms();


	//Meshes
	void DrawMeshTextured(Game_Object* mesh);

	//Normals
	void DrawVertexNormals(Game_Object* object);

	//Cull
	bool ContainsAABB(const AABB& aabb) const;

	std::vector<Game_Object*> ObjectsOnScene;

	//------------ CONSOLE STUFF

};

#endif