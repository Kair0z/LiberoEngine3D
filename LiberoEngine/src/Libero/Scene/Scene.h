#pragma once
#include <list>
#include <string>

namespace Libero
{
	class GameObject;
	class Scene
	{
	public:
		virtual ~Scene() = default;
		virtual void Load() = 0;

		GameObject* NewGameObject();
		void RemoveGameObject(GameObject*& pObj);
		const std::string& GetName() const;

		template <class SysType, class ...Args>
		void LoadSystem(Args&&... args);

		template <class SysType>
		void UnloadSystem();

		std::list<GameObject*> GetObjects() const;
	protected:
		Scene(const std::string& name = "Default Scene");

	private:
		std::list<GameObject*> m_pObjects;
		std::string m_Name;
	};
}

#include "Scene.inl"


