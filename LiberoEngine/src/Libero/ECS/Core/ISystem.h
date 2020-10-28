#pragma once
#include <functional>
#include "../ECSDef.h"
#include "Libero/Interfaces/Events/IEvent.h"

namespace Libero
{
	class IEvent;
	class ISystem
	{
	public:
		inline virtual void Initialize() {};
		inline virtual void Start() {};
		inline virtual void PreUpdate() {};
		inline virtual void Update() {};
		inline virtual void FixedUpdate() {};
		inline virtual void PostUpdate() {};

		inline virtual void Render() const {};
		inline virtual void PostRender() const {};
		inline virtual void OnEvent(IEvent&) {};

		virtual const SysTypeID StatTypeID() const = 0;

	private:
		float m_TimeSinceUpdate = 0.f;
		float m_UpdateIntv = 0.001f;

		bool m_IsEnabled = true;
		// Sleeping systems don't update:
		bool m_IsAsleep = false;

		friend class SystemMaster;

	protected:
		// For each component:
		template <class CompType, typename Op = std::function<void(CompType*)>>
		void ForEachComponent(Op op);

		template <class CompType, typename Op = std::function<void(CompType*)>>
		void ForEachComponent(Op op) const;
	};
}

#include "ISystem.inl"
