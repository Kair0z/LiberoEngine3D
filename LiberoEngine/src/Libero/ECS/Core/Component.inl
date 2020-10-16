#include "Liber_pch.h"
#include "Component.h"

namespace Libero
{
	template<class Type>
	inline const CTypeID Component<Type>::StatTypeID() const
	{
		return m_Stat_TypeID;
	}
}