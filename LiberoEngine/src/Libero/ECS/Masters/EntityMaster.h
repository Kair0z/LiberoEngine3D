#pragma once
#include "../ECSDef.h"
#include "../Containers/EntityContainer.h"

namespace Libero
{
	class IEntity;
	class EntityMaster final
	{
		using ContainerMap = std::unordered_map<ETypeID, IEntityContainer*>; // Store entities per container per eTypeID
		using EntityHandleTable = HandleTable<IEntity, Handle64>;

	public:
		~EntityMaster();

		template <class EType, typename... creationArgs>
		EntityID CreateEntity(creationArgs... params);

		IEntity* GetEntity(const EntityID id);
		void DestroyEntity(const EntityID id, bool immediate);

	private:
		ContainerMap m_ContainerMap;
		EntityHandleTable m_HandleTable;

	private:
		template <class EType>
		EntityContainer<EType>* GetEntityContainer();
	};
}

#include "EntityMaster.inl"
