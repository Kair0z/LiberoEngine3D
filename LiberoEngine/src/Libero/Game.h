#pragma once
#include "Libero/Settings/Settings.h"
#include "Libero/Scene/Scene.h"
#include <Windows.h>
#include <vector>
#include <unordered_map>
#include <string>

namespace Libero
{
	class Game
	{
		using SceneMap = std::unordered_map<std::string, Scene*>;

	public:
		Game() = default;
		virtual ~Game() = default;

		virtual void Initialize() = 0;

	protected:
		void AddScene(Scene* pScene);
		void GoToScene(const std::string& name);
	};

	// Defined in client
	static Game* CreateGame();
}