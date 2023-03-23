#pragma once
#define TIMER (Timer::GetInstance())
#include "Singleton.h"
#include "Minigin.h"
#include <chrono>
#include <iostream>

using namespace std::chrono;

class Timer final: public dae::Singleton<Timer>
{
public:
	Timer();

	[[nodiscard]] double GetDt() const { return m_Dt; }
	[[nodiscard]] double GetFPS() const { return m_FPS; }

	friend void dae::Minigin::Run(const std::function<void()>& load); // only this function can/needs to set m_Dt value
private:
	float m_SecondsPerCount{};
	double m_AccuSec{};
	double m_FPS{};
	double m_Dt{};

	uint64_t m_CurrentTime{};
	uint64_t m_PreviousTime{};

	void Update();
	void UpdateDt();
	void UpdateFPS();
	void Sleep() const;
};