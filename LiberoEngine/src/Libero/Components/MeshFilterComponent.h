#pragma once
#include "Libero/ECS/Core/Component.h"

namespace Libero
{
	class Mesh;
	class MeshFilterComponent final :
		public Component<MeshFilterComponent>
	{
	public:
		MeshFilterComponent(Mesh* pMesh);
		Mesh* GetMesh() const;

	private:
		Mesh* m_pMesh = nullptr;
	};
}


