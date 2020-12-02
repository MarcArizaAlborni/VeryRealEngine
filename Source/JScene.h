#ifndef _JSCENE_H_
#define _JSCENE_H_

#include "Globals.h"
#include "libraries/MathGeoLib/include/Math/float3.h"
#include "libraries/MathGeoLib/include/Math/Quat.h"
#include <vector>
#include <string>
#include "libraries/Parson/parson.h"

class string;

class JScene_Array;

class JScene
{
	public:
		JScene();						//New Files
		JScene(char* buffer);			//Read Data
		JScene(JSON_Object * obj);		//Nodes
		~JScene();					

		uint Serialize(char** buffer);	//Serialize function
		bool NodeExists();
		void Release();

		double GetDouble(const char* name, double std = 0) const;
		std::string GetString(const char* name, const char* std = "") const;
		bool GetBool(const char* name, bool std = true) const;
		JScene_Array GetArray(const char* name) const;
		JScene GetNode(const char* name) const;

		void SetDouble(const char* name, double new_data);
		void SetString(const char* name, const char* new_data);
		void SetBool(const char* name, bool new_data);
		JScene_Array SetArray(const char* name);
		JScene SetNode(const char* name);

	private:
		JSON_Value* vroot = nullptr; 
		JSON_Object* node = nullptr;
};

class JScene_Array
{
public:

	JScene_Array();
	JScene_Array(JSON_Array* arr);

	void AddNum(double num);
	void AddString(char* string);
	void AddBool(bool boolean);
	void AddFloat3(const float3& data);
	void AddQuat(const Quat& data);
	JScene AddNode();


	double GetNumber(uint index, double default = 0) const;
	const char* GetString(uint index, const char* default = "") const;
	bool GetBool(uint index, bool default = true) const;
	float3 GetFloat3(uint index, float3 default = float3::zero) const;
	Quat GetQuat(uint index, Quat  default = Quat::identity) const;
	JScene GetNode(uint index) const;
	uint GetSize() const;

	void SaveVectorNumber(std::vector<double>& vector); //Saves array pos of the type inside a vector of the same type
	void SaveVectorString(std::vector<char*>& vector);
	void SaveVectorBoool(std::vector<bool>& vector);
	
private:
	JSON_Array* arr;
	uint size = 0;
};

#endif //__CONFIG_H__
