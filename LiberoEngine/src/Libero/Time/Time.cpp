#include "Liber_pch.h"
#include "Time.h"

#define LBR_TIME_NOW std::chrono::steady_clock::now()

namespace Libero
{
	Time::Time(bool startOnConstruct)
		: m_Start()
		, m_DeltaTime{}
		, m_PrevTick{}
		, m_TotalTime{}
		, m_HasStarted{startOnConstruct}
		, m_FPSCounter{}
		, m_FPSTimer{}
		, m_FPS{}
	{
		if (startOnConstruct) Start();
	}

	void Time::Start()
	{
		m_Start = LBR_TIME_NOW;
		m_PrevTick = m_Start;
		m_TotalTime = 0;
		m_DeltaTime = 0;
		m_HasStarted = true;
	}

	void Time::Tick()
	{
		Timepoint now = LBR_TIME_NOW;
		double dt = std::chrono::duration<double>(now - m_PrevTick).count();

		m_DeltaTime = dt;
		m_TotalTime += dt;

		// Set FPS
		m_FPSTimer += dt;
		++m_FPSCounter;
		if (m_FPSTimer > 1) 
		{
			m_FPS = m_FPSCounter;
			m_FPSCounter = 0;
			m_FPSTimer = 0.0;
		}
		
		m_PrevTick = now;
	}


	double Time::Delta() const
	{
		if (!m_HasStarted) return 0.0;
		return m_DeltaTime;
	}
	double Time::Total() const
	{
		if (!m_HasStarted) return 0.0;
		return m_TotalTime;
	}

	uint32_t Time::FPS() const
	{
		if (!m_HasStarted) return 0;
		return m_FPS;
	}
}

