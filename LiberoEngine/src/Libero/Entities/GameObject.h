#pragma once
#include "Libero/API.h"
#include "Libero/ECS/Core/Entity.h"
#include <string>
#include <vector>

// Gameobject: 
// Entity with transform in scene:

namespace Libero
{
	class TransformComponent;
	class GameObject final : public Entity<GameObject>
	{
	public:
		GameObject(const std::string& name = "GameObject");
		~GameObject() = default;

		void Initialize() override;
		void AddChild(GameObject* pChild);

		DefGetSet(std::string, Name, m_Name);

		TransformComponent* GetTransform();

	private:
		std::string m_Name = "GameObject";
		std::vector<GameObject*> m_pChildren;
		TransformComponent* m_pTransform;
	};
}


