#pragma once
#include "Libero/Misc/Singleton.h"

#define LBR_MEMORY_CAPACITY 134217728 * 2

namespace Libero
{
	class LibStackAllocator;
	class MemoryMaster final : public Singleton<MemoryMaster>
	{
	public:
		MemoryMaster();
		~MemoryMaster();

		void* Allocate(const size_t size);
		void Free(void* pMem);

	private:
		void Initialize();

		LibStackAllocator* m_pMainAlloc;
		void* m_pMemoryBase;
		bool m_IsInitialized;
	};
}


