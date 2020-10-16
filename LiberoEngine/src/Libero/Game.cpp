#include "Liber_pch.h"
#include "Game.h"
#include "Scene/SceneMaster.h"

namespace Libero
{
    void Game::AddScene(Scene* pScene)
    {
        if (!pScene) return;
        SceneMasterLocator::Get()->AddScene(pScene);
    }

    void Game::GoToScene(const std::string& name)
    {
        SceneMasterLocator::Get()->LoadScene(name);
    }
}

