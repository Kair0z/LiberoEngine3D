#pragma once
#include "ImGuiWindow.h"
#include "Libero/Graphics/GraphicsMaster.h"
#include "Libero/Graphics/RenderTarget.h"
#include "Libero/Scene/SceneMaster.h"
#include "Libero/Scene/Scene.h"
#include "Libero/Entities/GameObject.h"
#include "Libero/Logging/Logger.h"
#include "Libero/Interfaces/Observer/SubjectMaster.h"
#include "Libero/Interfaces/Events/EngineEvent.h"


namespace Libero
{
	class ImGui_Editor final : public ImGuiWindow
	{
		virtual void ImGuiRender() override
		{
			Begin("Editor", m_EditEnable);

			ID3D11ShaderResourceView* pFrame = GraphicsLocator::Get()->GetFrame();
			ImVec2 size = ImGui::GetWindowSize();
			ImGui::Image((void*)pFrame, size);

			ImGui::End();
		}
	};

	class ImGui_Logger final : public ImGuiWindow
	{
		virtual void ImGuiRender() override
		{
			Begin("Logger", m_EditEnable);

			Logger* pLogger = LoggerLocator::Get();
			if (pLogger)
			{
				const std::vector<std::string>& buffer = pLogger->GetLogBuffer();
				for (auto it = buffer.rbegin(); it != buffer.rend(); ++it)
				{
					ImGui::TextUnformatted(it->c_str());
				}
			}

			ImGui::End();
		}
	};

	class ImGui_Play final : public ImGuiWindow
	{
		virtual void ImGuiRender() override
		{
			Begin("Play", m_EditEnable);

			ImVec2 buttonDim = { 100.f, 30.f };

			ImGui::Indent((ImGui::GetWindowSize().x / 2.f) - buttonDim.x);

			if (ImGui::Button("Play", buttonDim))
			{
				EventGameStart e{};
				SubjectLocator::Get()->Notify(eSubject::Engine, e);
			}

			ImGui::SameLine();

			if (ImGui::Button("Stop", buttonDim))
			{
				EventGameStop e{};
				SubjectLocator::Get()->Notify(eSubject::Engine, e);
			}

			ImGui::End();
		}
	};

	class ImGui_TopMenu final : public ImGuiWindow
	{
		virtual void ImGuiRender() override
		{
			ImGui::BeginMainMenuBar();

			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Options"))
			{
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	};
}

#include "ImGui_Resources.h"
#include "ImGui_Inspector.h"
#include "ImGui_Hierarchy.h"