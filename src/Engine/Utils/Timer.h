#ifndef TIMER_H
#define TIMER_H

class Timer
{
private:
	double _lifeTime;

public:
	Timer() = default;

	void StartTimer(double lifeTime);
	void UpdateTimer(double deltaTime);
	bool TimerDone() const;
};

#endif