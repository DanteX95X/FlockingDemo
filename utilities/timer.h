#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <SDL2/SDL.h>

typedef std::chrono::high_resolution_clock Clock;

class Timer
{
public:
	static Timer& Instance();
	static double GetDeltaTime();
	static short GetFPS();
	static double GetTime();
	void Update();

private:
	Timer();
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	void operator = (const Timer&) = delete;
	void operator = (Timer&&) = delete;

	std::chrono::time_point<Clock, std::chrono::duration<double>> currentTime;
	std::chrono::time_point<Clock, std::chrono::duration<double>> startTime;
	long double deltaTime;
	short fps;
	short currentFrames;
	double secondCounter;
};

#endif // TIMER_H
