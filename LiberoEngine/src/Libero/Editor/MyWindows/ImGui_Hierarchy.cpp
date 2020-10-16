#include "Liber_pch.h"
#include "ImGui_Hierarchy.h"
#include "Libero/Scene/SceneMaster.h"
#include "Libero/Scene/Scene.h"
#include "Libero/Entities/GameObject.h"

namespace Libero
{
	void ImGui_Hierarchy::ImGuiRender()
	{
		Begin("Hierarchy", m_EditEnable);

		SceneMaster* pSceneMaster = SceneMasterLocator::Get();
		if (!pSceneMaster)
		{
			ImGui::End();
			return;
		}
		if (pSceneMaster->IsEmpty())
		{
			ImGui::End();
			return;
		}

		Scene* pActiveScene = pSceneMaster->GetActiveScene();

		bool h = ImGui::CollapsingHeader(pActiveScene->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen);

		if (h)
		{
			

			// For each object:
			for (GameObject* pObj : pActiveScene->GetObjects())
			{
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
				if (pObj == m_pSelectedObject) flags = flags | ImGuiTreeNodeFlags_Selected;

				bool temp =  ImGui::TreeNodeEx(pObj->GetName().c_str(), flags);
				if (ImGui::IsItemClicked())
				{
					m_pSelectedObject = pObj;

					if (ImGui::BeginPopupContextItem("* Game Scene *"))
					{
						std::string fullStr = "* Delete " + pObj->GetName() + " *";
						if (ImGui::Selectable(fullStr.c_str())) pActiveScene->RemoveGameObject(pObj);

						ImGui::EndPopup();
					}
				}
				
				if (temp) ImGui::TreePop();
			}
		}

		ImGui::End();
	}
	GameObject* ImGui_Hierarchy::GetSelected()
	{
		return m_pSelectedObject;
	}
}