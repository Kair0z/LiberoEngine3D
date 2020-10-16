#include "Liber_pch.h"
#include "ImGui_Resources.h"

#include "Libero/Content/ContentMaster.h"

namespace Libero
{
	ImGui_Resources::ImGui_Resources()
	{
		m_CurrentPath = "../Resources/Assets";
	}

	void ImGui_Resources::ImGuiRender() 
	{
		//if (m_CurrentPath.empty())
			//m_CurrentPath = FileMaster::Path(FileLocator::Get()->GetRoot().c_str());

		
		Begin("Resources", m_EditEnable);

		Texture2D* pTex = ContentLocator::Get()->Load<Texture2D>("../Resources/Core/Textures/folder_icon&32.png");

		ImVec2 size = { (float)m_IconSize, (float)m_IconSize };
		auto fn = [&pTex, size](FileMaster::rDirEntry dirEntry)
		{
			if (ImGui::ImageButton((void*)pTex->GetSRV(), size, {}, { 1, 1 }, -1, { 0, 0, 0, 0 }, { 1, 1, 1, 1 }))
			{
				
			}
			std::string filename = dirEntry.path().filename().string();
			ImGui::Text(filename.c_str());
		};
		
		FileLocator::Get()->ForEachFolder(fn, m_CurrentPath);

		ImGui::End();
	}
}