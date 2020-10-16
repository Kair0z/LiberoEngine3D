#pragma once
#include <string>

namespace Libero
{
	class ImGui_CompWidget
	{
	public:
		ImGui_CompWidget(const std::string& widgetName) : m_Name{ widgetName } {};
		virtual ~ImGui_CompWidget() = default;

		virtual void ImGuiRender(IComponent* pComponent) = 0;

		const std::string& GetName() const { return m_Name; };

	private:
		std::string m_Name;
	};
}