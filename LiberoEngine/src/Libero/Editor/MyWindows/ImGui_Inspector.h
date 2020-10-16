#pragma once
#include "ImGuiWindow.h"

namespace Libero
{
	class ImGui_Hierarchy;
	class ImGui_Inspector final : public ImGuiWindow
	{
	public:
		ImGui_Inspector(ImGui_Hierarchy& hierarchy) : m_HierarchyRef{ hierarchy } {};

	private:
		virtual void ImGuiRender() override;

	private:
		ImGui_Hierarchy& m_HierarchyRef;
	};
}