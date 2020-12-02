#pragma once
#include <string>
#include "libraries/Parson/parson.h"
#include "JScene.h"
#include "Globals.h"

class Application;
#include "Globals.h"

class Module
{
private:
	bool enabled;

public:
	Application* App;
	std::string name;
	bool active;
	Module(Application* parent, const char* name = "none", bool start_enabled = true) : App(parent), name(name), active(start_enabled)
	{}

	virtual ~Module()
	{}

	virtual bool Init()
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	virtual void SaveJScene(JScene& root) const
	{}

	virtual void LoadJScene(JScene& root)
	{}

	
};