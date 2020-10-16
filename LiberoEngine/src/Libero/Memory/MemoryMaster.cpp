#include "Liber_pch.h"
#include "MemoryMaster.h"
#include "Allocators/LibAllocators.h"

namespace Libero
{
	MemoryMaster::MemoryMaster()
		: m_pMainAlloc{nullptr}
		, m_IsInitialized{false}
		, m_pMemoryBase{nullptr}
	{
		Initialize();
	}

	MemoryMaster::~MemoryMaster()
	{
		m_pMainAlloc->Clear();

		delete m_pMainAlloc;
		m_pMainAlloc = nullptr;
		
		free(m_pMemoryBase);
		m_pMemoryBase = nullptr;
	}

	void* MemoryMaster::Allocate(const size_t size)
	{
		if (!m_IsInitialized) return nullptr;

		void* pMem = m_pMainAlloc->Allocate(size);
		return pMem;
	}

	void MemoryMaster::Free(void* pMem)
	{
		if (!m_IsInitialized) return;

		m_pMainAlloc->Free(pMem);
	}

	void MemoryMaster::Initialize()
	{
		size_t c = LBR_MEMORY_CAPACITY;
		m_pMemoryBase = malloc(c);
		m_pMainAlloc = new LibStackAllocator(c, m_pMemoryBase);

		m_IsInitialized = true;
	}
}

