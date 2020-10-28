#pragma once
#include "Liber_pch.h"
#include "ECSMaster.h"
#include "Masters/Masters.h"

namespace Libero
{
	inline ECSMaster::ECSMaster()
	{
		m_pEntityMaster = new EntityMaster();
		m_pComponentMaster = new ComponentMaster();
		m_pSystemMaster = new SystemMaster();
	}

	inline ECSMaster::~ECSMaster()
	{
		SafeDelete(m_pSystemMaster);
		SafeDelete(m_pEntityMaster);
		SafeDelete(m_pComponentMaster);
	}


	inline void ECSMaster::GameInitialize()
	{
		m_pSystemMaster->InitializeSystems();
	}

	inline void ECSMaster::GameStart()
	{
		m_pSystemMaster->OnStart();
	}

	inline void ECSMaster::GameUpdate()
	{
		m_pSystemMaster->OnUpdate();
	}

	inline void ECSMaster::GameStop()
	{
		m_pSystemMaster->OnStop();
	}

	inline void ECSMaster::Render() const
	{
		m_pSystemMaster->OnRender();
	}

	inline void ECSMaster::OnEvent(IEvent& e)
	{
		m_pSystemMaster->OnEvent(e);
	}
}