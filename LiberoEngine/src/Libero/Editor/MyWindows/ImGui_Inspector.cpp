#include "Liber_pch.h"
#include "ImGui_Inspector.h"
#include "ImGui_Hierarchy.h"

#include "Libero/Entities/GameObject.h"
#include "Libero/Components/ImGuiTooltips/ImGui_CompWidget.h"

namespace Libero
{
	void ImGui_Inspector::ImGuiRender() 
	{
		Begin("Inspector", m_EditEnable);

		GameObject* pObject = m_HierarchyRef.GetSelected();

		if (!pObject) { ImGui::End(); return; };

		for (IComponent* pComponent : pObject->GetComponents())
		{
			pComponent;
			/*ImGui_CompWidget* pWidget = pComponent->GetImGuiWidget();
			if (!pWidget) continue;

			if (ImGui::TreeNodeEx(pWidget->GetName().c_str(), 0))
			{
				pComponent;
				ImGui::TreePop();
			}*/
		}
		
		ImGui::End();
	}
}