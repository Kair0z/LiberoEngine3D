#pragma once
#include "Libero/ECS/Core/Component.h"
#include "ImGuiTooltips/ImGui_CompWidget.h"

namespace Libero
{
	class CameraComponent : public Component<CameraComponent>
	{
	public:
		CameraComponent();

		DefGetSet(XMMATRIX, View, m_View);
		DefGetSet(XMMATRIX, Projection, m_Projection);
		XMMATRIX GetViewProjection() const;

		DefGet(float, FOV, m_FOV);
		void SetFOV(const float newFOV);

		DefGetSet(float, NearPlane, m_NearPlane);
		DefGetSet(float, FarPlane, m_FarPlane);

		void SetActive(bool active);
		bool IsActive();

	private:
		XMMATRIX m_Projection = XMMatrixIdentity();
		XMMATRIX m_View = XMMatrixIdentity();
		float m_NearPlane{ 1.f };
		float m_FarPlane{ 500.f };
		float m_FOV{ 90.f };
	};
}


