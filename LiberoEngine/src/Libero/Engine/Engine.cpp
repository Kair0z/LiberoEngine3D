#include "Liber_pch.h"
#include "Engine.h"
#include "../Game.h"

#include "Libero/Entities/GameObject.h"
#include "Libero/Interfaces/Events/EngineEvent.h"
#include "Libero/Interfaces/Events/EventDispatcher.h"
#include "Libero/Systems/CoreSystems.h"


namespace Libero
{

	void Engine::Cleanup()
	{
		SafeDelete(m_Mods.m_pEditor);
		SafeDelete(m_Mods.m_pGraphicsMaster);
		SafeDelete(m_Mods.m_pECSMaster);
		SafeDelete(m_Mods.m_pSubjectMaster);
		SafeDelete(m_Mods.m_pInputMaster);
		SafeDelete(m_Mods.m_pTime);
		SafeDelete(m_Mods.m_pSceneMaster);
		SafeDelete(m_Mods.m_pCameraMaster);
		SafeDelete(m_Mods.m_pLogger);
		SafeDelete(m_Mods.m_pContentMaster);
		SafeDelete(m_Mods.m_pFileMaster);
		SafeDelete(m_Mods.m_pMaterialMaster);
	}

	void Engine::SetGame(Game* pGame)
	{
		if (m_pGame) delete m_pGame;
		m_pGame = pGame;
	}


	void Engine::Run(HINSTANCE winInstance)
	{
		// Init masters:
		InitModules(winInstance);
		LoadCoreSystems();

		// Init Game:
		LoadGame();
		while (!m_ShouldQuit)
		{
			m_Mods.m_pTime->Tick();

			// Run Engine
			EngineLoop();

			// Run Game
			GameLoop();
		}
	}


#pragma region Initialization
	void Engine::InitModules(HINSTANCE winInstance)
	{
		// Init Managers:
		m_Mods.m_pGraphicsMaster = new GraphicsMaster();
		m_Mods.m_pGraphicsMaster->Initialize(winInstance);
		GraphicsLocator::Provide(m_Mods.m_pGraphicsMaster);

		m_Mods.m_pLogger = new Logger();
		LoggerLocator::Provide(m_Mods.m_pLogger);
		m_Mods.m_pLogger->LogInfo("The Libero Engine! <DX11>");

		m_Mods.m_pEditor = new Editor();
		m_Mods.m_pEditor->Initialize();

		m_Mods.m_pECSMaster = new ECSMaster();
		ECSLocator::Provide(m_Mods.m_pECSMaster);

		m_Mods.m_pSubjectMaster = new SubjectMaster();
		SubjectLocator::Provide(m_Mods.m_pSubjectMaster);

		// Subscribe the engine object to Input & Engine events
		m_Mods.m_pSubjectMaster->AddToSubject(this, eSubject::Input);
		m_Mods.m_pSubjectMaster->AddToSubject(this, eSubject::Engine);

		m_Mods.m_pInputMaster = new InputMaster();

		m_Mods.m_pTime = new Time();
		m_Mods.m_pTime->Start();
		TimeLocator::Provide(m_Mods.m_pTime);

		m_Mods.m_pSceneMaster = new SceneMaster();
		SceneMasterLocator::Provide(m_Mods.m_pSceneMaster);

		m_Mods.m_pCameraMaster = new CameraMaster();
		m_Mods.m_pCameraMaster->Initialize();
		CameraMasterLocator::Provide(m_Mods.m_pCameraMaster);

		m_Mods.m_pContentMaster = new ContentMaster();
		ContentLocator::Provide(m_Mods.m_pContentMaster);

		m_Mods.m_pFileMaster = new FileMaster();
		FileLocator::Provide(m_Mods.m_pFileMaster);

		m_Mods.m_pMaterialMaster = new MaterialMaster();
		MaterialLocator::Provide(m_Mods.m_pMaterialMaster);
	}

	void Engine::LoadCoreSystems()
	{
		ECSLocator::LoadSystem<SysRendering>();
		ECSLocator::LoadSystem<SysTransforms>();
		ECSLocator::LoadSystem<SysCameras>();
		ECSLocator::LoadSystem<SysInput>();
	}

	void Engine::LoadGame()
	{
		m_pGame->Initialize();
		m_Mods.m_pECSMaster->GameInitialize();
	}

#pragma endregion

	void Engine::BootGame(bool active)
	{
		if (m_GameRunning == active) return; // If no change in state...
		m_GameRunning = active;

		if (active) m_Mods.m_pECSMaster->GameStart();
		else m_Mods.m_pECSMaster->GameStop();
	}

	void Engine::GameLoop()
	{
		if (!m_pGame) return;

		// Game Update:
		m_Mods.m_pECSMaster->GameUpdate();

		// Game Render:
		m_Mods.m_pGraphicsMaster->OpenGameRender();
		m_Mods.m_pECSMaster->Render();
	}

	void Engine::EngineLoop()
	{
		// Engine update:
		m_Mods.m_pInputMaster->Update();

		// UI Render:
		m_Mods.m_pGraphicsMaster->OpenWindowRender();
		
		// Render as Editor || Render as final on window
#ifdef _DEBUG
		m_Mods.m_pEditor->Render();
#else
		m_Mods.m_pGraphicsMaster->RenderGameFrame();
#endif
		// Present Backbuffer
		m_Mods.m_pGraphicsMaster->Present();
	}

	void Engine::OnEvent(IEvent& e)
	{
		EventCatch eCatch{ e };
		eCatch.Catch<EventQuit>([=](IEvent&) { m_ShouldQuit = true; }, true);
		eCatch.Catch<EventGameStart>([=](IEvent&) {BootGame(true); }, true);
		eCatch.Catch<EventGameStop>([=](IEvent&) {BootGame(false); }, true);
	
		m_Mods.m_pECSMaster->OnEvent(e);
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