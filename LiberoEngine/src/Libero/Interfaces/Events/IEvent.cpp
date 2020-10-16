#include "Liber_pch.h"
#include "IEvent.h"

namespace Libero
{
	bool IEvent::IsHandled() const
	{
		return m_IsHandled;
	}
	void IEvent::SetHandled(bool handled)
	{
		m_IsHandled = handled;
	}
}

