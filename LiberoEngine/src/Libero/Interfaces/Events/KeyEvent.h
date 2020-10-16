#pragma once
#include "IEvent.h"

namespace Libero
{
	class EventKeyUp : public IEvent
	{
	public:
		EventKeyUp(WPARAM wParam) : m_Param{wParam}{}
		LBR_E_DEFTYPE(EventType::KeyUp);

		WPARAM GetParam() const { return m_Param; };

	private:
		WPARAM m_Param;
	};

	class EventKeyDown : public IEvent
	{
	public:
		EventKeyDown(WPARAM wParam) : m_Param{wParam}{}
		LBR_E_DEFTYPE(EventType::KeyDown);

		WPARAM GetParam() const { return m_Param; };
	private:
		WPARAM m_Param;
	};
}