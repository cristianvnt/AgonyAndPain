#include "Timer.h"

void Timer::StartTimer(double lifeTime)
{
	_lifeTime = lifeTime;
}

void Timer::UpdateTimer(double deltaTime)
{
	if (_lifeTime < 0.0)
		return;

	_lifeTime -= deltaTime;
}

bool Timer::TimerDone() const
{
	return _lifeTime <= 0.0;
}
