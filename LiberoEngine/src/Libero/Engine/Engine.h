#pragma once
#include "../Settings/Settings.h"
#include "Libero/Interfaces/Observer/IObserver.h"
#include "EngineModules.h"

namespace Libero
{
	class Game;
	class Engine final : public IObserver
	{
	public:
		~Engine() { Cleanup(); };

		void SetGame(Game* pGame);
		void Run(HINSTANCE winInstance);

		void OnEvent(IEvent& e);

	private:
		Game* m_pGame;
		Settings m_Settings{};

		// Managers:
		EngineModules m_Mods{};
		
		bool m_ShouldQuit = false;
		bool m_GameRunning = false;

	private:
		void Cleanup();

		void InitModules(HINSTANCE winInstance);
		void LoadCoreSystems();
		void LoadGame();

		void BootGame(bool active);
		void EngineLoop();
		void GameLoop();

	public:
		static LRESULT CALLBACK WindowsProcedureStatic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}


