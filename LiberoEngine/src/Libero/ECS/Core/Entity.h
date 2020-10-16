#pragma once
#include "IEntity.h"
#include "Libero/Misc/FamilyTypeID.h"

namespace Libero
{
	template <class Type>
	class Entity : public IEntity
	{
	public:
		virtual ~Entity() = default;
		virtual const ETypeID StatTypeID() const override;
		static const ETypeID m_Stat_TypeID;

	private:
		// Construction & deletion should happen in the EntityMaster
		void operator delete(void*) = delete;
		void operator delete[](void*) = delete;
	};

	template <class Type>
	const ETypeID Entity<Type>::m_Stat_TypeID = FamilyTypeID<IEntity>::Create<Type>();
}

#include "Entity.inl"


