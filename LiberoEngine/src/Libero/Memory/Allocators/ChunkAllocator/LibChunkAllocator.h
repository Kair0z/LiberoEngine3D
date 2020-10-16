#pragma once
// ---------------------------------------------------------------------------------------------------------------------------------*
//  Credits to Tobias Stein's article about an auxiliary allocator class using the base PoolAllocator.
// --> It creates memory chunks when out of capacity. Every memory chunk is managed by a single PoolAllocator
// This article helped me greatly into creating the perfect allocator to manage my ECS-items
// https://github.com/tobias-stein/EntityComponentSystem/blob/master/EntityComponentSystem/include/ECS/Memory/MemoryChunkAllocator.h
// ---------------------------------------------------------------------------------------------------------------------------------*
#include <list>
#include "Libero/Memory/Allocators/LibPoolAllocator.h"

namespace Libero
{
	class LibPoolAllocator;
	
	template <class ObjType, size_t MaxPerChunk>
	class LibChunkAllocator 
	{
		static const size_t m_MaxObjPerChunk = MaxPerChunk;
		static const size_t m_ChunkAllocationSize = (sizeof(ObjType)) * MaxPerChunk;

	public:
		class Chunk
		{
		public:
			Chunk(LibPoolAllocator* pAllocator);
			~Chunk();

		private:
			friend class LibChunkAllocator;
			LibPoolAllocator* m_pAllocator;
			std::list<ObjType*> m_pObjects;

			char* m_pStart;
			char* m_pEnd;
		};
		class ChunkIterator
		{
		public:
			ChunkIterator(typename std::list<Chunk*>::iterator chunksBegin, typename std::list<Chunk*>::iterator chunksEnd);

			ChunkIterator& operator++();
			ObjType* operator*() const;
			ObjType* operator->() const;

			bool operator==(const ChunkIterator& other) const;
			bool operator!=(const ChunkIterator& other) const;

		private:
			typename std::list<Chunk*>::iterator m_CurChunk;
			typename std::list<Chunk*>::iterator m_EndChunk;
			typename std::list<ObjType*>::iterator m_CurObj;
		};
	
	public:
		LibChunkAllocator();
		~LibChunkAllocator();

		void* CreateObj();
		void DestroyObj(void* pObj);

		ChunkIterator Begin();
		ChunkIterator End();

	protected:
		std::list<Chunk*> m_pChunks;
		Chunk* NewChunk();
	};
}

#include "Chunk.inl"
#include "ChunkIterator.inl"
#include "LibChunkAllocator.inl"
