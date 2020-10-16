#include "Liber_pch.h"
#include "ECSMaster.h"

#define INVALID_SERVICE(service) (!service || !service->m_IsInitialized)

namespace Libero
{

	template<class Type, typename ...creationArgs>
	inline Type* ECSLocator::NewEntityAs(creationArgs&& ...params)
	{
		if (INVALID_SERVICE(m_pService)) return nullptr;

		return static_cast<Type*>(ECSLocator::NewEntity<Type, creationArgs...>(params...));
	}

	inline ComponentMaster* ECSLocator::GetComponentMaster()
	{
		if (!m_pService) return nullptr;
		return m_pService->m_pComponentMaster;
	}

	inline EntityMaster* ECSLocator::GetEntityMaster()
	{
		if (!m_pService) return nullptr;
		return m_pService->m_pEntityMaster;
	}

	inline SystemMaster* ECSLocator::GetSystemMaster()
	{
		if (!m_pService) return nullptr;
		return m_pService->m_pSystemMaster;
	}

	inline void ECSLocator::DestroyEntity(IEntity*& pEntity)
	{
		if (INVALID_SERVICE(m_pService)) return;

		// Destroy the entity and remove the components
		m_pService->m_pEntityMaster->DestroyEntity(pEntity->GetID(), true);
		m_pService->m_pComponentMaster->RemoveAllComponents(pEntity->GetID());

		pEntity = nullptr;
	}

	inline std::vector<IComponent*> ECSLocator::GetComponents(const EntityID eID)
	{
		if (INVALID_SERVICE(m_pService)) return {};

		return m_pService->m_pComponentMaster->GetComponents(eID);
	}

	inline void ECSLocator::RemoveAllComponents(const EntityID eID)
	{
		if (INVALID_SERVICE(m_pService)) return;

		m_pService->m_pComponentMaster->RemoveAllComponents(eID);
	}

	template<class Type, typename ...creationArgs>
	inline IEntity* ECSLocator::NewEntity(creationArgs&& ...params)
	{
		if (INVALID_SERVICE(m_pService)) return nullptr;

		EntityID id = m_pService->m_pEntityMaster->CreateEntity<Type, creationArgs...>(params...);

		if (id == id.INVALID) return nullptr;
		else return m_pService->m_pEntityMaster->GetEntity(id);
	}

	template<class CType, class ...Args>
	inline CType* ECSLocator::CreateComponent(const EntityID eID, Args&...args)
	{
		if (INVALID_SERVICE(m_pService)) return nullptr;

		return m_pService->m_pComponentMaster->CreateComponent<CType, Args&...>(eID, args...);
	}

	template<class CType, class ...Args>
	inline CType* ECSLocator::CreateComponent(const EntityID eID, Args&& ...args)
	{
		if (INVALID_SERVICE(m_pService)) return nullptr;

		return m_pService->m_pComponentMaster->CreateComponent<CType, Args&&...>(eID, args...);
	}

	template <class CType> 
	static CType* ECSLocator::CreateComponent(const EntityID eID)
	{
		if (INVALID_SERVICE(m_pService)) return nullptr;

		return m_pService->m_pComponentMaster->CreateComponent<CType>(eID);
	}

	template<class CType>
	inline CType* ECSLocator::GetComponent(const EntityID eID)
	{
		if (INVALID_SERVICE(m_pService)) return nullptr;

		return m_pService->m_pComponentMaster->GetComponent<CType>(eID);
	}

	template<class CType>
	inline void ECSLocator::RemoveComponent(const EntityID eID)
	{
		if (INVALID_SERVICE(m_pService)) return;

		m_pService->m_pComponentMaster->RemoveComponent<CType>(eID);
	}

	template<class Type, class ...Args>
	inline Type* ECSLocator::LoadSystem(Args&& ...args)
	{
		if (INVALID_SERVICE(m_pService)) return nullptr;
		return m_pService->m_pSystemMaster->AddSystem<Type, Args...>(args...);
	}
}

#ifdef INVALID_SERVICE
#undef INVALID_SERVICE
#endif