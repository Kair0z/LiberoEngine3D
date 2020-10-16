#pragma once
#include "../ECSDef.h"

namespace Libero
{
	class IEntity;
	class IComponent
	{
	public:
		virtual ~IComponent() = default;
		virtual const CTypeID StatTypeID() const = 0;

		IEntity* GetOwner() const;
		EntityID GetOwnerID() const;

		void SetEnable(bool enable);
		bool IsEnabled() const;

		const bool operator==(const IComponent& other) const;
		const bool operator!=(const IComponent& other) const;

	private:
		friend class ComponentMaster;
		CTypeID m_TypeID;
		CompID m_ID;
		EntityID m_OwnerID;
		bool m_IsEnabled = true;
	};
}