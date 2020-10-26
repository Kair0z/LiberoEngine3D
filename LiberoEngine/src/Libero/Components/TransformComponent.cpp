#include "Liber_pch.h"
#include "TransformComponent.h"

namespace Libero
{
	void TransformComponent::UpdateMatrices()
	{
		XMMATRIX pos = XMMatrixTranslation(m_Local.Position.x, m_Local.Position.y, m_Local.Position.z);
		XMMATRIX scale = XMMatrixScaling(m_Local.Scale.x, m_Local.Scale.y, m_Local.Scale.z);
		XMMATRIX rot = XMMatrixRotationRollPitchYaw(m_Local.Rotation.x, m_Local.Rotation.y, m_Local.Rotation.z);
		
		m_LocalMatrix = scale * rot * pos;
	}

	TransformComponent::PRS TransformComponent::DataFromMatrix(XMMATRIX mat)
	{
		PRS data{};

		XMVECTOR trans{};
		XMVECTOR rotQuat{};
		XMVECTOR scale{};

		XMMatrixDecompose(&scale, &rotQuat, &trans, mat);

	
		XMFLOAT3 pos = ToXMFLOAT3(trans);
		data.Position = { pos.x, pos.y, pos.z };

		XMFLOAT3 sc = ToXMFLOAT3(scale);
		data.Scale = { sc.x, sc.y, sc.z };

		data.Rotation = {};

		return data;
	}

	bool TransformComponent::HasParent() const
	{
		return m_HasParent;
	}

	void TransformComponent::AddChild(TransformComponent* pChild)
	{
		m_pChildren.push_back(pChild);
	}

	void TransformComponent::UpdateChildren(XMMATRIX parentWorld)
	{
		// Calculate my new world:
		// Update world data from matrix:
		m_WorldMatrix = parentWorld * m_LocalMatrix;
		m_World = DataFromMatrix(m_WorldMatrix);

		for (TransformComponent* pChild : m_pChildren)
		{
			// Pass it through to children:
			pChild->UpdateChildren(m_WorldMatrix);

			// Set dirty bit false
			pChild->m_IsDirty = false;
		}
	}

	void TransformComponent::SetPosition(const Vector3f& pos)
	{
		m_Local.Position = pos;
		UpdateMatrices();
	}

	void TransformComponent::SetRotation(const Vector3f& eulers)
	{
		m_Local.Rotation = eulers;
		UpdateMatrices();
	}

	Vector3f TransformComponent::GetScale() const
	{
		return m_Local.Scale;
	}

	void TransformComponent::SetScale(float uniScale)
	{
		m_Local.Scale = { uniScale, uniScale, uniScale };
		UpdateMatrices();
	}


	void TransformComponent::Translate(const Vector3f& trans, eSpace inSpace)
	{
		switch (inSpace)
		{
		case eSpace::World:
			m_Local.Position += trans;
			break;

		case eSpace::Local:
			m_Local.Position += (GetRight() * trans.x + GetUp()* trans.y + GetForward()* trans.z);
			break;
		}
		
		UpdateMatrices();
	}

	void TransformComponent::Rotate(const Vector3f& eulers, eSpace inSpace)
	{
		switch (inSpace)
		{
		case eSpace::World:
			m_Local.Rotation += eulers;
			break;

		case eSpace::Local:
			m_Local.Rotation += eulers;
			break;
		}
		
		UpdateMatrices();
	}

	void TransformComponent::LookAt(const Vector3f& target)
	{

	}

	Vector3f TransformComponent::GetRight() const
	{
		XMFLOAT4X4 world;
		XMStoreFloat4x4(&world, m_WorldMatrix);
		return { world.m[0][0], world.m[0][1], world.m[0][2] };
	}
	Vector3f TransformComponent::GetForward() const
	{
		XMFLOAT4X4 world;
		XMStoreFloat4x4(&world, m_WorldMatrix);
		return { world.m[2][0], world.m[2][1], world.m[2][2] };
	}
	Vector3f TransformComponent::GetUp() const
	{
		XMFLOAT4X4 world;
		XMStoreFloat4x4(&world, m_WorldMatrix);
		return { world.m[1][0], world.m[1][1], world.m[1][2] };
	}

	XMMATRIX TransformComponent::GetWorldMatrix() const
	{
		return m_LocalMatrix;
	}
	XMMATRIX TransformComponent::GetLocalMatrix() const
	{
		return m_LocalMatrix;
	}
}

