#include "Liber_pch.h"
#include "CameraComponent.h"
#include "Libero/Graphics/CameraMaster.h"
#include "Libero/Settings/Settings.h"

namespace Libero
{
	CameraComponent::CameraComponent()
	{
		m_Projection = DirectX::XMMatrixPerspectiveFovLH(m_FOV, Settings::Window.AR, m_NearPlane, m_FarPlane);
	}

	XMMATRIX CameraComponent::GetViewProjection() const
	{
		return m_View * m_Projection;
	}

	void CameraComponent::SetActive(bool active)
	{
		CameraMaster* pMaster = CameraMasterLocator::Get();
		if (!pMaster) return;

		CameraComponent* pActiveCam = pMaster->GetActiveCamera();

		if (active && pActiveCam != this) pMaster->SetActiveCamera(this);
		if (!active && pActiveCam == this) pMaster->SetActiveCamera(nullptr); // Set default camera
	}

	bool CameraComponent::IsActive()
	{
		return CameraMasterLocator::Get()->GetActiveCamera() == this;
	}
}

