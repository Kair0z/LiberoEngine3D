#pragma once
#include "Liber_pch.h"
#include "ECSMaster.h"
#include "Masters/Masters.h"

namespace Libero
{
	inline ECSMaster::ECSMaster()
		: m_pComponentMaster{nullptr}
		, m_pEntityMaster{nullptr}
		, m_pSystemMaster{nullptr}
		, m_IsInitialized{false}
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

	inline void ECSMaster::Initialize()
	{
		m_pSystemMaster->Initialize();
		m_pEntityMaster->Initialize();
		m_pComponentMaster->Initialize();

		m_IsInitialized = true;
	}

	inline void ECSMaster::GameInitialize()
	{
		if (!m_IsInitialized) return;

		m_pSystemMaster->InitializeSystems();
	}

	inline void ECSMaster::GameStart()
	{
		if (!m_IsInitialized) return;

		m_pSystemMaster->OnStart();
	}

	inline void ECSMaster::GameUpdate()
	{
		if (!m_IsInitialized) return;

		m_pSystemMaster->OnUpdate();
	}

	inline void ECSMaster::GameStop()
	{
		if (!m_IsInitialized) return;

		m_pSystemMaster->OnStop();
	}

	inline void ECSMaster::Render() const
	{
		if (!m_IsInitialized) return;
		
		m_pSystemMaster->OnRender();
	}

	inline void ECSMaster::OnEvent(IEvent& e)
	{
		m_pSystemMaster->OnEvent(e);
	}
}