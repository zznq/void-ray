#include "Timer.hpp"
#include <algorithm>

bool Timer::stopped = false;
int Timer::sampleIndex = 0;
float Timer::timeScale = 1.0f;
std::vector<double> Timer::history = std::vector<double>(sampleSize, 0);

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
	        return 0.0;
	}
	
	Uint32 new_time = now - last_time;
	last_time = now;
	
	double elapsed_time = Timer::timeScale * (new_time / 1000.0);
	Timer::history[Timer::sampleIndex] = elapsed_time;
	Timer::sampleIndex = (Timer::sampleIndex + 1) % Timer::sampleSize;

    double sum = 0;

	sort(Timer::history.begin(), Timer::history.end());

	for (int i=0; i<Timer::history.size(); i++) {
		//Discard top two and bottom two results
		if(i >= (noiseConstant /2) && i < (Timer::history.size() - noiseConstant /2)){
			sum += Timer::history.at(i);
		}
	}

    return sum / ((double)Timer::history.size() - noiseConstant);
}
