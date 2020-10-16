#pragma once
#include "ImGuiWindow.h"

namespace Libero
{
	class GameObject;
	class ImGui_Hierarchy final : public ImGuiWindow
	{
		virtual void ImGuiRender() override;

	public:
		GameObject* GetSelected();

	private:
		GameObject* m_pSelectedObject = nullptr;
	};
}