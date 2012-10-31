#ifndef AI_TIMER
#define AI_TIMER

#include <vector>
#include <SDL.h>

#define TICK_INTERVAL 30

class Timer {
protected:
	static bool stopped;
	static int sampleIndex;
	static const int sampleSize = 11;
	static const int noiseConstant = 4;
	static float timeScale;
	static std::vector<double> history;
public:
	static void Initialize(bool start);
	
	static void Stop();
	static void Start();
	static double TimerUpdate();
};

#endif
