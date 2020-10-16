#pragma once
#include "IComponent.h"
#include "Libero/Misc/FamilyTypeID.h"

namespace Libero
{
	template <class Type>
	class Component : public IComponent
	{
	public:
		virtual ~Component() = default;
		virtual const CTypeID StatTypeID() const override;
		static const CTypeID m_Stat_TypeID;

	private:
		// Construction & deletion should happen in the EntityMaster
		void operator delete(void*) = delete;
		void operator delete[](void*) = delete;
	};

	template <class Type>
	const CTypeID Component<Type>::m_Stat_TypeID = FamilyTypeID<IComponent>::Create<Type>();
}

#include "Component.inl"