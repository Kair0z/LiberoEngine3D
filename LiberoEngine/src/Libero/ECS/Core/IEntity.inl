#include "Liber_pch.h"
#include "IEntity.h"
#include "Libero/ECS/ECSMaster.h"
#include "Libero/Interfaces/Events/IEvent.h"
#include "IComponent.h"

namespace Libero
{
	inline const EntityID IEntity::GetID() const
	{
		return m_ID;
	}

	inline std::vector<IComponent*> IEntity::GetComponents()
	{
		return m_pComponents;
	}

	// Components:
	template<class CType>
	inline CType* IEntity::GetComponent()
	{
		return ECSLocator::GetComponent<CType>(m_ID);
	}

	template<class CType, class ...Args>
	inline CType* IEntity::AddComponent(Args&... args)
	{
		CType* pComponent = ECSLocator::CreateComponent<CType, Args...>(m_ID, args...);
		if (pComponent) m_pComponents.push_back(pComponent);

		return pComponent;
	}

	template<class CType, class ...Args>
	inline CType* IEntity::AddComponent(Args&&... args)
	{
		CType* pComponent = ECSLocator::CreateComponent<CType, Args...>(m_ID, args...);
		if (pComponent) m_pComponents.push_back(pComponent);

		return pComponent;
	}

	template <class CType>
	inline CType* IEntity::AddComponent()
	{
		CType* pComponent = ECSLocator::CreateComponent<CType>(m_ID);
		if (pComponent) m_pComponents.push_back(pComponent);

		return pComponent;
	}

	template<class CType>
	inline bool IEntity::RemoveComponent()
	{
		ECSLocator::RemoveComponent<CType>(m_ID);
		return true;
	}

	// Enabling
	inline void IEntity::SetEnable(bool enable)
	{
		if (m_IsEnabled == enable) return;
		m_IsEnabled = enable;

		if (!enable) OnDisable();
		else OnEnable();
	}

	inline bool IEntity::IsEnabled() const
	{
		return m_IsEnabled;
	}

#pragma region EntityComp
	inline bool IEntity::operator==(const IEntity& other) const
	{
		return m_ID == other.m_ID;
	}

	inline bool IEntity::operator==(const IEntity* pOther) const
	{
		return m_ID == pOther->m_ID;
	}

	inline bool IEntity::operator!=(const IEntity& other) const
	{
		return !(*this == other);
	}

	inline bool IEntity::operator!=(const IEntity* pOther) const
	{
		return !(this == pOther);
	}
#pragma endregion
}