#include "Liber_pch.h"
#include "EntityMaster.h"
#include "../Core/Entity.h"

namespace Libero
{
	inline EntityMaster::~EntityMaster()
	{
		for (auto container : m_ContainerMap)
		{
			delete container.second;
			container.second = nullptr;
		}
	}


	template<class EType, typename ...creationArgs>
	inline EntityID EntityMaster::CreateEntity(creationArgs... params)
	{
		// Get Container:
		// If it doesn't exist, it'll create a new one internally:
		void* pObjMem = GetEntityContainer<EType>()->CreateObj();

		// Create object:
		IEntity* pEntity = new (pObjMem)EType(std::forward<creationArgs>(params)...);

		// Create Unique ID:
		pEntity->m_ID = m_HandleTable.AcquireHandle((EType*)pObjMem);

		// Initialize:
		pEntity->Initialize();

		return pEntity->m_ID;
	}

	inline void EntityMaster::DestroyEntity(const EntityID id, bool)
	{
		IEntity* pEntity = GetEntity(id);
		const ETypeID typeID = pEntity->StatTypeID();

		// Find the container of the EntityType
		auto it = m_ContainerMap.find(typeID);
		if (it != m_ContainerMap.end())
		{
			// Destroy the entity out of the container
			it->second->DestroyEntity(pEntity);
		}

		m_HandleTable.ReleaseHandle(id);
	}



	template<class EType>
	inline EntityContainer<EType>* EntityMaster::GetEntityContainer()
	{
		ETypeID typeID = EType::m_Stat_TypeID;
		auto it = m_ContainerMap.find(typeID);

		EntityContainer<EType>* pContainer = nullptr;
		if (it == m_ContainerMap.end())
		{
			// If the container with this type doesn't exit yet, create a new one:
			pContainer = new EntityContainer<EType>();
			m_ContainerMap[typeID] = pContainer;
		}
		else pContainer = (EntityContainer<EType>*)it->second;

		return pContainer;
	}

	inline IEntity* EntityMaster::GetEntity(const EntityID id)
	{
		return m_HandleTable[id];
	}
}