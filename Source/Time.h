#ifndef TIME_H_
#define TIME_H_

#include "Timer.h"


class Time
{

public:

    void Init();
    void Start();
    void PreUpdate(float dt);
    void Update();
    
    
    void Play();
    void Pause();
    void Resume();
    void Stop();


	float delta_t;
	float scale_t;
	float time;

	Timer game_timer;

	bool paused;
	bool running;

};

#endif 