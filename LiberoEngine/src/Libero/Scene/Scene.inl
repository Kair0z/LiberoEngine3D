#include "Liber_pch.h"
#include "Scene.h"
#include "Libero/ECS/ECSMaster.h"
#include "Libero/Entities/GameObject.h"


namespace Libero
{
	inline Scene::Scene(const std::string& name)
		: m_Name{ name }
	{
	}

	inline GameObject* Scene::NewGameObject()
	{
		GameObject* pObject = ECSLocator::NewEntityAs<GameObject>();
		m_pObjects.push_back(pObject);
		return pObject;
	}

	inline void Scene::RemoveGameObject(GameObject*& pObj)
	{
		IEntity* pEntity = (IEntity*)pObj;
		ECSLocator::DestroyEntity(pEntity);

		// remove it from the list:
		m_pObjects.remove(pObj);

		pObj = nullptr;
	}

	template<class SysType, class ...Args>
	inline void Scene::LoadSystem(Args&& ...args)
	{
		ECSLocator::LoadSystem<SysType, Args...>(args...);
	}

	template<class SysType>
	inline void Scene::UnloadSystem()
	{
		//
	}

	inline const std::string& Scene::GetName() const
	{
		return m_Name;
	}
	inline std::list<GameObject*> Scene::GetObjects() const
	{
		return m_pObjects;
	}
}
