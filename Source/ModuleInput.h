#pragma once
#ifndef __ModuleInput_H__
#define __ModuleInput_H__


#include "Module.h"
#include "Globals.h"

#define MAX_MOUSE_BUTTONS 5

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};
struct TextureInfo;
class ModuleInput : public Module
{
public:

	ModuleInput(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleInput();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);

	bool CleanUp();

	KEY_STATE GetKey(int id) const
	{
		return keyboard[id];
	}

	KEY_STATE GetMouseButton(int id) const
	{
		return mouse_buttons[id];
	}

	int GetMouseX() const
	{
		return mouse_x;
	}

	int GetMouseY() const
	{
		return mouse_y;
	}

	int GetMouseZ() const
	{
		return mouse_z;
	}

	int GetMouseXMotion() const
	{
		return mouse_x_motion;
	}

	int GetMouseYMotion() const
	{
		return mouse_y_motion;
	}

public:
	KEY_STATE* keyboard;
	KEY_STATE mouse_buttons[MAX_MOUSE_BUTTONS];
	int mouse_x;
	int mouse_y;
	int mouse_z;
	int mouse_x_motion;
	int mouse_y_motion;
	//int mouse_z_motion;



	int CheckImportedFileType(std::string string1, std::string string2);

private:
	void CheckSelectedChild(Game_Object* Object,TextureInfo Texture);


public:

	bool ExitEngine;


	//----------DROP ITEMS

	std::string Drop_Path;

//------------ CONSOLE STUFF
#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);
};

#endif