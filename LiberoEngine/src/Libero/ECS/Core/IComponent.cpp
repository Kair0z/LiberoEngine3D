#include "Liber_pch.h"
#include "IComponent.h"
#include "Libero/ECS/ECSMaster.h"

namespace Libero
{

	IEntity* IComponent::GetOwner() const
	{
		return ECSLocator::GetEntityMaster()->GetEntity(m_OwnerID);
	}

	EntityID IComponent::GetOwnerID() const
	{
		return m_OwnerID;
	}

	void IComponent::SetEnable(bool enable)
	{
		m_IsEnabled = enable;
	}
	bool IComponent::IsEnabled() const
	{
		return m_IsEnabled;
	}

	const bool IComponent::operator==(const IComponent& other) const
	{
		return !(*this != other);
	}

	const bool IComponent::operator!=(const IComponent& other) const
	{
		if (m_TypeID != other.m_TypeID) return true;
		if (m_OwnerID != other.m_OwnerID) return true;
		return false;
	}
}