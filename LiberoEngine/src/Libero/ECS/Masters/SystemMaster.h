#pragma once
#include <vector>
#include <unordered_map>
#include "../ECSDef.h"

namespace Libero
{
	class ISystem;
	class LibLinearAllocator;
	class IEvent;
	class SystemMaster final 
	{
		using SystemMap = std::unordered_map<SysTypeID, ISystem*>;

	public:
		SystemMaster();
		~SystemMaster();

		void InitializeSystems();

		void OnStart();
		void OnUpdate();
		void OnStop();
		void OnEvent(IEvent& e);
		void OnRender() const;

		template <class SysType, class... Args>
		SysType* AddSystem(Args... sysArgs);

	private:
		SystemMap m_Systems;
		std::vector<ISystem*> m_pSystems;
		LibLinearAllocator* m_pAllocator = nullptr;
	};
}

#include "SystemMaster.inl"

