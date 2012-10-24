#include "Timer.hpp"

float Timer::timeScale = 1.0f;
bool Timer::stopped = false;

void Timer::Initialize(bool start) {
	SDL_Init(SDL_INIT_TIMER);
	Timer::stopped = !start;
}

void Timer::Stop() {
	Timer::stopped = true;	
}

void Timer::Start() {
	SDL_GetTicks();
	Timer::stopped = false;	
}
	
double Timer::TimerUpdate() {
	static Uint32 last_time = 0;
	Uint32 now;
	
	now = SDL_GetTicks();		

	if(Timer::stopped) {
		return 0.0;		
	}
	
	if ( last_time <= now ) {
	    if(now - last_time < TICK_INTERVAL)
	        return(0);
	}
	
	Uint32 new_time = now - last_time;
	last_time = now;
	
	return Timer::timeScale * (new_time / 1000.0);	
}
