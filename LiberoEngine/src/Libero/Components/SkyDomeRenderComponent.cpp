#include "Liber_pch.h"
#include "SkyDomeRenderComponent.h"
#include "Libero/Graphics/Mesh.h"
#include "Libero/Graphics/Skydome/SkyDome.h"
#include "Libero/Graphics/GraphicsMaster.h"
#include "Libero/Graphics/CameraMaster.h"
#include "Libero/Components/CameraComponent.h"
#include "Libero/Components/TransformComponent.h"

namespace Libero
{
	SkyDomeRenderComponent::SkyDomeRenderComponent(const std::string& effectFile)
		: m_EffectPath{effectFile}
	{
		m_pSkyDome = new SkyDome();

		Initialize();
	}

	SkyDomeRenderComponent::~SkyDomeRenderComponent()
	{
		SafeRelease(m_pCameraPosition);
		SafeRelease(m_pApexColor);
		SafeRelease(m_pBaseColor);
		SafeRelease(m_pWVP);
		SafeRelease(m_pIndexBuffer);
		SafeRelease(m_pVertexBuffer);
		SafeRelease(m_pInputLayout);
		SafeRelease(m_pEffect);

		SafeDelete(m_pSkyDome);
	}

	void SkyDomeRenderComponent::UpdateEffectVariables()
	{
		TransformComponent* pTransform = CameraMasterLocator::Get()->GetActiveCamera()->GetOwner()->GetComponent<TransformComponent>();
		m_CameraPosition = pTransform->GetPosition();

		if (m_pCameraPosition)
			m_pCameraPosition->SetFloatVector(&m_CameraPosition.x);

		if (m_pApexColor)
			m_pApexColor->SetFloatVector(&m_pSkyDome->GetApexColor().r);

		if (m_pBaseColor)
			m_pBaseColor->SetFloatVector(&m_pSkyDome->GetBaseColor().r);

		XMFLOAT4X4 vp;
		DirectX::XMStoreFloat4x4(&vp, CameraMasterLocator::Get()->GetActiveCamera()->GetViewProjection());
		if (m_pWVP)
			m_pWVP->SetMatrix(&vp.m[0][0]);
	}

	void SkyDomeRenderComponent::Initialize()
	{
		if (m_IsInitialized) return;

		InitEffect();

		InitMeshData();
		InitBuffer();

		m_IsInitialized = true;
	}

