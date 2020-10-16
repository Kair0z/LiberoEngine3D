#pragma once
#include "ImGuiWindow.h"
#include "Libero/Files/FileMaster.h"

namespace Libero
{
	class ImGui_Resources final : public ImGuiWindow
	{
	public:
		ImGui_Resources();
		virtual void ImGuiRender() override;

	private:
		FileMaster::Path m_CurrentPath;
		size_t m_IconSize{ 40 };
	};
}

