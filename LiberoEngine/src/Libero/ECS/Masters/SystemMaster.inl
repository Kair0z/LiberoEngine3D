#include "Liber_pch.h"
#include "SystemMaster.h"
#include "Libero/Memory/Allocators/LibLinearAllocator.h"
#include "Libero/Memory/MemoryMaster.h"
#include "Libero/ECS/Core/ISystem.h"
#include "Libero/Time/Time.h"

namespace Libero
{
	inline SystemMaster::SystemMaster()
	{
		// Setup the Linear allocator for storing systems
		size_t size = LBR_SYSTEM_MEMORY_SIZE;
		MemoryMaster& memMaster = MemoryMaster::Get();
		m_pAllocator = new LibLinearAllocator(size, memMaster.Allocate(size));
	}

	inline SystemMaster::~SystemMaster()
	{
		for (std::vector<ISystem*>::reverse_iterator it = m_pSystems.rbegin(); it != m_pSystems.rend(); ++it)
		{
			(*it)->~ISystem();
			*it = nullptr;
		}

		m_pSystems.clear();
		m_Systems.clear();

		// Free memory:
		MemoryMaster& mem = MemoryMaster::Get();
		mem.Free((void*)m_pAllocator->GetBaseAdress());
		
		delete m_pAllocator;
		m_pAllocator = nullptr;
	}
	

	inline void SystemMaster::InitializeSystems()
	{
		for (ISystem* pSys : m_pSystems)
		{
			pSys->Initialize();
		}
	}

	template<class SysType, class ...Args>
	inline SysType* SystemMaster::AddSystem(Args... sysArgs)
	{
		const SysTypeID typeID = SysType::m_Stat_TypeID;
		auto it = m_Systems.find(typeID);

		// if the system exists already:
		// return the existing system:
		if (it != m_Systems.end() && it->second != nullptr) return (SysType*)it->second;

		SysType* pSys{ nullptr };

		void* pSysMem = m_pAllocator->Allocate(sizeof(SysType));
		if (pSysMem)
		{
			// Create system:
			pSys = new (pSysMem)SysType(std::forward<Args>(sysArgs)...);

			// Map:
			m_Systems[typeID] = pSys;
		}
		else assert(false); // Out of system memory...

		// Add to work order:
		m_pSystems.emplace_back(pSys);

		return pSys;
	}



	// *************************************************************************
	//  FUNCTIONALITY:
	// *************************************************************************

	inline void SystemMaster::OnStart()
	{
		for (ISystem* pSys : m_pSystems)
			if (pSys->m_IsEnabled) pSys->Start();
	}
	inline void SystemMaster::OnUpdate()
	{
		// PREUPDATE:
		for (ISystem* pSys : m_pSystems)
			if (pSys->m_IsEnabled && !pSys->m_IsAsleep) pSys->PreUpdate();

		// UPDATE:
		for (ISystem* pSys : m_pSystems)
			if (pSys->m_IsEnabled) pSys->Update();

		// FIXED UPDATE:
		for (ISystem* pSys : m_pSystems)
		{
			// Inc time since last update:
			pSys->m_TimeSinceUpdate += (float)TimeLocator::GetDeltaTime();

			// Check if exceed:
			bool isIntvExceeded = (pSys->m_UpdateIntv > 0.f) && (pSys->m_TimeSinceUpdate > pSys->m_UpdateIntv);

			// System is asleep and won't update if updateintv < 0.0f || the intv is not exceeded.
			pSys->m_IsAsleep = (pSys->m_UpdateIntv < 0.f || !isIntvExceeded);
		
			if (!pSys->m_IsAsleep && pSys->m_IsEnabled)
			{
				pSys->FixedUpdate();
				pSys->m_TimeSinceUpdate = 0.f;
			}
		}
	
		// POSTUPDATE:
		for (ISystem* pSys : m_pSystems)
			if (pSys->m_IsEnabled) pSys->PostUpdate();
	}
	inline void SystemMaster::OnStop()
	{
		// Do nothing for now...
	}
	inline void SystemMaster::OnEvent(IEvent& e)
	{
		for (ISystem* pSys : m_pSystems)
			if (pSys->m_IsEnabled) pSys->OnEvent(e);
	}
	inline void SystemMaster::OnRender() const
	{
		for (ISystem* pSys : m_pSystems)
			if (pSys->m_IsEnabled) pSys->Render();

		for (ISystem* pSys : m_pSystems)
			if (pSys->m_IsEnabled) pSys->PostRender();
	}
}