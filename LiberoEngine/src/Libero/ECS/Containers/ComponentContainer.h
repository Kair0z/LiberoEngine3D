#pragma once
#include "../Core/IComponent.h"
#include "Libero/Memory/Allocators/ChunkAllocator/LibChunkAllocator.h"

namespace Libero
{
	class IComponentContainer
	{
	public:
		virtual ~IComponentContainer() = default;
		virtual void DestroyComponent(IComponent*& pComponent) = 0;
	};

	template <class Type>
	class ComponentContainer final:
		public LibChunkAllocator<Type, LBR_COMPONENT_T_CHUNK_SIZE>,
		public IComponentContainer
	{
	public:
		virtual void DestroyComponent(IComponent*& pComponent)
		{
			// Call obj destructor:
			pComponent->~IComponent();

			// Release memory:
			this->DestroyObj(pComponent);

			pComponent = nullptr;
		}
	};
}


