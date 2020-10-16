#pragma once

// Family = Basetype
// The create function counts up everytime it get's called with the DerivType

template <class BaseType>
class FamilyTypeID
{
public:
	template <class DerivType>
	static const unsigned int Create();
	static const unsigned int GetCount();

private:
	static unsigned int m_Stat_TypeCount;
};

template<class BaseType>
template<class DerivType>
inline const unsigned int FamilyTypeID<BaseType>::Create()
{
	static const unsigned int val = m_Stat_TypeCount++;
	return val;
}

template<class BaseType>
inline const unsigned int FamilyTypeID<BaseType>::GetCount()
{
	return m_Stat_TypeCount;
}

#include "Libero/ECS/Core/IComponent.h"
#include "Libero/ECS/Core/IEntity.h"
#include "Libero/ECS/Core/ISystem.h"

unsigned int FamilyTypeID<Libero::IEntity>::m_Stat_TypeCount = 1;
template class FamilyTypeID<Libero::IEntity>;

unsigned int FamilyTypeID<Libero::IComponent>::m_Stat_TypeCount = 1;
template class FamilyTypeID<Libero::IComponent>;

unsigned int FamilyTypeID<Libero::ISystem>::m_Stat_TypeCount = 1;
template class FamilyTypeID<Libero::ISystem>;