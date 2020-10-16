#include "Liber_pch.h"
#include "MeshRenderComponent.h"
#include "Libero/Graphics/GraphicsMaster.h"
#include "Libero/Graphics/CameraMaster.h"
#include "Libero/Components/CameraComponent.h"
#include "Libero/Components/TransformComponent.h"
#include "Libero/Content/ContentMaster.h"
#include "Libero/Components/MeshFilterComponent.h"
#include "Libero/Graphics/DXUtils.h"
#include "Libero/Graphics/Materials/MaterialMaster.h"
#include "Libero/Graphics/Materials/Material.h"

#include "assimp/mesh.h"

namespace Libero
{
	MeshRenderComponent::~MeshRenderComponent()
	{
		SafeRelease(m_pVertexBuffer);
		SafeRelease(m_pIndexBuffer);
	}

	void MeshRenderComponent::Initialize(MeshFilterComponent* pMeshFilter)
	{
		using namespace DirectX;
		if (m_IsInitialized) return;

		// Setup default material:
		//m_pDefaultMaterial = MaterialLocator::Get()->CreateMaterial<

		InitMeshData(pMeshFilter);
		InitBuffer();
		UpdateBuffer();

		m_IsInitialized = true;
	}

	void MeshRenderComponent::InitMeshData(MeshFilterComponent* pMeshFilter)
	{
		m_VertexBuffer.clear();
		m_IndexBuffer.clear();

		if (!pMeshFilter) return;

		Mesh* pMesh = pMeshFilter->GetMesh();

		// Setup indexbuffer
		for (size_t f{}; f < pMesh->GetMesh()->mNumFaces; ++f)
		{
			const aiFace* face = &pMesh->GetMesh()->mFaces[f];

			for (size_t i{}; i < face->mNumIndices; ++i)
			{
				m_IndexBuffer.push_back((uint32_t)face->mIndices[i]);
			}
		}

		// Set up mesh data:
		for (size_t i{}; i < pMesh->GetMesh()->mNumVertices; ++i)
		{
			XMFLOAT3 pos{}; XMFLOAT2 uv{}; XMFLOAT4 col{}; XMFLOAT3 norm{}; XMFLOAT3 tan{};

			col.w = 1.f;
			switch (i % 3)
			{
			case 0: col.x = 1.f; break;
			case 1: col.y = 1.f; break;
			case 2: col.z = 1.f; break;
			}

			if (pMesh->GetMesh()->mVertices) pos = XMFLOAT3(&pMesh->GetMesh()->mVertices[i].x);
			uv = { pMesh->GetMesh()->mTextureCoords[0][i].x, 1.f - pMesh->GetMesh()->mTextureCoords[0][i].y };
			if (pMesh->GetMesh()->mNormals) norm = XMFLOAT3(&pMesh->GetMesh()->mNormals[i].x);
			if (pMesh->GetMesh()->mTangents) tan = XMFLOAT3(&pMesh->GetMesh()->mTangents[i].x);

			Vertex vert{ pos, uv, col, norm, tan };
			m_VertexBuffer.push_back(vert);
		}
	}

	void MeshRenderComponent::InitBuffer()
	{
		if (m_pVertexBuffer)
			SafeRelease(m_pVertexBuffer);

		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.ByteWidth = sizeof(Vertex) * (UINT)m_VertexBuffer.size();
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		bufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		bufferDesc.MiscFlags = 0;

		GraphicsLocator::Get()->GetGraphicsContext().m_pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pVertexBuffer);

		if (m_pIndexBuffer)
			SafeRelease(m_pIndexBuffer);

		D3D11_BUFFER_DESC idxDesc;
		idxDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		idxDesc.ByteWidth = sizeof(uint32_t) * (UINT)m_IndexBuffer.size();
		idxDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		idxDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		idxDesc.MiscFlags = 0;

		GraphicsLocator::Get()->GetGraphicsContext().m_pDevice->CreateBuffer(&idxDesc, nullptr, &m_pIndexBuffer);
	}

	void MeshRenderComponent::UpdateBuffer()
	{
		const GraphicsContext& grphContext = GraphicsLocator::Get()->GetGraphicsContext();
		size_t nrVertices = m_VertexBuffer.size();

		if (nrVertices > 0)
		{
			D3D11_MAPPED_SUBRESOURCE mappedRes;
			grphContext.m_pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedRes);
			memcpy(mappedRes.pData, m_VertexBuffer.data(), sizeof(Vertex) * nrVertices);
			grphContext.m_pDeviceContext->Unmap(m_pVertexBuffer, 0);
		}

		size_t nrIndices = m_IndexBuffer.size();

		if (nrIndices > 0)
		{
			D3D11_MAPPED_SUBRESOURCE mappedRes;
			grphContext.m_pDeviceContext->Map(m_pIndexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedRes);
			memcpy(mappedRes.pData, m_IndexBuffer.data(), sizeof(uint32_t) * nrIndices);
			grphContext.m_pDeviceContext->Unmap(m_pIndexBuffer, 0);
		}
	}
	

	void MeshRenderComponent::SetMaterial(IMaterial* pMaterial)
	{
		m_pMaterial = pMaterial;
	}

	void MeshRenderComponent::Render()
	{
		if (m_VertexBuffer.empty()) return;
		if (!m_pMaterial) return;

		const GraphicsContext& grph = GraphicsLocator::Get()->GetGraphicsContext();
		TransformComponent* pTransform = GetOwner()->GetComponent<TransformComponent>();

		m_pMaterial->UpdateEffectVariables(pTransform);
	
		grph.m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		grph.m_pDeviceContext->IASetInputLayout(m_pMaterial->GetDX().m_pInputLayout);

		UINT offset = 0;
		UINT stride = sizeof(Vertex);
		grph.m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
		grph.m_pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		D3DX11_TECHNIQUE_DESC techDesc;
		m_pMaterial->GetDX().m_pTechnique->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			m_pMaterial->GetDX().m_pTechnique->GetPassByIndex(p)->Apply(0, grph.m_pDeviceContext);
			grph.m_pDeviceContext->DrawIndexed((UINT)m_IndexBuffer.size(), 0, 0);
		}
	}
}
