#ifndef AI_TIMER
#define AI_TIMER

#include <SDL.h>

#define TICK_INTERVAL 30

class Timer {
protected:
	static float timeScale;
	static bool stopped;
public:
	static void Initialize(bool start);
	
	static void Stop();
	static void Start();
	static double TimerUpdate();
};

#endif
