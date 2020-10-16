#pragma once
#include <unordered_map>
#include <string>

namespace Libero
{
	class ImGuiWindow;
	class Editor final
	{
	public:
		Editor() = default;
		~Editor() { Shutdown(); };

		void Initialize();
		void Render();

	private:
		struct ImGuiIO* m_pIO;
		bool m_IsInitialized = false;

		std::unordered_map<std::string, ImGuiWindow*> m_Windows;

		void InitWindows();
		void Shutdown();
	};
}


