#include "Liber_pch.h"
#include "Entity.h"

namespace Libero
{
	template<class Type>
	inline const ETypeID Entity<Type>::StatTypeID() const
	{
		return m_Stat_TypeID;
	}
}