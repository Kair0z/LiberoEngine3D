#pragma once
#include "Libero/Interfaces/ILocator.h"
#include <string>

#include <iostream>
#include <fstream>
#include <vector>

//*************************************************************
// Logger (Credits to The Overlord Engine)
//*************************************************************

#define LBR_LOGBUFFER_INITSIZE 10000

namespace Libero
{
	class Logger
	{
	public:
		enum class LogType
		{
			Info,
			Warning,
			Error
		};

	public:
		Logger();

		// * General Logging functions *
		void Log(LogType, const std::string& mssg);
		void LogInfo(const std::string& mssg);
		void LogWarning(const std::string& mssg);
		void LogError(const std::string& mssg);

		void ExplicitConsoleLog(LogType logType, const std::string& mssg);

		// * File Logging *
		void StartFileLogging(const std::string& filepath);
		void StopFileLogging();

		// Get buffer
		const std::vector<std::string>& GetLogBuffer() const;
		void Clear();

	private:
		void Initialize();

		std::vector<std::string> m_Logbuffer; // Current log report
		std::vector<std::string> m_Backbuffer; // Total log report
	};

	class LoggerLocator final : public ILocator<Logger>{};
}