	void SkyDomeRenderComponent::Render() 
	{
		if (m_VertexBuffer.empty()) return;
		if (!m_pSkyDome) return;

		const GraphicsContext& grph = GraphicsLocator::Get()->GetGraphicsContext();
		
		UpdateEffectVariables();

		UINT offset = 0; UINT stride = sizeof(DomeVertex);
		grph.m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
		grph.m_pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		grph.m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		grph.m_pDeviceContext->IASetInputLayout(m_pInputLayout);

		D3DX11_TECHNIQUE_DESC techDesc;
		m_pTechnique->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			m_pTechnique->GetPassByIndex(p)->Apply(0, grph.m_pDeviceContext);
			grph.m_pDeviceContext->DrawIndexed((UINT)m_IndexBuffer.size(), 0, 0);
		}
	}

	void SkyDomeRenderComponent::InitMeshData()
	{
		m_VertexBuffer.clear();
		m_IndexBuffer.clear();

		Mesh* pMesh = m_pSkyDome->GetMesh();

		// Setup indexbuffer
		for (size_t f{}; f < pMesh->GetMesh()->mNumFaces; ++f)
		{
			const aiFace* face = &pMesh->GetMesh()->mFaces[f];
			for (size_t i{}; i < face->mNumIndices; ++i)
				m_IndexBuffer.push_back((uint32_t)face->mIndices[i]);
		}

		// Set up mesh data: (only positions)
		for (size_t i{}; i < pMesh->GetMesh()->mNumVertices; ++i)
		{
			aiVector3D pVertex = pMesh->GetMesh()->mVertices[i];

			m_VertexBuffer.push_back({ pVertex.x, pVertex.y, pVertex.z });
		}
	}

	void SkyDomeRenderComponent::InitBuffer()
	{
		// Vertexbuffer:
		if (m_pVertexBuffer) SafeRelease(m_pVertexBuffer);

		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.ByteWidth = sizeof(DomeVertex) * (UINT)m_VertexBuffer.size();
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		bufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		bufferDesc.MiscFlags = 0;
		HRESULT res = GraphicsLocator::Get()->GetGraphicsContext().m_pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pVertexBuffer);
	
		// Indexbuffer:
		if (m_pIndexBuffer) SafeRelease(m_pIndexBuffer);

		D3D11_BUFFER_DESC idxDesc;
		idxDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		idxDesc.ByteWidth = sizeof(uint32_t) * (UINT)m_IndexBuffer.size();
		idxDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		idxDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		idxDesc.MiscFlags = 0;
		GraphicsLocator::Get()->GetGraphicsContext().m_pDevice->CreateBuffer(&idxDesc, nullptr, &m_pIndexBuffer);
		res;

		// FILL IT UP WITH THE INITIAL DATA
		const GraphicsContext& grphContext = GraphicsLocator::Get()->GetGraphicsContext();

		D3D11_MAPPED_SUBRESOURCE mappedR;
		grphContext.m_pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedR);
		memcpy(mappedR.pData, m_VertexBuffer.data(), sizeof(DomeVertex) * m_VertexBuffer.size());
		grphContext.m_pDeviceContext->Unmap(m_pVertexBuffer, 0);

		D3D11_MAPPED_SUBRESOURCE mappedRes;
		grphContext.m_pDeviceContext->Map(m_pIndexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedRes);
		memcpy(mappedRes.pData, m_IndexBuffer.data(), sizeof(uint32_t) * m_IndexBuffer.size());
		grphContext.m_pDeviceContext->Unmap(m_pIndexBuffer, 0);
	}

	void SkyDomeRenderComponent::InitEffect()
	{
		// Load the effect:
#pragma region LoadEffect
		const GraphicsContext& graphicsContext = GraphicsLocator::Get()->GetGraphicsContext();
		HRESULT hr;
		ID3D10Blob* pErrBlob = nullptr;
		ID3DX11Effect* pEffect;
		DWORD shaderFlags = 0;

		hr = D3DX11CompileEffectFromFile(s2ws(m_EffectPath).c_str(),
			nullptr,
			nullptr,
			shaderFlags,
			0,
			graphicsContext.m_pDevice,
			&pEffect,
			&pErrBlob);

		if (hr != S_OK)
		{
			std::string val = (char*)pErrBlob;
			val;
		}

		m_pEffect = pEffect;
		m_pTechnique = m_pEffect->GetTechniqueByIndex(0);

		D3D11_INPUT_ELEMENT_DESC layout [1] = 
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		
		D3DX11_PASS_DESC passDesc;
		m_pTechnique->GetPassByIndex(0)->GetDesc(&passDesc);
		const auto res = graphicsContext.m_pDevice->CreateInputLayout(layout, 1, passDesc.pIAInputSignature,
			passDesc.IAInputSignatureSize, &m_pInputLayout);
#pragma endregion

		// Load Effect Variables:
#pragma region LoadVariables
		if (!m_pCameraPosition)
			m_pCameraPosition = m_pEffect->GetVariableByName("gCameraPosition")->AsVector();

		if (!m_pBaseColor)
			m_pBaseColor = m_pEffect->GetVariableByName("gColorBase")->AsVector();

		if (!m_pApexColor)
			m_pApexColor = m_pEffect->GetVariableByName("gColorApex")->AsVector();

		if (!m_pWVP)
			m_pWVP = m_pEffect->GetVariableByName("gWVP")->AsMatrix();
#pragma endregion
	}


#pragma region GettingSetting
	void SkyDomeRenderComponent::SetBaseColor(const ColorRGB& col)
	{
		m_pSkyDome->SetBaseColor(col);
	}

	void SkyDomeRenderComponent::SetApexColor(const ColorRGB& col)
	{
		m_pSkyDome->SetApexColor(col);
	}

	ColorRGB SkyDomeRenderComponent::GetBaseColor() const
	{
		return m_pSkyDome->GetBaseColor();
	}

	ColorRGB SkyDomeRenderComponent::GetApexColor() const
	{
		return m_pSkyDome->GetApexColor();
	}
#pragma endregion
}