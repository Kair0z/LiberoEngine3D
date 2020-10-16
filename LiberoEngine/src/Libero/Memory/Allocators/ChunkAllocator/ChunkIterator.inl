#include "Liber_pch.h"
#include "LibChunkAllocator.h"

namespace Libero
{
	template <class ObjType, size_t ObjPerChunk>
	inline LibChunkAllocator<ObjType, ObjPerChunk>::ChunkIterator::ChunkIterator(typename std::list<LibChunkAllocator<ObjType, ObjPerChunk>::Chunk*>::iterator chunksBegin, typename std::list<LibChunkAllocator<ObjType, ObjPerChunk>::Chunk*>::iterator chunksEnd)
		// Defining range in construction
		: m_CurChunk{chunksBegin}
		, m_EndChunk{chunksEnd}
	{

		// Setting Current obj:
		// if 'chunksBegin' == 'chunksEnd' --> Current object is the last obj of the last chunk before end
		// Else --> Current object is the first obj of 'chunksBegin'

		if (chunksBegin == chunksEnd) m_CurObj = (*std::prev(chunksEnd))->m_pObjects.end();
		else m_CurObj = (*chunksBegin)->m_pObjects.begin();
	}


	template<class ObjType, size_t MaxPerChunk>
	inline typename LibChunkAllocator<ObjType, MaxPerChunk>::ChunkIterator& LibChunkAllocator<ObjType, MaxPerChunk>::ChunkIterator::operator++()
	{
		// Go to the next obj
		++m_CurObj;

		// If obj-iterator == chunk-end-iterator 
		// --> Move to next chunk
		if (m_CurObj == (*m_CurChunk)->m_pObjects.end())
		{
			++m_CurChunk;

			if (m_CurChunk != m_EndChunk) m_CurObj = (*m_CurChunk)->m_pObjects.begin();
		}

		// returning modified operator is for chaining purposes...
		return *this;
	}


	template<class ObjType, size_t ObjPerChunk>
	inline ObjType* LibChunkAllocator<ObjType, ObjPerChunk>::ChunkIterator::operator*() const
	{
		return *m_CurObj;
	}
	template<class ObjType, size_t ObjPerChunk>
	inline ObjType* LibChunkAllocator<ObjType, ObjPerChunk>::ChunkIterator::operator->() const
	{
		return *m_CurObj;
	}


	template<class ObjType, size_t ObjPerChunk>
	inline bool LibChunkAllocator<ObjType, ObjPerChunk>::ChunkIterator::operator==(const LibChunkAllocator<ObjType, ObjPerChunk>::ChunkIterator& other) const
	{
		return (m_CurChunk == other.m_CurChunk) && (m_CurObj == other.m_CurObj);
	}
	template<class ObjType, size_t ObjPerChunk>
	inline bool LibChunkAllocator<ObjType, ObjPerChunk>::ChunkIterator::operator!=(const LibChunkAllocator<ObjType, ObjPerChunk>::ChunkIterator& other) const
	{
		return !(*this == other);
	}
}