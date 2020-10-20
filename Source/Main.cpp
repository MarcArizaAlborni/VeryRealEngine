#include <stdlib.h>
#include "Application.h"
#include "Globals.h"

#include "libraries/Glew/include/GL/glew.h"
#include "libraries/SDL/include/SDL.h"

#pragma comment (lib, "libraries/Glew/lib/Release/Win32/glew32.lib")
#pragma comment (lib, "libraries/Glew/lib/Release/Win32/glew32s.lib")

#pragma comment( lib, "libraries/SDL/libx86/SDL2.lib" )
#pragma comment( lib, "libraries/SDL/libx86/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT

};




int main(int argc, char ** argv)
{
	

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	Application* App = NULL;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

		
			App = new Application();
			state = MAIN_START;
			break;

		case MAIN_START:

			
			if (App->Init() == false)
			{
			
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
			
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			
			if (App->CleanUp() == false)
			{
				
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
	}

	delete App;
	
	return main_return;
}

