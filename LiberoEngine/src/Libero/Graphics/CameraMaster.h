#pragma once
#include "Libero/Interfaces/ILocator.h"

namespace Libero
{
	class CameraComponent;
	class GameObject;
	class CameraMaster final
	{
	public:
		void Initialize();

		CameraComponent* GetActiveCamera();
		void SetActiveCamera(CameraComponent* pCamera);

	private:
		CameraComponent* m_pActiveCamera = nullptr;
		CameraComponent* m_pDefaultCamera = nullptr;
		GameObject* m_pDefaultCameraActor = nullptr;
	};

	class CameraMasterLocator final : public ILocator<CameraMaster>{};
}


