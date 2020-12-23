#ifndef __JsonFiles_H__
#define __JsonFiles_H__


#include "libraries/json/json.hpp"
#include <string>

using json = nlohmann::json;

class  JSONFiles {
public:

	JSONFiles() {}
	~JSONFiles() {}

	json Load(const char* File) const;

	bool Save(const char* File, const json& jsonfile);

	void Serialize(const json& jsonfile, std::string& jsonserialized);


};

#endif
