#include "Liber_pch.h"
#include "ILibAllocator.h"

namespace Libero
{
	ILibAllocator::ILibAllocator(const size_t size, const void* pBase)
		: m_pBase{ pBase }
		, m_Size{ size }
	{
	}

	size_t ILibAllocator::GetMemorySize() const
	{
		return m_Size;
	}

	size_t ILibAllocator::GetUsedMemory() const
	{
		return m_MemoryUsed;
	}

	const void* ILibAllocator::GetBaseAdress() const
	{
		return m_pBase;
	}
}

