#pragma once

namespace Libero
{
	class InputMaster
	{
	public:
		void Update();

	private:
		void ProcessKeyDown(WPARAM wParam);
		void ProcessKeyUp(WPARAM wParam);
		void ProcessMouseDown(LPARAM lParam, WPARAM wParam);
		void ProcessMouseUp(LPARAM lParam, WPARAM wParam);
		void ProcessMouseMove(LPARAM lParam, WPARAM wParam);
		
	};
}


