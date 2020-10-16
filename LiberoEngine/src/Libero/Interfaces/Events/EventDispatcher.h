#pragma once
#include <functional>
#include "IEvent.h"

namespace Libero
{
	// Calls the <void(IEvent&)> Function and automatically sets the event handled
#define LBR_EVDISP_FUNCBIND(Func) std::bind(&##Func, this, std::placeholders::_1)

	class EventDispatcher 
	{
		template <class E>
		using EventFunc = std::function<void(E&)>;
	public:
		EventDispatcher(IEvent& e) : m_Event{e}{}

		template <class E>
		bool Dispatch(EventFunc<E> func)
		{
			
			if (m_Event.IsHandled()) return false;
			if (E::GetStaticType() != m_Event.GetType()) return false;
			func(*(E*)&m_Event);
			return true;
		}

	private:
		IEvent& m_Event;
	}; 
}


