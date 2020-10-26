#pragma once
#include "ImGuiWindow.h"
#include "Libero/Settings/Settings.h"
#include "Libero/Graphics/GraphicsMaster.h"

namespace Libero
{
	class ImGui_Editor final : public ImGuiWindow
	{
		virtual void ImGuiRender() override
		{
			Begin("Editor", m_EditEnable);

			ID3D11ShaderResourceView* pFrame = GraphicsLocator::Get()->GetGameFrame();

			Vector2f actualDimensions = Settings::Window.Dimensions;
			ImVec2 imguiWindowSize = ImGui::GetWindowSize();

			//float ar = actualDimensions.x / actualDimensions.y;
			//float oar = imguiWindowSize.x / imguiWindowSize.y;

			float uvdx = 0.0f;
			float uvdy = 0.0f;

			ImVec2 uv0{uvdx, uvdy};
			ImVec2 uv1{1.0f - uvdx, 1.0f - uvdy};
			ImGui::Image((void*)pFrame, imguiWindowSize, uv0, uv1);

			ImGui::End();
		}
	};

	class ImGui_GameView :
		public ImGuiWindow
	{
		
	};
}



