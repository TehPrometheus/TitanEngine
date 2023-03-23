#include "Timer.h"
#include <SDL.h>
#include <thread>
#include <chrono>

Timer::Timer()
{
	const uint64_t countPerSecond = SDL_GetPerformanceFrequency();
	m_SecondsPerCount = 1.f / static_cast<float>(countPerSecond);
	m_PreviousTime = SDL_GetPerformanceCounter(); // ensures that the first m_Dt is small, otherwise long load time.
}

void Timer::Sleep() const
{
	constexpr int targetFPS{ 60 };
	constexpr double frameTimeSeconds{ 1.0 / targetFPS };
	const auto sleepTime{ frameTimeSeconds - m_Dt };
	std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
}

void Timer::Update()
{
	UpdateDt();
	UpdateFPS();
}

void Timer::UpdateDt()
{
	m_CurrentTime = SDL_GetPerformanceCounter();
	m_Dt = static_cast<float>(m_CurrentTime - m_PreviousTime) * m_SecondsPerCount;
	m_PreviousTime = m_CurrentTime;

	if (m_Dt < 0)
		m_Dt = 0;

}

void Timer::UpdateFPS()
{
	static int frameCount{};
	++frameCount;
	m_AccuSec += m_Dt;

	if(m_AccuSec > 1.0)
	{
		m_FPS = frameCount / m_AccuSec; // does not include time slept.
		frameCount = 0;
		m_AccuSec = 0.0;
	}
}
