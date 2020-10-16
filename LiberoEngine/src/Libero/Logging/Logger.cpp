#include "Liber_pch.h"
#include "Logger.h"

//******************************
// Logger Initialization
//******************************

namespace Libero
{
	Logger::Logger()
	{
		Initialize();
	}

	void Logger::Initialize()
	{
		m_Logbuffer.reserve(LBR_LOGBUFFER_INITSIZE);
		m_Backbuffer.reserve(LBR_LOGBUFFER_INITSIZE);
	}

	//*******************************
	// General Logging Functionality
	//*******************************

	void Logger::Log(LogType logType, const std::string& mssg)
	{
		std::string finalMessage;

		switch (logType)
		{
		case LogType::Error:
			finalMessage = "[ERROR:] ";
			break;

		case LogType::Warning:
			finalMessage = "[WARNING:] ";
			break;

		case LogType::Info:
			finalMessage = "[INFO:] ";
			break;
		}

		finalMessage += mssg;

		m_Logbuffer.push_back(finalMessage);
		m_Backbuffer.push_back(finalMessage);
	}

	void Logger::LogWarning(const std::string& mssg)
	{
		Log(LogType::Warning, mssg);
	}

	void Logger::LogError(const std::string& mssg)
	{
		Log(LogType::Error, mssg);
	}

	void Logger::LogInfo(const std::string& mssg)
	{
		Log(LogType::Info, mssg);
	}


	const std::vector<std::string>& Logger::GetLogBuffer() const
	{
		return m_Logbuffer;
	}

	void Logger::Clear()
	{
		m_Logbuffer.clear();
	}
}