#include "Time.h"



void Time::Init()
{
	scale_t = 1;

	paused = false;
	running = false;
}

void Time::Start()
{
	running = true;
	game_timer.Start();
	time = 0;
}

void Time::PreUpdate(float dt)
{
	delta_t = running ? dt : 0;

	if (running)
	{
		time = game_timer.Read() / 1000.0f;
	}
}

void Time::Update()
{
}

void Time::Play()
{
	running = true;
}

void Time::Pause()
{
	paused = true;

}

void Time::Resume()
{
	paused = false;

}

void Time::Stop()
{
	running = false;

}