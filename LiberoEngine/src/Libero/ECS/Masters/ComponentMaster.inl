#include "Liber_pch.h"
#include "ComponentMaster.h"
#include "../Core/IComponent.h"
#include "Libero/Misc/FamilyTypeID.h"

namespace Libero
{
	inline ComponentMaster::~ComponentMaster()
	{
		for (auto container : m_ContainerMap)
		{
			delete container.second;
			container.second = nullptr;
		}
	}

	inline void ComponentMaster::Initialize()
	{
		m_IsInitialized = true;
	}

	template<class CType, class ...Args>
	inline CType* ComponentMaster::CreateComponent(const EntityID eID, Args&...args)
	{
		const CTypeID cTypeID = CType::m_Stat_TypeID;

		// Retrieve memory for object:
		void* pObjMem = GetComponentContainer<CType>()->CreateObj();

		// Create ID:
		CompID cID = GenerateID((CType*)pObjMem);

		// Create the object:
		IComponent* pComponent = new (pObjMem)CType(std::forward<Args&>(args)...);
		pComponent->m_OwnerID = eID;
		pComponent->m_ID = cID;

		// Map the componentID to the entityID
		MapComponentToEntity(eID, cID, cTypeID);

		return (CType*)pComponent;
	}

	template<class CType, class ...Args>
	inline CType* ComponentMaster::CreateComponent(const EntityID eID, Args&& ...args)
	{
		const CTypeID cTypeID = CType::m_Stat_TypeID;

		// Retrieve memory for object:
		void* pObjMem = GetComponentContainer<CType>()->CreateObj();

		// Create ID:
		CompID cID = GenerateID((CType*)pObjMem);

		// Create the object:
		IComponent* pComponent = new (pObjMem)CType(std::forward<Args&&>(args)...);
		pComponent->m_OwnerID = eID;
		pComponent->m_ID = cID;

		// Map the componentID to the entityID
		MapComponentToEntity(eID, cID, cTypeID);

		return (CType*)pComponent;
	}

	template <class CType>
	inline CType* ComponentMaster::CreateComponent(const EntityID eID)
	{
		const CTypeID cTypeID = CType::m_Stat_TypeID;

		// Memory:
		void* pObjMem = GetComponentContainer<CType>()->CreateObj();

		// ID:
		CompID cID = GenerateID((CType*)pObjMem);

		// Create the obj:
		IComponent* pComponent = new (pObjMem)CType();
		pComponent->m_OwnerID = eID;
		pComponent->m_ID = cID;

		// Map:
		MapComponentToEntity(eID, cID, cTypeID);

		return (CType*)pComponent;
	}

	inline std::vector<IComponent*> ComponentMaster::GetComponents(const EntityID eID)
	{
		std::vector<IComponent*> components;
		for (CompID cID : m_EntityComponentMap[eID.m_Idx])
		{
			if (cID == gComponentID_Invalid) continue;
			IComponent* pComp = m_ComponentLookUp[cID];
			if (pComp) components.push_back(pComp);
		}
		
		return components;
	}

	inline void ComponentMaster::RemoveAllComponents(const EntityID eID)
	{
		static const size_t nrComp = m_EntityComponentMap[0].size();

		for (CTypeID cTypeID{}; cTypeID < nrComp; ++cTypeID)
		{
			const CompID cID = m_EntityComponentMap[eID.m_Idx][cTypeID];
			if (cID == gComponentID_Invalid) continue;

			IComponent* pComp = m_ComponentLookUp[cID];
			if (!pComp) continue;

			// Get Container:
			auto it = m_ContainerMap.find(cTypeID);
			if (it != m_ContainerMap.end()) it->second->DestroyComponent(pComp);

			UnMapComponentFromEntity(eID, cID, cTypeID);
		}
	}

	template<class CType>
	inline CType* ComponentMaster::GetComponent(const EntityID eID)
	{
		const CTypeID cTypeID = CType::m_Stat_TypeID;
		const CompID cID = m_EntityComponentMap[eID.m_Idx][cTypeID];

		if (cID == gComponentID_Invalid) return nullptr;

		return (CType*)m_ComponentLookUp[cID];
	}

