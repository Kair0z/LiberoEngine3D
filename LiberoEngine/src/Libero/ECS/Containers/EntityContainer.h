#pragma once
#include "../ECSDef.h"
#include "Libero/Memory/Allocators/ChunkAllocator/LibChunkAllocator.h"

namespace Libero
{
	class IEntity;
	class IEntityContainer
	{
	public:
		virtual ~IEntityContainer() = default;
		virtual void DestroyEntity(IEntity*& pEntity) = 0;
	};

	template <class EType>
	class EntityContainer: 
		public LibChunkAllocator<EType, LBR_ENTITY_T_CHUNK_SIZE>, // Allocating the memory for the entity
		public IEntityContainer
	{
	public:
		void DestroyEntity(IEntity*& pEntity) override final
		{
			// Call IEntity destructor:
			pEntity->~IEntity();

			// Free the memory internally:
			LibChunkAllocator<EType, LBR_ENTITY_T_CHUNK_SIZE>::DestroyObj(pEntity);

			// Set pointer to nullptr:
			pEntity = nullptr;
		}
	};
}