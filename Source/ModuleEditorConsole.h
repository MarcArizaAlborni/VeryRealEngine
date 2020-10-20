#pragma once
#ifndef __ModuleEditorConsole_H__
#define __ModuleEditorConsole_H__


#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include <vector>
#include "libraries/ImGUI/imgui.h"

class ModuleEditorConsole : public Module
{
public:

	ModuleEditorConsole(Application* app, const char* name = "null", bool start_enabled = true);
	~ModuleEditorConsole();

	// ---------------Console Window---------------
	void CreateConsoleWindow();

	///---------------CONSOLE STUFF-------------

	std::list<char*> ConsoleLogs;
	int LogsAmount;

#define LOGFIX(format, ...) CreateConsolelog(__FILE__, __LINE__, format, __VA_ARGS__);
	void CreateConsolelog(const char file[], int line, const char* format, ...);

	void CallLOG(char* text);
};

#endif 