#pragma once
#include "Libero/Math/LiberoMath.h"
#include "Libero/ECS/Core/Component.h"

namespace Libero
{
	class TransformComponent final : public Component<TransformComponent>
	{
	public:
		enum class eSpace
		{
			World,
			Local
		};

		struct PRS // Position Rotation Scale
		{
			Vector3f Position{};
			Vector3f Rotation{};
			Vector3f Scale{1.f, 1.f, 1.f};
		};

	public:
		Vector3f GetScale() const;
		void SetScale(float uniScale);

		XMMATRIX GetWorldMatrix() const;
		XMMATRIX GetLocalMatrix() const;

		DefGet(Vector3f, Position, m_Local.Position);
		DefGet(Vector3f, Rotation, m_Local.Rotation);

		// Transform functions:
		void SetPosition(const Vector3f& pos);
		void SetRotation(const Vector3f& eulers);

		void Translate(const Vector3f& trans, eSpace inSpace = eSpace::World);
		void Rotate(const Vector3f& eulers, eSpace inSpace = eSpace::World);

		void LookAt(const Vector3f& target);

		Vector3f GetUp() const;
		Vector3f GetRight() const;
		Vector3f GetForward() const;

		bool HasParent() const;
		void AddChild(TransformComponent* pChild);
		void UpdateChildren(XMMATRIX parentWorld);

	private:
		PRS m_Local{};
		PRS m_World{};
		
		XMMATRIX m_WorldMatrix = XMMatrixIdentity();
		XMMATRIX m_LocalMatrix = XMMatrixIdentity();

		std::list<TransformComponent*> m_pChildren{};
		bool m_IsDirty{ false };
		bool m_HasParent{ false };

		void UpdateMatrices();
		PRS DataFromMatrix(XMMATRIX mat);
	};
}


