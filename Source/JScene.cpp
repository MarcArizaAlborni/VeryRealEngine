#include "JScene.h"

JScene::JScene()
{
	vroot = json_value_init_object();
	node = json_value_get_object(vroot);
}

JScene::JScene(char* buffer)
{
	vroot = json_parse_string(buffer);
	if (vroot)
	{
		node = json_value_get_object(vroot);
	}
}

JScene::JScene(JSON_Object* obj) : node(obj)
{
}

JScene::~JScene()
{
	Release();
}

//Converts a object into a string
uint JScene::Serialize(char** buffer)
{
	size_t size = json_serialization_size_pretty(vroot);
	*buffer = new char[size];
	json_serialize_to_buffer_pretty(vroot, *buffer, size);
	return size;
}

bool JScene::NodeExists()
{
	return vroot != nullptr;
}

void JScene::Release()
{
	// Clean
	if (vroot)
	{
		json_value_free(vroot);
	}
}

//Getters
double JScene::GetDouble(const char* name, double std) const
{
	if (json_object_has_value_of_type(node, name, JSONNumber))
	{
		return json_object_get_number(node, name);
	}
		
	return std;
}

std::string JScene::GetString(const char* name, const char* std) const
{
	if (json_object_has_value_of_type(node, name, JSONString))
	{
		return json_object_get_string(node, name);
	}
		
	return std;
}

bool JScene::GetBool(const char* name, bool std) const
{
	if (json_object_has_value_of_type(node, name, JSONBoolean))
	{
		return json_object_get_boolean(node, name);
	}
		
	return std;
}

JScene_Array JScene::GetArray(const char* name) const
{
	if (json_object_has_value_of_type(node, name, JSONArray))
	{
		return JScene_Array(json_object_get_array(node, name));
	}
		
	else
	{
		return JScene_Array();
	}
}

JScene JScene::GetNode(const char* name) const
{
	return JScene(json_object_get_object(node, name));
}


//Setters
void JScene::SetDouble(const char* name, double new_data)
{
	json_object_set_number(node, name, new_data);
}

void JScene::SetString(const char* name, const char* new_data)
{
	json_object_set_string(node, name, new_data);
}

void JScene::SetBool(const char* name, bool new_data)
{
	json_object_set_boolean(node, name, new_data);
}

JScene_Array JScene::SetArray(const char* name)
{
	json_object_set_value(node, name, json_value_init_array());

	return JScene_Array(json_object_get_array(node, name));
}

JScene JScene::SetNode(const char* name)
{
	json_object_set_value(node, name, json_value_init_object());

	return JScene(json_object_get_object(node, name));
}


// Class JScene_Array
JScene_Array::JScene_Array()
{
	arr = json_value_get_array(json_value_init_array());
}

JScene_Array::JScene_Array(JSON_Array * arr) : arr(arr)
{
	size = json_array_get_count(arr);
}

//Add functions (GO)
void JScene_Array::AddNum(double num)
{
	json_array_append_number(arr, num);
	size++;
}

void JScene_Array::AddString(char* string)
{
	json_array_append_string(arr, string);
	size++;
}

void JScene_Array::AddBool(bool boolean)
{
	json_array_append_boolean(arr, boolean);
	size++;
}

void JScene_Array::AddFloat3(const float3 & data)
{
	json_array_append_number(arr, data.x);
	json_array_append_number(arr, data.y);
	json_array_append_number(arr, data.z);
	size += 3;
}

void JScene_Array::AddQuat(const Quat & data)
{
	json_array_append_number(arr, data.x);
	json_array_append_number(arr, data.y);
	json_array_append_number(arr, data.z);
	json_array_append_number(arr, data.w);
	size += 4;
}

JScene JScene_Array::AddNode()
{
	json_array_append_value(arr, json_value_init_object());
	size++;
	return JScene(json_array_get_object(arr, size - 1));
}

//Getter for Json Array
double JScene_Array::GetNumber(uint index, double default) const
{
	if (index < size)
		return json_array_get_number(arr, index);
	else
	{
		return 0;
	}
}

const char* JScene_Array::GetString(uint index, const char* default) const
{
	if (index < size)
		return json_array_get_string(arr, index);
	else
	{
		LOG("[Warning] JSON Array: Index out of size");
		return default;
	}
}

float3 JScene_Array::GetFloat3(uint index, float3 default) const
{
	index *= 3;
	float3 ret = default;

	ret.x = GetNumber(index + 0, ret.x);
	ret.y = GetNumber(index + 1, ret.y);
	ret.z = GetNumber(index + 2, ret.z);

	return ret;
}

Quat JScene_Array::GetQuat(uint index, Quat  default) const
{
	index *= 4;
	Quat ret = default;

	ret.x = GetNumber(index + 0, ret.x);
	ret.y = GetNumber(index + 1, ret.y);
	ret.z = GetNumber(index + 2, ret.z);
	ret.w = GetNumber(index + 3, ret.w);

	return ret;
}

bool JScene_Array::GetBool(uint index, bool default) const
{
	if (index < size)
		return json_array_get_boolean(arr, index);
	else
	{
		LOG("[Warning] JSON Array: Index out of size");
		return default;
	}
}

JScene JScene_Array::GetNode(uint index) const
{
	return JScene(json_array_get_object(arr, index));
}

uint JScene_Array::GetSize() const
{
	return size;
}

void JScene_Array::SaveVectorNumber(std::vector<double> & vector) 
{
	for (uint i = 0; i < size; i++)
	{
		vector.push_back(GetNumber(i));
	}
}

void JScene_Array::SaveVectorString(std::vector<char*> & vector)
{
	for (uint i = 0; i < size; i++)
	{
		vector.push_back((char*)GetString(i));
	}
}

void JScene_Array::SaveVectorBoool(std::vector<bool> & vector) 
{
	for (uint i = 0; i < size; i++)
	{
		vector.push_back(GetBool(i));
	}
}

