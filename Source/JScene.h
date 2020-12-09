#ifndef _JSCENE_H_
#define _JSCENE_H_

#include "Globals.h"
#include "libraries/MathGeoLib/include/Math/float3.h"
#include "libraries/MathGeoLib/include/Math/Quat.h"
#include <vector>
#include <string>
#include "libraries/Parson/parson.h"




class Scene_Manager {

public:

	Scene_Manager(); //EMPTY CONSTRUCTOR
	Scene_Manager(const char* FileName);
	Scene_Manager(JSON_Object* Object);
	Scene_Manager(JSON_Object* Object, JSON_Array* Value);
	~Scene_Manager();


	void WriteInt(const char* field, int value);
	void WriteBool(const char* field, bool value);
	void WriteFloat(const char* field, float value);
	void WriteDouble(const char* field, double value);
	void WriteQuad(const char* field, Quat value);
	void WriteString(const char* field, std::string value);



	int ReadInt(const char* field);
	bool ReadBool(const char* field);
	float ReadFloat(const char* field);
	double ReadDouble(const char* field);
	Quat ReadQuat(const char* field);
	std::string ReadString(const char* field);



	bool CheckString(const char* name) const;

	Scene_Manager GetSection(const char* name) const;
	Scene_Manager AddSection(const char* name);

	Scene_Manager AddSectionArray(int num);
	Scene_Manager GetSectionArray(int num);
	bool IsArraySection(int num);

	Scene_Manager AddJArray(const char* name);
	Scene_Manager GetJArray(const char* name);

	bool Save(const char* name);

	std::string ReadName() const;
	JSON_Value* ReadJValueRoot() const;

private:
	JSON_Value* JValue_Root = nullptr;
	JSON_Object* Root = nullptr;
	JSON_Array* JArray = nullptr;
	JSON_Array* Sub_JArray = nullptr;
	std::string scene_name;
};



#endif //__CONFIG_H__
