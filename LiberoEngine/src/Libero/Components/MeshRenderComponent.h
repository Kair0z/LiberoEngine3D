#pragma once
#include "Libero/API.h"
#include "Libero/ECS/Core/Component.h"
#include "Libero/Graphics/Vertex.h"
#include "assimp/mesh.h"

#pragma region DX
struct ID3DX11EffectMatrixVariable;
struct ID3DX11EffectTechnique;
struct ID3D11InputLayout;
struct ID3DX11Effect;
struct ID3D11Buffer;
#pragma endregion

namespace Libero
{
	class IMaterial;
	class MeshFilterComponent;
	class MeshRenderComponent final  
		: public Component<MeshRenderComponent>
	{
	public:
		MeshRenderComponent() = default;
		~MeshRenderComponent();

		void Initialize(MeshFilterComponent* pMeshFilter);
		void UpdateBuffer();

		DefGetSet(size_t, VertexCapacity, m_VertexCapacity);

		void SetMaterial(IMaterial* pMaterial);
		IMaterial* GetMaterial() const;

		void Render();

	private:
		using Vertex = VertexPosTexColNormTan;
		std::vector<Vertex> m_VertexBuffer;
		std::vector<uint32_t> m_IndexBuffer;
		ID3D11Buffer* m_pVertexBuffer = nullptr;
		ID3D11Buffer* m_pIndexBuffer = nullptr;
		size_t m_VertexCapacity = 50;

		IMaterial* m_pMaterial = nullptr;
		IMaterial* m_pDefaultMaterial = nullptr;

		void InitMeshData(MeshFilterComponent* pMeshFilter);
		void InitBuffer();

		bool m_IsInitialized = false;
	};
}


