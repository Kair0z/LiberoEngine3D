#include "Liber_pch.h"
#include "EntityContainer.h"

namespace Libero
{
	template<class EType>
	inline void EntityContainer<EType>::DestroyEntity(IEntity* pEntity)
	{
		// Call IEntity destructor:
		pEntity->~IEntity();

		// Free the memory internally:
		LibChunkAllocator<EType, LBR_ENTITY_T_CHUNK_SIZE>::DestroyObj(pEntity);
	}
}