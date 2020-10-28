#include "Liber_pch.h"
#include "CameraMaster.h"
#include "Libero/Components/CameraComponent.h"
#include "Libero/ECS/ECSMaster.h"
#include "Libero/Entities/GameObject.h"

namespace Libero
{
	void CameraMaster::Initialize()
	{
		// Create default camera actor:
		m_pDefaultCameraActor = ECSLocator::NewEntityAs<GameObject>("DefaultCamera");
		m_pDefaultCamera = m_pDefaultCameraActor->AddComponent<CameraComponent>(CameraComponent());
		SetActiveCamera(m_pDefaultCamera);
	}

	CameraComponent* CameraMaster::GetActiveCamera()
	{
		// If no camera exists, set the active camera to default camera...
		if (!m_pActiveCamera)
		{
			m_pActiveCamera = m_pDefaultCamera;
		}

		return m_pActiveCamera;
	}

	void CameraMaster::SetActiveCamera(CameraComponent* pCamera)
	{
		if (!pCamera) 
			m_pActiveCamera = m_pDefaultCamera;

		m_pActiveCamera = pCamera;
	}
}
