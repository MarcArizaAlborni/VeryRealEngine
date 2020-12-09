#include "JScene.h"


Scene_Manager::Scene_Manager()
{
	JValue_Root = json_value_init_object();
	Root = json_value_get_object(JValue_Root);
}

Scene_Manager::Scene_Manager(const char* FileName)
{
	if (FileName != nullptr)
	{
		JValue_Root = json_parse_file(FileName);
		if (JValue_Root != nullptr) {
			Root = json_value_get_object(JValue_Root);
			scene_name = FileName;
		}
	}
}

Scene_Manager::Scene_Manager(JSON_Object* Object): Root(Object)
{
}

Scene_Manager::Scene_Manager(JSON_Object* Object, JSON_Array* Value):Root(Object),JArray(Value)
{
}

Scene_Manager::~Scene_Manager()
{
	json_value_free(JValue_Root);
}

void Scene_Manager::WriteInt(const char* field, int value)
{
	 json_object_set_number(Root, field, (uint32)value) == JSONSuccess;
}

void Scene_Manager::WriteBool(const char* field, bool value)
{
	 json_object_set_boolean(Root, field, (bool)value) == JSONSuccess;
}

void Scene_Manager::WriteFloat(const char* field, float value)
{
	 json_object_set_number(Root, field, (float)value) == JSONSuccess;
}

void Scene_Manager::WriteDouble(const char* field, double value)
{
	 json_object_set_number(Root, field, (double)value) == JSONSuccess;
}

void Scene_Manager::WriteQuad(const char* field, Quat value)   //???? No idea how this works
{
	JSON_Value* va = json_value_init_array();
	JArray = json_value_get_array(va);
	json_object_set_value(Root, field, va);

	json_array_append_number(JArray, value.x);
	json_array_append_number(JArray, value.y);
	json_array_append_number(JArray, value.z);
	json_array_append_number(JArray, value.w);

	
}

void Scene_Manager::WriteString(const char* field, std::string value)
{
	 json_object_set_string(Root, field, value.c_str()) == JSONSuccess;
}

int Scene_Manager::ReadInt(const char* field)
{
	return int(json_object_get_number(Root, field));
}

bool Scene_Manager::ReadBool(const char* field)
{
	return bool(json_object_get_boolean(Root, field));;
}

float Scene_Manager::ReadFloat(const char* field)
{
	return float(json_object_get_number(Root, field));
}

double Scene_Manager::ReadDouble(const char* field)
{
	return double(json_object_get_number(Root, field));
}

Quat Scene_Manager::ReadQuat(const char* field) //???? No idea how this works
{
	Quat value;

	Sub_JArray = json_object_get_array(Root, field);

	value.x = json_array_get_number(Sub_JArray, 0);
	value.y = json_array_get_number(Sub_JArray, 1);
	value.z = json_array_get_number(Sub_JArray, 2);
	value.w = json_array_get_number(Sub_JArray, 3);

	return value;
}

std::string Scene_Manager::ReadString(const char* field)
{
	return json_object_get_string(Root, field);
}

bool Scene_Manager::CheckString(const char* name) const
{
	return json_object_has_value_of_type(Root, name, JSONString);
}

Scene_Manager Scene_Manager::GetSection(const char* name) const
{
	return Scene_Manager(json_object_get_object(Root, name));
}

Scene_Manager Scene_Manager::AddSection(const char* name)
{
	json_object_set_value(Root, name, json_value_init_object());
	scene_name = name;
	return GetSection(name);
}

Scene_Manager Scene_Manager::AddSectionArray(int num)
{
	JSON_Value* leaf_value = json_value_init_object();
	JSON_Object* leaf_obj = json_value_get_object(leaf_value);
	json_array_append_value(JArray, leaf_value);

	return Scene_Manager(json_value_get_object(json_array_get_value(JArray, num)));
}

Scene_Manager Scene_Manager::GetSectionArray(int num)
{
	return Scene_Manager(json_value_get_object(json_array_get_value(JArray, num)), JArray);
}

bool Scene_Manager::IsArraySection(int num)
{
	bool ret = true;
	JSON_Value* obj = json_array_get_value(JArray, num);
	if (obj)
		ret = true;
	else
		ret = false;

	return ret;
}

Scene_Manager Scene_Manager::AddJArray(const char* name)
{
	JSON_Value* va = json_value_init_array();
	JArray = json_value_get_array(va);
	json_object_set_value(Root, name, va);

	return Scene_Manager(json_value_get_object(JValue_Root), JArray);
}

Scene_Manager Scene_Manager::GetJArray(const char* name)
{
	JArray = json_object_get_array(Root, name);
	return Scene_Manager(json_value_get_object(JValue_Root), JArray);
}

bool Scene_Manager::Save(const char* name)
{
	return json_serialize_to_file(JValue_Root, name) == JSONSuccess;
}

std::string Scene_Manager::ReadName() const
{
	return scene_name;
}

JSON_Value* Scene_Manager::ReadJValueRoot() const
{
	return JValue_Root;
}
