#ifndef FRAME_TIMER_H
#define FRAME_TIMER_H

#include <chrono>

class FrameTimer
{
private:
	double _deltaTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> _lastFrameTime;

	int _fpsCounter;
	std::chrono::time_point<std::chrono::high_resolution_clock> _lastFPSTime;
	double _currentFPS;

public:
	FrameTimer();

	void Update();
	double GetDeltaTime() const;

	void UpdateFPS();
	int GetFPS() const;
};

#endif