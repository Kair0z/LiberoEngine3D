#pragma once

namespace Libero
{
	inline void Begin(const std::string& title, bool editEnable)
	{
		if (!editEnable) ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		else ImGui::Begin(title.c_str());
	}

	class ImGuiWindow
	{
	public:
		virtual ~ImGuiWindow() = default;

		virtual void ImGuiRender() = 0;

		void EnableEdit(const bool enable)
		{
			m_EditEnable = enable;
		}

	protected:
		ImGuiWindow() = default;
		bool m_EditEnable = false;
	};
}


