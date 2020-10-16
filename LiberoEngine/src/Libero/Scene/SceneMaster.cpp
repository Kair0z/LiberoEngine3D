#include "Liber_pch.h"
#include "SceneMaster.h"
#include "Scene.h"

namespace Libero
{
	SceneMaster::~SceneMaster()
	{
		for (auto& scene : m_SceneMap)
		{
			SafeDelete(scene.second);
		}
	}

	void SceneMaster::AddScene(Scene* pScene)
	{
		if (!pScene) return;

		const std::string& name = pScene->GetName();
		SafeDelete(m_SceneMap[name]);

		m_SceneMap[name] = pScene;
		if (m_SceneMap.size() == 1) LoadScene(name);
	}

	void SceneMaster::LoadScene(const std::string& name)
	{
		// This scene does not exist...
		if (m_SceneMap.find(name) == m_SceneMap.cend()) return;

 		m_pActiveScene = m_SceneMap[name];
		m_pActiveScene->Load();
	}
	bool SceneMaster::IsEmpty() const
	{
		return m_SceneMap.empty();
	}
	Scene* SceneMaster::GetActiveScene() const
	{
		return m_pActiveScene;
	}
}