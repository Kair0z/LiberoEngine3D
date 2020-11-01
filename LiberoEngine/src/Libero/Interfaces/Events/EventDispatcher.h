#pragma once
#include <functional>
#include "IEvent.h"

namespace Libero
{
	// ** Catches events and directs them based on type to a given function
	class EventCatch final
	{
		template <class E>
		using ECatchFunc = std::function<void(E&)>;
	public:
		EventCatch(IEvent& e) : m_Event{e}{}

		template <class E>
		bool Catch(ECatchFunc<E> func, bool autoHandle = false)
		{
			if (m_Event.IsHandled()) return false;
			if (E::GetStaticType() != m_Event.GetType()) return false;

			// Use function on event
			func(*(E*)&m_Event);
			m_Event.SetHandled(autoHandle);

			return true;
		}

	private:
		IEvent& m_Event;
	}; 
}


