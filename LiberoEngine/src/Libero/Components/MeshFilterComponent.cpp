#include "Liber_pch.h"
#include "MeshFilterComponent.h"
#include "Libero/Graphics/Mesh.h"

namespace Libero
{
	MeshFilterComponent::MeshFilterComponent(Mesh* pMesh)
		: m_pMesh{pMesh}
	{
	}

	Mesh* MeshFilterComponent::GetMesh() const
	{
		return m_pMesh;
	}
}

