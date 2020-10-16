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
		virtual void DestroyEntity(IEntity* pEntity) = 0;
	};

	template <class EType>
	class EntityContainer: 
		public LibChunkAllocator<EType, LBR_ENTITY_T_CHUNK_SIZE>,
		public IEntityContainer
	{
	public:
		void DestroyEntity(IEntity* pEntity) override final;
	};
}

#include "EntityContainer.inl"
