#include "Liber_pch.h"
#include "Editor.h"
#include "ImGuiStyleLibrary.h"
#include "MyWindows/MyImGuiWindows.h"
#include "Libero/Settings/Settings.h"
#include "Libero/Graphics/GraphicsMaster.h"

namespace Libero
{
	void Editor::Initialize()
	{
		const GraphicsContext& graphContx = GraphicsLocator::Get()->GetGraphicsContext();
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		m_IsInitialized = ImGui_ImplWin32_Init(graphContx.m_WindowHandle) && ImGui_ImplDX11_Init(graphContx.m_pDevice, graphContx.m_pDeviceContext);
		m_pIO = &ImGui::GetIO();

		ImGuiStyles::GoldBlackTheme();

		m_pIO->IniFilename = Settings::ImGui.iniFilePath.c_str();

		InitWindows();
	}

	void Editor::InitWindows()
	{
		m_Windows["Play"] = new ImGui_Play();
		ImGui_Hierarchy* pHierarchy = new ImGui_Hierarchy();
		m_Windows["Hierarchy"] = pHierarchy;

		m_Windows["TopMenu"] = new ImGui_TopMenu();
		m_Windows["Resources"] = new ImGui_Resources();
		m_Windows["Inspector"] = new ImGui_Inspector(*pHierarchy);
		m_Windows["Logger"] = new ImGui_Logger();
		m_Windows["Editor"] = new ImGui_Editor();

		for (auto& wPair : m_Windows)
		{
			wPair.second->EnableEdit(false);
		}
	}

	void Editor::Render()
	{
		if (!m_IsInitialized) return;

		m_pIO->WantCaptureMouse = true;
		m_pIO->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		{
			// Render demo:
			ImGui::ShowDemoWindow();

			// Render My Windows
			for (const auto& wPair : m_Windows)
			{
				wPair.second->ImGuiRender();
			}
		}
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void Libero::Editor::Shutdown()
	{
		if (!m_IsInitialized) return;

		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		for (auto& wPair : m_Windows)
		{
			delete wPair.second;
			wPair.second = nullptr;
		}
	}

}
