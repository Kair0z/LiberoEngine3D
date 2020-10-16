#include "Liber_pch.h"
#include "InputMaster.h"
#include "Libero/Interfaces/Observer/SubjectMaster.h"
#include "Libero/Interfaces/Events/EngineEvent.h"
#include "Libero/Interfaces/Events/KeyEvent.h"
#include "Libero/Interfaces/Events/MouseEvent.h"
#include "Libero/Logging/Logger.h"

namespace Libero
{
	void InputMaster::Update()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
			switch (msg.message)
			{
			case WM_QUIT: 
				{
					EventQuit q{};
					SubjectLocator::Get()->Notify(eSubject::Input, q);
				}
				break;

			case WM_KEYDOWN:
				ProcessKeyDown(msg.wParam);
				break;

			case WM_KEYUP:
				ProcessKeyUp(msg.wParam);
				break;

			case WM_LBUTTONDOWN:
				ProcessMouseDown(msg.lParam, msg.wParam);
				break;

			case WM_LBUTTONUP:
				ProcessMouseUp(msg.lParam, msg.wParam);
				break;

			case WM_MOUSEMOVE:
				ProcessMouseMove(msg.lParam, msg.wParam);
				break;

			default:
				break;
			}
		}
	}

	void InputMaster::ProcessKeyDown(WPARAM wParam)
	{
		//LoggerLocator::Get()->LogInfo("KeyDown!");

		EventKeyDown e{wParam};
		SubjectLocator::Get()->Notify(eSubject::Input, e);
	}

	void InputMaster::ProcessKeyUp(WPARAM wParam)
	{
		//LoggerLocator::Get()->LogInfo("KeyUp!");
		
		EventKeyUp e{wParam};
		SubjectLocator::Get()->Notify(eSubject::Input, e);
	}

	void InputMaster::ProcessMouseDown(LPARAM lParam, WPARAM wParam)
	{
		EventMouseDown e{ lParam, wParam };
		SubjectLocator::Get()->Notify(eSubject::Input, e);
	}

	void InputMaster::ProcessMouseUp(LPARAM lParam, WPARAM wParam)
	{
		EventMouseUp e{ lParam, wParam};
		SubjectLocator::Get()->Notify(eSubject::Input, e);
	}

	void InputMaster::ProcessMouseMove(LPARAM lParam, WPARAM wParam)
	{
		EventMouseMove e{ lParam, wParam };
		SubjectLocator::Get()->Notify(eSubject::Input, e);
	}
}