#pragma once
#include "Libero/API.h"
#include "../Settings/Settings.h"

#include "Libero/Graphics/GraphicsMaster.h"
#include "Libero/Interfaces/Observer/IObserver.h"
#include "Libero/Time/Time.h"

namespace Libero
{
	class Game;
	class ECSMaster;
	class SubjectMaster;
	class InputMaster;
	class SceneMaster;
	class CameraMaster;
	class ContentMaster;
	class FileMaster;
	class Logger;
	class MaterialMaster;
	class Editor;

	class Engine final : public IObserver
	{
	public:
		Engine();
		~Engine() { Cleanup(); };

		void LoadGame(Game* pGame);
		void Run(HINSTANCE winInstance);

		void OnEvent(IEvent& e);

	private:
		// The loaded game:
		Game* m_pGame;
		Settings m_Settings{};

		// Managers:
		ECSMaster* m_pECSMaster;
		GraphicsMaster* m_pGraphicsMaster;
		SubjectMaster* m_pSubjectMaster;
		Editor* m_pEditor;
		InputMaster* m_pInputMaster;
		Time* m_pTime;
		SceneMaster* m_pSceneMaster;
		CameraMaster* m_pCameraMaster;
		ContentMaster* m_pContentMaster;
		Logger* m_pLogger;
		FileMaster* m_pFileMaster;
		MaterialMaster* m_pMaterialMaster;

		bool m_ShouldQuit = false;
		bool m_GameRunning = false;

	private:
		void Cleanup();

		void InitMasters(HINSTANCE winInstance);
		void InitSystems();
		void InitGame();

		void GameStart();
		void GameStop();

		void EngineLoop();
		void GameLoop();

	public:
		static LRESULT CALLBACK WindowsProcedureStatic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}


