#include "timer.h"
#include <iostream>

Timer::Timer()
	: currentTime{std::chrono::high_resolution_clock::now()}, startTime{currentTime}, deltaTime{0}, fps{0}, currentFrames{0}, secondCounter{0}
{
}

void Timer::Update()
{

	++currentFrames;

	deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - currentTime).count()/1000000000.0;

	currentTime = Clock::now();
	secondCounter += deltaTime;
	if(secondCounter >= 1)
	{
		secondCounter = 0;
		fps = currentFrames;
		currentFrames = 0;
	}
}

Timer& Timer::Instance()
{
	static Timer instance;
	return instance;
}

double Timer::GetDeltaTime() { return Instance().deltaTime; }

short Timer::GetFPS() { return Instance().fps; }

double Timer::GetTime() { return std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - Instance().startTime).count()/1000000000.0; }
