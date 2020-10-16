#include "Liber_pch.h"
#include "LibChunkAllocator.h"

namespace Libero
{
	template<class ObjType, size_t MaxPerChunk>
	inline LibChunkAllocator<ObjType, MaxPerChunk>::Chunk::Chunk(LibPoolAllocator* pAllocator)
		: m_pAllocator{pAllocator}
	{
		m_pStart = (char*)m_pAllocator->GetBaseAdress();
		size_t capacity = sizeof(ObjType) * MaxPerChunk;
		m_pEnd = m_pStart + capacity;

		m_pObjects.clear();
	}

	template<class ObjType, size_t MaxPerChunk>
	inline LibChunkAllocator<ObjType, MaxPerChunk>::Chunk::~Chunk()
	{
		SafeDelete(m_pAllocator);
	}
}