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
				// If object is selected, mark node as selected:
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
				if (pObj == m_pSelectedObject) flags = flags | ImGuiTreeNodeFlags_Selected;
				
				// Start a collapsable node:
				bool temp =  ImGui::TreeNodeEx(pObj->GetName().c_str(), flags);
				if (temp) ImGui::TreePop();

				if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
				{
					// Open Object Delete Menu:
					std::string fullStr = "Remove " + pObj->GetName();
					if (ImGui::Selectable(fullStr.c_str())) pActiveScene->RemoveGameObject(pObj);
				}

				// Select the node:
				if (ImGui::IsItemClicked()) m_pSelectedObject = pObj;
			}

			if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_Delete)) && m_pSelectedObject)
			{
				pActiveScene->RemoveGameObject(m_pSelectedObject);
			}
		}

		ImGui::End();
	}
	GameObject* ImGui_Hierarchy::GetSelected()
	{
		return m_pSelectedObject;
	}
}