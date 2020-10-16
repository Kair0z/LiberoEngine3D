#pragma once
#include "Libero/Interfaces/ILocator.h"
#include <unordered_map>

namespace Libero
{
	class Scene;
	class SceneMaster final
	{
		using SceneMap = std::unordered_map<std::string, Scene*>;

	public:
		SceneMaster() = default;
		~SceneMaster();

		void AddScene(Scene* pScene);
		void LoadScene(const std::string& name);

		bool IsEmpty() const;
		Scene* GetActiveScene() const;

	private:
		SceneMap m_SceneMap;
		Scene* m_pActiveScene;
	};

	class SceneMasterLocator : public ILocator<SceneMaster>{};
}


