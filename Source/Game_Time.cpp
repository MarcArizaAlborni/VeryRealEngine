#include "Game_Time.h"

float Game_Time::scale_time = 1;
float Game_Time::delta_time;
float Game_Time::time;

Timer Game_Time::game_timer;

bool Game_Time::pause = false;
bool Game_Time::running = false;

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

}

void Game_Time::Resume()
{
	pause = false;

}

void Game_Time::Stop()
{
	running = false;

}