	template<class CType>
	inline std::vector<CType*> ComponentMaster::GetComponentsOfType()
	{
		const CTypeID cTypeID = CType::m_Stat_TypeID;

		std::vector<CType*> res;
		res.reserve(1024);

		for (auto it = Begin<CType>(); it != End<CType>(); ++it)
			res.push_back(*it);

		return res;
	}

	template<class CType>
	inline void ComponentMaster::RemoveComponent(const EntityID eID)
	{
		const CTypeID cTypeID = CType::m_Stat_TypeID;
		const CompID cID = m_EntityComponentMap[eID.m_Idx][cTypeID];

		// Find object in lookup:
		IComponent* pComp = m_ComponentLookUp[cID];
		assert(pComp);

		// Destroy object:
		GetComponentContainer<CType>()->DestroyComponent(pComp);

		// Unmap
		UnMapComponentFromEntity(eID, cID, cTypeID);
	}

	template<class CType>
	inline ComponentMaster::ComponentIt<CType> ComponentMaster::Begin()
	{
		return GetComponentContainer<CType>()->Begin();
	}

	template<class CType>
	inline ComponentMaster::ComponentIt<CType> ComponentMaster::End()
	{
		return GetComponentContainer<CType>()->End();
	}

	template<class Type>
	inline ComponentContainer<Type>* ComponentMaster::GetComponentContainer()
	{
		CTypeID typeID = Type::m_Stat_TypeID;
		
		auto it = m_ContainerMap.find(typeID);
		ComponentContainer<Type>* pContainer = nullptr;

		if (it == m_ContainerMap.end())
		{
			pContainer = new ComponentContainer<Type>();
			m_ContainerMap[typeID] = pContainer;
		}
		else pContainer = (ComponentContainer<Type>*)it->second;

		return pContainer;
	}





#pragma region IDHandling
	inline CompID ComponentMaster::GenerateID(IComponent* pComp)
	{
		size_t i{};

		// Find first element in LUT that's nullptr,
		// Put the component in there:

		for (; i < m_ComponentLookUp.size(); ++i)
		{
			if (m_ComponentLookUp[i] == nullptr)
			{
				m_ComponentLookUp[i] = pComp;
				return CompID(i);
			}
		}

		// If component lookup is out of size, 
	    // resize with nullptr's
		m_ComponentLookUp.resize(m_ComponentLookUp.size() + LBR_COMPONENT_LUTGROW, nullptr);
		m_ComponentLookUp[i] = pComp;

		return CompID(i);
	}

	inline void ComponentMaster::ReleaseID(CompID id)
	{
		assert((id != gComponentID_Invalid && id < m_ComponentLookUp.size()));
		m_ComponentLookUp[id] = nullptr;
	}

	inline void ComponentMaster::MapComponentToEntity(const EntityID eID, const CompID cID, const CTypeID cTypeID)
	{
		static const size_t nrComp = FamilyTypeID<IComponent>::GetCount();

		if (eID.m_Idx >= m_EntityComponentMap.size())
		{
			// if entity is not registered yet:
			// grow the map:
			size_t oldSize = m_EntityComponentMap.size();
			size_t newSize = oldSize + LBR_ENTITY_LUTGROW;

			// Fill the new Entity ID's with invalidcomponentIDS:
			m_EntityComponentMap.resize(newSize);
			for (auto i{ oldSize }; i < newSize; ++i)
				m_EntityComponentMap[i].resize(nrComp, gComponentID_Invalid);
		}

		m_EntityComponentMap[eID.m_Idx][cTypeID] = cID;
	}

	inline void ComponentMaster::UnMapComponentFromEntity(const EntityID eID, const CompID cID, const CTypeID cTypeID)
	{
		assert(m_EntityComponentMap[eID.m_Idx][cTypeID] == cID);

		// Unmap:
		m_EntityComponentMap[eID.m_Idx][cTypeID] = gComponentID_Invalid;
		
		// Release the id
		ReleaseID(cID);
	}
#pragma endregion
}