#include "Liber_pch.h"
#include "Engine.h"
#include "../Game.h"
#include "Libero/ECS/ECSMaster.h"
#include "Libero/Interfaces/Observer/SubjectMaster.h"
#include "Libero/Content/ContentMaster.h"
#include "Libero/Files/FileMaster.h"
#include "Libero/Graphics/CameraMaster.h"
#include "Libero/Entities/GameObject.h"
#include "Libero/Interfaces/Events/EngineEvent.h"
#include "Libero/Interfaces/Events/EventDispatcher.h"
#include "Libero/Input/InputMaster.h"
#include "Libero/Scene/SceneMaster.h"
#include "Libero/Graphics/Materials/MaterialMaster.h"
#include "Libero/Systems/CoreSystems.h"
#include "Libero/Logging/Logger.h"
#include "Libero/Editor/Editor.h"


namespace Libero
{
#pragma region Constructor
	Engine::Engine()
		: m_pGame{nullptr}
		, m_pEditor{nullptr}
		, m_pECSMaster{nullptr}
		, m_pSubjectMaster{nullptr}
		, m_Settings{}
		, m_pTime{nullptr}
		, m_pSceneMaster{nullptr}
		, m_pCameraMaster{nullptr}
		, m_pContentMaster{nullptr}
		, m_pFileMaster{nullptr}
		, m_pMaterialMaster{nullptr}
	{
		
	}
#pragma endregion

	void Engine::Cleanup()
	{
		SafeDelete(m_pEditor);
		SafeDelete(m_pGraphicsMaster);
		SafeDelete(m_pECSMaster);
		SafeDelete(m_pSubjectMaster);
		SafeDelete(m_pInputMaster);
		SafeDelete(m_pTime);
		SafeDelete(m_pSceneMaster);
		SafeDelete(m_pCameraMaster);
		SafeDelete(m_pLogger);
		SafeDelete(m_pContentMaster);
		SafeDelete(m_pFileMaster);
		SafeDelete(m_pMaterialMaster);
	}

	void Engine::LoadGame(Game* pGame)
	{
		if (m_pGame) delete m_pGame;

		m_pGame = pGame;
	}


	void Engine::Run(HINSTANCE winInstance)
	{
		// Init masters:
		InitMasters(winInstance);
		InitSystems();

		// Init Game:
		InitGame();

		float cap{};
		while (!m_ShouldQuit)
		{
			// TODO: make this multithreaded:
			m_pTime->Tick();
			cap += (float)m_pTime->Delta();
			if (cap > 1.0f)
			{
				m_pLogger->LogInfo(std::to_string(m_pTime->FPS()));
				cap = 0.f;
			}
			
			GameLoop();
			EngineLoop();

			m_pGraphicsMaster->Present();
		}
	}


#pragma region Initialize
	void Engine::InitMasters(HINSTANCE winInstance)
	{
		// Init Managers:
		m_pGraphicsMaster = new GraphicsMaster();
		m_pGraphicsMaster->Initialize(winInstance);
		GraphicsLocator::Provide(m_pGraphicsMaster);

		m_pLogger = new Logger();
		LoggerLocator::Provide(m_pLogger);
		m_pLogger->LogInfo("The Libero Engine! <DX11>");

		m_pEditor = new Editor();
		m_pEditor->Initialize();

		m_pECSMaster = new ECSMaster();
		m_pECSMaster->Initialize();
		ECSLocator::Provide(m_pECSMaster);

		m_pSubjectMaster = new SubjectMaster();
		SubjectLocator::Provide(m_pSubjectMaster);

		// Subscribe the engine object to Input & Engine events
		m_pSubjectMaster->AddToSubject(this, eSubject::Input);
		m_pSubjectMaster->AddToSubject(this, eSubject::Engine);

		m_pInputMaster = new InputMaster();

		m_pTime = new Time();
		m_pTime->Start();
		TimeLocator::Provide(m_pTime);

		m_pSceneMaster = new SceneMaster();
		SceneMasterLocator::Provide(m_pSceneMaster);

		m_pCameraMaster = new CameraMaster();
		m_pCameraMaster->Initialize();
		CameraMasterLocator::Provide(m_pCameraMaster);

		m_pContentMaster = new ContentMaster();
		ContentLocator::Provide(m_pContentMaster);

		m_pFileMaster = new FileMaster();
		FileLocator::Provide(m_pFileMaster);

		m_pMaterialMaster = new MaterialMaster();
		MaterialLocator::Provide(m_pMaterialMaster);
	}

	void Engine::InitSystems()
	{
		ECSLocator::LoadSystem<SysRendering>();
		ECSLocator::LoadSystem<SysTransforms>();
		ECSLocator::LoadSystem<SysCameras>();
		ECSLocator::LoadSystem<SysInput>();
	}

	void Engine::InitGame()
	{
		m_pGame->Initialize();
		m_pECSMaster->GameInitialize();
	}

#pragma endregion

	void Engine::GameStart()
	{
		if (m_GameRunning) return;
		m_GameRunning = true;
		//m_pECSMaster->GameStart();

		m_pLogger->LogInfo("GameStart!!!");
	}

	void Engine::GameStop()
	{
		if (!m_GameRunning) return;
		m_GameRunning = false;

		//m_pECSMaster->GameStop();
		m_pLogger->LogInfo("GameStop!!!");
	}

	void Engine::GameLoop()
	{
		if (!m_pGame) return;

		// Game Update:
		m_pECSMaster->GameUpdate();

		// Game Render:
		m_pGraphicsMaster->OpenGameRender();
		m_pECSMaster->Render();
	}

	void Engine::EngineLoop()
	{
		// Engine update:
		m_pInputMaster->Update();

		// UI Render:
		m_pGraphicsMaster->OpenEngineRender();
		m_pEditor->Render();
	}

	void Engine::OnEvent(IEvent& e)
	{
		EventDispatcher dispatcher{ e };
		dispatcher.Dispatch<EventQuit>([=](IEvent& e) { m_ShouldQuit = true;  e.SetHandled(); });
		dispatcher.Dispatch<EventGameStart>([=](IEvent& e) {GameStart(); e.SetHandled(); });
		dispatcher.Dispatch<EventGameStop>([=](IEvent& e) {GameStop(); e.SetHandled(); });
	
		m_pECSMaster->OnEvent(e);
	}
}

#pragma region WindowsProc
// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Libero
{
	LRESULT Engine::WindowsProcedureStatic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
			return true;

		// sort through and find what code to run for the message given
		switch (message)
		{
			// this message is read when the window is closed
		case WM_DESTROY:
		{
			// close the application entirely
			PostQuitMessage(0);
			return 0;
		} break;
		}

		// Handle any messages the switch statement didn't
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
#pragma endregion