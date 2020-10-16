#pragma once
#include "../ECSDef.h"
#include "Libero/API.h"
#include <vector>

namespace Libero
{
	class IComponent;
	class IEntity
	{
	public:
		virtual ~IEntity() = default;
		virtual void Initialize() = 0;

		const EntityID GetID() const;
		virtual const ETypeID StatTypeID() const = 0;

		// Get component / Components
		template <class CType>
		CType* GetComponent();
		std::vector<IComponent*> GetComponents();

		// Add component
		template <class CType, class ...Args>
		CType* AddComponent(Args&...args); 
		template <class CType, class ...Args>
		CType* AddComponent(Args&&...args);
		template <class CType>
		CType* AddComponent();

		// Remove component
		template <class CType>
		bool RemoveComponent();

		virtual void OnEnable() {};
		virtual void OnDisable() {};
		void SetEnable(bool enable);
		bool IsEnabled() const;

	private:
		EntityID m_ID = gEntityID_Invalid;
		bool m_IsEnabled = true;
		friend class EntityMaster;

		std::vector<IComponent*> m_pComponents;

	public:
		bool operator==(const IEntity& other) const;
		bool operator!=(const IEntity& other) const;
		bool operator==(const IEntity* pOther) const;
		bool operator!=(const IEntity* pOther) const;
	};
}

#include "IEntity.inl"
