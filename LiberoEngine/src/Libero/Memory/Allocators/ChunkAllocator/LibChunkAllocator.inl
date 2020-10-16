#include "Liber_pch.h"
#include "LibChunkAllocator.h"
#include "Libero/Memory/MemoryMaster.h"


namespace Libero
{
	template<class ObjType, size_t MaxPerChunk>
	inline LibChunkAllocator<ObjType, MaxPerChunk>::LibChunkAllocator()
	{
		// Create the first chunk:
		Chunk* pChunk = NewChunk();
		m_pChunks.push_back(pChunk); 
	}

	template<class ObjType, size_t MaxPerChunk>
	inline LibChunkAllocator<ObjType, MaxPerChunk>::~LibChunkAllocator()
	{
		MemoryMaster& mem = MemoryMaster::Get();
		for (Chunk* pChunk : m_pChunks)
		{
			// Call all object destructors:
			for (ObjType* pObj : pChunk->m_pObjects)
				pObj->~ObjType();

			// Clear the vector:
			pChunk->m_pObjects.clear();

			// Let memorymaster release all obj memory:
			mem.Free((void*)pChunk->m_pAllocator->GetBaseAdress());

			// Safedelete the chunk:
			SafeDelete(pChunk);
		}
	}


	template<class ObjType, size_t MaxPerChunk>
	inline void* LibChunkAllocator<ObjType, MaxPerChunk>::CreateObj()
	{
		void* pSlot = nullptr;

		for (Chunk* pChunk : m_pChunks)
		{
			// If there are already too many objects in the chunk:
			// Continue to next chunk:
			if (pChunk->m_pObjects.size() >= MaxPerChunk) continue;
		
			pSlot = pChunk->m_pAllocator->Allocate(sizeof(ObjType));
			if (pSlot)
			{
				pChunk->m_pObjects.push_back((ObjType*)pSlot);
				break;
			}
		}
	
		// If no free slot was found:
		// --> All chunks are full
		// --> Allocate a new chunk:
		if (!pSlot)
		{
			Chunk* pChunk = NewChunk();
			m_pChunks.push_back(pChunk);
			
			pSlot = pChunk->m_pAllocator->Allocate(sizeof(ObjType));
			pChunk->m_pObjects.clear();
			pChunk->m_pObjects.push_back((ObjType*)pSlot);
		}

		return pSlot;
	}

	template<class ObjType, size_t MaxPerChunk>
	inline void LibChunkAllocator<ObjType, MaxPerChunk>::DestroyObj(void* pObj)
	{
		// Here we only destroy the memory of the obj, not the actual obj
		// Destructor must get called earlier down the line!
		char* asChar = (char*)pObj;

		for (Chunk* pChunk : m_pChunks)
		{
			if (pChunk->m_pStart <= asChar && asChar < pChunk->m_pEnd)
			{
				// No need for destructor (should've been called earlier)
				pChunk->m_pObjects.remove((ObjType*)pObj);
				pChunk->m_pAllocator->Free(pObj);
				pObj = nullptr;
				return;
			}
		}
	}


	template<class ObjType, size_t MaxPerChunk>
	inline typename LibChunkAllocator<ObjType, MaxPerChunk>::ChunkIterator LibChunkAllocator<ObjType, MaxPerChunk>::Begin()
	{
		return LibChunkAllocator<ObjType, MaxPerChunk>::ChunkIterator(m_pChunks.begin(), m_pChunks.end());
	}
	template<class ObjType, size_t MaxPerChunk>
	inline typename LibChunkAllocator<ObjType, MaxPerChunk>::ChunkIterator LibChunkAllocator<ObjType, MaxPerChunk>::End()
	{
		return LibChunkAllocator<ObjType, MaxPerChunk>::ChunkIterator(m_pChunks.end(), m_pChunks.end());
	}


	// Helper that creates chunk:
	template<class ObjType, size_t MaxPerChunk>
	inline typename LibChunkAllocator<ObjType, MaxPerChunk>::Chunk* LibChunkAllocator<ObjType, MaxPerChunk>::NewChunk()
	{
		//return nullptr;
		MemoryMaster& mem = MemoryMaster::Get();
		LibPoolAllocator* pAllocator = new LibPoolAllocator(m_ChunkAllocationSize, mem.Allocate(m_ChunkAllocationSize), sizeof(ObjType));
		Chunk* pChunk = new Chunk(pAllocator);
		return pChunk;
	}
}