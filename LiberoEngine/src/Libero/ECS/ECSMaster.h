#pragma once
#include "ECSDef.h"
#include "Libero/Interfaces/ILocator.h"

namespace Libero
{
	class IEntity;
	class EntityMaster;
	class ComponentMaster;
	class SystemMaster;
	class IEvent;

	class ECSMaster final
	{
	public:
		ECSMaster();
		~ECSMaster();

		void GameInitialize();
		void GameStart();
		void GameUpdate();
		void GameStop();
		void Render() const;

		void OnEvent(IEvent& e);

	private:
		EntityMaster* m_pEntityMaster;
		ComponentMaster* m_pComponentMaster;
		SystemMaster* m_pSystemMaster;

		friend class ECSLocator;
	};

	class IComponent;
	class ECSLocator final : public ILocator<ECSMaster>
	{
	public:
		static ComponentMaster* GetComponentMaster();
		static EntityMaster* GetEntityMaster();
		static SystemMaster* GetSystemMaster();

		// Entities:
		template <class Type, typename ...creationArgs> static Type* NewEntityAs(creationArgs&& ...params);
		template <class Type, typename ...creationArgs> static IEntity* NewEntity(creationArgs&& ...params);
		static void DestroyEntity(IEntity*& pEntity);

		// Components
		template <class CType, class ...Args> static CType* CreateComponent(const EntityID eID, Args&... args);
		template <class CType, class ...Args> static CType* CreateComponent(const EntityID eID, Args&&... args);
		template <class CType> static CType* CreateComponent(const EntityID id);
		template <class CType> static CType* GetComponent(const EntityID eID);
		static std::vector<IComponent*> GetComponents(const EntityID eID);
		template <class CType> static void RemoveComponent(const EntityID eID);
		static void RemoveAllComponents(const EntityID eID);

		// Systems:
		template <class Type, class ...Args>
		static Type* LoadSystem(Args&&... args);
	};
}

#include "ECSMaster.inl"
#include "ECSLocator.inl"


