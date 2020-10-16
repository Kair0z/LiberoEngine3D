#pragma once
#include "ISystem.h"
#include "Libero/Misc/FamilyTypeID.h"

namespace Libero
{
	template <class Type>
	class System : public ISystem
	{
	public:
		virtual ~System() = default;
		virtual const SysTypeID StatTypeID() const override { return m_Stat_TypeID; };
		static const SysTypeID m_Stat_TypeID;

	private:
		// Construction & deletion should happen in the EntityMaster
		void operator delete(void*) = delete;
		void operator delete[](void*) = delete;
	};

	template <class Type>
	const SysTypeID System<Type>::m_Stat_TypeID = FamilyTypeID<ISystem>::Create<Type>();
}

#include "System.inl"
