#include "Liber_pch.h"
#include "SysCameras.h"

#include "Libero/Components/CameraComponent.h"
#include "Libero/Components/TransformComponent.h"

namespace Libero
{
	void SysCameras::PostUpdate()
	{
		CalculateViews();
	}

	void SysCameras::CalculateViews()
	{
		using namespace DirectX;
		ForEachComponent<CameraComponent>([](CameraComponent* pCamera)
			{
				TransformComponent* pTransform = pCamera->GetOwner()->GetComponent<TransformComponent>();
				if (!pTransform) return;

				XMMATRIX view;
				XMVECTOR pos = ToXMVector(pTransform->GetPosition());
				XMVECTOR lookAt = ToXMVector(pTransform->GetForward());
				XMVECTOR up = ToXMVector(pTransform->GetUp());
				
				view = DirectX::XMMatrixLookAtLH(pos, DirectX::XMVectorAdd(pos, lookAt), up);
				pCamera->SetView(view);
			});
	}
}