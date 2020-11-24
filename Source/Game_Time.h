#ifndef TIME_H_
#define TIME_H_

#include "Timer.h"


class Game_Time
{

public:

    static void Start();
   static void PreUpdate(float dt);
   static void Update();
    
    
   static void Play();
   static void Stop();
   static void Pause();
   static void Resume();

   static float delta_time;
   static float scale_time;
   static float time;

   static Timer game_timer;

   static bool pause;
   static bool running;

};

#endif 