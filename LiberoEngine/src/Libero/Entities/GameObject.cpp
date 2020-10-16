#include "Liber_pch.h"
#include "GameObject.h"
#include "Libero/Components/TransformComponent.h"

namespace Libero
{
	GameObject::GameObject(const std::string& name)
		: m_Name{name}
	{
		m_pChildren.reserve(20);
		
	}

	void GameObject::Initialize()
	{
		m_pTransform = AddComponent<TransformComponent>(TransformComponent());
	}

	void GameObject::AddChild(GameObject* pChild)
	{
		m_pChildren.push_back(pChild);
	}

	TransformComponent* GameObject::GetTransform()
	{
		return m_pTransform;
	}
}