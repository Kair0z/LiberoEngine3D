#pragma once
#include "../ECSDef.h"
#include "../Containers/ComponentContainer.h"

namespace Libero
{
	class IComponent;
	class ComponentMaster final
	{
		using ContainerMap = std::unordered_map<CTypeID, IComponentContainer*>;
		
	public:
		~ComponentMaster();
		void Initialize();

		template <class CType, class ...Args>
		CType* CreateComponent(const EntityID eID, Args&... args);
		template <class CType, class ...Args>
		CType* CreateComponent(const EntityID eID, Args&&... args);
		template <class CType>
		CType* CreateComponent(const EntityID eID);

		template <class CType>
		CType* GetComponent(const EntityID eID);
		std::vector<IComponent*> GetComponents(const EntityID eID);

		template <class CType>
		std::vector<CType*> GetComponentsOfType();

		template <class CType>
		void RemoveComponent(const EntityID eID);
		void RemoveAllComponents(const EntityID eID);

	public:
#pragma region ComponentIterator
		template <class CType>
		using ComponentIt = typename ComponentContainer<CType>::ChunkIterator;

		template <class CType>
		ComponentIt<CType> Begin();

		template <class CType>
		ComponentIt<CType> End();
#pragma endregion

	private:
		ContainerMap m_ContainerMap;
		std::vector<std::vector<CompID>> m_EntityComponentMap;
		std::vector<IComponent*> m_ComponentLookUp;
		bool m_IsInitialized = false;

	private:
		template <class Type>
		ComponentContainer<Type>* GetComponentContainer();
		
		CompID GenerateID(IComponent* pComp);
		void ReleaseID(CompID id);

		void MapComponentToEntity(const EntityID eID, const CompID cID, const CTypeID cTypeID);
		void UnMapComponentFromEntity(const EntityID eID, const CompID cID, const CTypeID cTypeID);
	};
}

#include "ComponentMaster.inl"

