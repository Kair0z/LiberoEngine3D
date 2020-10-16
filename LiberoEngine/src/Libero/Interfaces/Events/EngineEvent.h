#pragma once
#include "IEvent.h"

namespace Libero
{
	class EventQuit : public IEvent
	{
		LBR_E_DEFTYPE(EventType::EngineExit);
	};


	class EventGameStart : public IEvent
	{
		LBR_E_DEFTYPE(EventType::GameStart);
	};

	class EventGameStop : public IEvent
	{
		LBR_E_DEFTYPE(EventType::GameStop);
	};
}