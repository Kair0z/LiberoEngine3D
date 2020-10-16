#include "Liber_pch.h"
#include "SystemMaster.h"
#include "Libero/Memory/Allocators/LibLinearAllocator.h"
#include "Libero/Memory/MemoryMaster.h"
#include "Libero/ECS/Core/ISystem.h"

namespace Libero
{
	inline SystemMaster::SystemMaster()
	{
		size_t size = LBR_SYSTEM_MEMORY_SIZE;
		MemoryMaster& memMaster = MemoryMaster::Get();
		m_pAllocator = new LibLinearAllocator(size, memMaster.Allocate(size));
	}

	inline SystemMaster::~SystemMaster()
	{
		for (std::vector<ISystem*>::reverse_iterator it = m_pWorkingSystems.rbegin(); it != m_pWorkingSystems.rend(); ++it)
		{
			(*it)->~ISystem();
			*it = nullptr;
		}

		m_pWorkingSystems.clear();
		m_Systems.clear();

		// Free memory:
		MemoryMaster& mem = MemoryMaster::Get();
		mem.Free((void*)m_pAllocator->GetBaseAdress());
		
		delete m_pAllocator;
		m_pAllocator = nullptr;
	}
	
	inline void SystemMaster::Initialize()
	{
		m_IsInitialized = true;
	}

	inline void SystemMaster::InitializeSystems()
	{
		for (ISystem* pSys : m_pWorkingSystems)
		{
			pSys->Initialize();
		}
	}

	template<class SysType, class ...Args>
	inline SysType* SystemMaster::AddSystem(Args&& ...sysArgs)
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
		else assert(false);

		// Add to work order:
		m_pWorkingSystems.emplace_back(pSys);

		return pSys;
	}

	inline void SystemMaster::OnStart()
	{
		

		for (ISystem* pSys : m_pWorkingSystems)
		{
			if (pSys->m_IsEnabled) pSys->Start();
		}
	}

	inline void SystemMaster::OnUpdate()
	{
		float dt = 2.f;
		// PREUPDATE:
		for (ISystem* pSys : m_pWorkingSystems)
			if (pSys->m_IsEnabled && !pSys->m_IsAsleep) pSys->PreUpdate();

		for (ISystem* pSys : m_pWorkingSystems)
		{
			// Inc time since last update:
			pSys->m_TimeSinceUpdate += dt;

			// If exceed:
			bool isIntvExceeded = (pSys->m_UpdateIntv > 0.f) && (pSys->m_TimeSinceUpdate > pSys->m_UpdateIntv);
			pSys->m_IsAsleep = !((pSys->m_UpdateIntv < 0.f) || isIntvExceeded);
		
			if (!pSys->m_IsAsleep && pSys->m_IsEnabled)
			{
				pSys->Update();
				pSys->m_TimeSinceUpdate = 0.f;
			}
		}
	
		for (ISystem* pSys : m_pWorkingSystems)
			if (pSys->m_IsEnabled) pSys->PostUpdate();
	}

	inline void SystemMaster::OnStop()
	{
		// Do nothing for now...
	}

	inline void SystemMaster::OnEvent(IEvent& e)
	{
		for (ISystem* pSys : m_pWorkingSystems)
			if (pSys->m_IsEnabled) pSys->OnEvent(e);
	}

	inline void SystemMaster::OnRender() const
	{
		for (ISystem* pSys : m_pWorkingSystems)
			if (pSys->m_IsEnabled) pSys->Render();

		for (ISystem* pSys : m_pWorkingSystems)
			if (pSys->m_IsEnabled) pSys->PostRender();
	}
}