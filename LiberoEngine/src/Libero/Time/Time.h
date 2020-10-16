#pragma once
#include <chrono>
#include "Libero/Interfaces/ILocator.h"

namespace Libero
{
	class Time
	{
		using Timepoint = std::chrono::steady_clock::time_point;

	public:
		Time(bool startOnConstruct = false);
		void Start();

		double Delta() const;
		double Total() const;
		uint32_t FPS() const;

		void Tick();

	private:
		Timepoint m_Start;
		Timepoint m_PrevTick;

		double m_DeltaTime;
		double m_TotalTime;

		uint32_t m_FPS;
		uint32_t m_FPSCounter;
		double m_FPSTimer;

		bool m_HasStarted;
	};

	class TimeLocator : public ILocator<Time>
	{
	public:
		static double GetDeltaTime()
		{
			if (!m_pService) return 0.0;
			return m_pService->Delta();
		}
		static double GetTotalTime()
		{
			if (!m_pService) return 0.0;
			return m_pService->Total();
		}
		static double GetFPS()
		{
			if (!m_pService) return 0.0;
			return m_pService->FPS();
		}
	};
}


