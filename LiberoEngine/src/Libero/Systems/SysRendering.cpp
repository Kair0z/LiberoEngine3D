#include "Liber_pch.h"
#include "SysRendering.h"

#include "Libero/Components/MeshRenderComponent.h"
#include "Libero/Components/MeshFilterComponent.h"
#include "Libero/Components/SkyDomeRenderComponent.h"

namespace Libero
{
	void SysRendering::Initialize()
	{
		ForEachComponent<MeshRenderComponent>([](MeshRenderComponent* pMesh)
			{
				MeshFilterComponent* pMeshFilter = pMesh->GetOwner()->GetComponent<MeshFilterComponent>();
				if (pMeshFilter) pMesh->Initialize(pMeshFilter);
			});

		
	}

	void SysRendering::Render() const
	{
		ForEachComponent<SkyDomeRenderComponent>([](SkyDomeRenderComponent* pSky)
			{
				pSky->Render();
			});
			
		ForEachComponent<MeshRenderComponent>([](MeshRenderComponent* pMesh)
			{
				pMesh->Render();
			});
	}
}