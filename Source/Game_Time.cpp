#include "Game_Time.h"

float Game_Time::scale_time = 1;
float Game_Time::delta_time;
float Game_Time::time;

Timer Game_Time::game_timer;

bool Game_Time::pause = false;
bool Game_Time::running = false;
bool Game_Time::oneframe = false;

void Game_Time::Start()
{
	running = true;
	game_timer.Start();
	time = 0;
}

void Game_Time::PreUpdate(float dt)
{
	delta_time = running ? dt : 0;

	if (running)
	{
		time = game_timer.Read() / 1000.0f;
	}
}

void Game_Time::Update()
{

}

void Game_Time::Play()
{
	running = true;
}

void Game_Time::Pause()
{
	pause = true;
	game_timer.Stop();

}

void Game_Time::Resume()
{
	pause = false;
	game_timer.Resume_Timer();
}

void Game_Time::Stop()
{
	running = false;
	game_timer.Stop();
}

void Game_Time::One_Frame()
{
	
	
	//Move timer one frame
	Game_Time::oneframe = (Game_Time::oneframe == false) ? true : false;

	if (Game_Time::oneframe)
	{
		//Check if its paused
		if (Game_Time::pause)
		{
			//If it is activate resume (timer runs) and then activate pause (timer stops)
			Game_Time::Resume();
			Game_Time::pause = true;
		}
		else
		{
			//If not activate pause (timer stops) and then activate resume (timer starts)
			Game_Time::pause = true;
			Game_Time::Resume();
		}
	}
	
}