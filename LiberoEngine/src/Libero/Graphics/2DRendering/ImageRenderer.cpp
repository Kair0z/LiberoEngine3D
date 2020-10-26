#include "Liber_pch.h"
#include "ImageRenderer.h"
#include "Libero/Graphics/GraphicsMaster.h"
#include "Libero/Settings/Settings.h"

namespace Libero
{
	ImageRenderer::~ImageRenderer()
	{
		SafeRelease(m_pEffect);
		SafeRelease(m_pImmediateVertexBuffer);
	}
	void ImageRenderer::Initialize()
	{
		if (m_IsInitialized) return;

#pragma region Effect & Technique
		const GraphicsContext& graphicsContext = GraphicsLocator::Get()->GetGraphicsContext();

		HRESULT hr;
		ID3D10Blob* pErrBlob = nullptr;
		ID3DX11Effect* pEffect;
		DWORD shaderFlags = 0;

		hr = D3DX11CompileEffectFromFile(s2ws("../Resources/Core/Effects/ImageRenderer.fx").c_str(),
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

#pragma endregion

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},

			{ "DATA", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		const auto numElements = 2;

		D3DX11_PASS_DESC passDesc;
		m_pTechnique->GetPassByIndex(0)->GetDesc(&passDesc);
		const auto res = graphicsContext.m_pDevice->CreateInputLayout(layout, numElements, passDesc.pIAInputSignature,
			passDesc.IAInputSignatureSize, &m_pInputLayout);

		m_pTransformMatrixVar = m_pEffect->GetVariableByName("gTransform")->AsMatrix();
		m_pTextureSizeVar = m_pEffect->GetVariableByName("gTextureSize")->AsVector();
		m_pTextureSRV = m_pEffect->GetVariableByName("gSpriteTexture")->AsShaderResource();

		// Transform matrix:
		const auto windowSettings = Settings::Window;
		const float x = 2.0f / windowSettings.Dimensions.x;
		const float y = 2.0f / windowSettings.Dimensions.y;

		m_Transform._11 = x;
		m_Transform._12 = 0;
		m_Transform._13 = 0;
		m_Transform._14 = 0;
		m_Transform._21 = 0;
		m_Transform._22 = -y;
		m_Transform._23 = 0;
		m_Transform._24 = 0;
		m_Transform._31 = 0;
		m_Transform._32 = 0;
		m_Transform._33 = 1;
		m_Transform._34 = 0;
		m_Transform._41 = -1;
		m_Transform._42 = 1;
		m_Transform._43 = 0;
		m_Transform._44 = 1;

		m_IsInitialized = true;
	}
	void ImageRenderer::RenderImmediate(ID3D11ShaderResourceView* pSRV, XMFLOAT2 pos, XMFLOAT2 pivot, XMFLOAT2 scale, float rot)
	{
		GraphicsContext ctx = GraphicsLocator::Get()->GetGraphicsContext();
		if (!m_pImmediateVertexBuffer)
		{
			// Create VB
			D3D11_BUFFER_DESC buffDesc;
			buffDesc.Usage = D3D11_USAGE_DYNAMIC;
			buffDesc.ByteWidth = sizeof(ImageVertex);
			buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			buffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			buffDesc.MiscFlags = 0;

			ctx.m_pDevice->CreateBuffer(&buffDesc, nullptr, &m_pImmediateVertexBuffer);
		}
		
		// Map data:
		ImageVertex vertex;
		vertex.TransformData = XMFLOAT4(pos.x, pos.y, 0, rot);
		vertex.TransformData2 = XMFLOAT4(pivot.x, pivot.y, scale.x, scale.y);
		
		D3D11_MAPPED_SUBRESOURCE mapped;
		ctx.m_pDeviceContext->Map(m_pImmediateVertexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mapped);
		memcpy(mapped.pData, &vertex, sizeof(ImageVertex));
		ctx.m_pDeviceContext->Unmap(m_pImmediateVertexBuffer, 0);

		// Set pipeline:
		ctx.m_pDeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);
		UINT stride = sizeof(ImageVertex);
		UINT offset = 0;
		ctx.m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pImmediateVertexBuffer, &stride, &offset);
		ctx.m_pDeviceContext->IASetInputLayout(m_pInputLayout);

		// Set texture:
		m_pTextureSRV->SetResource(pSRV);

		ID3D11Resource* pRes;
		pSRV->GetResource(&pRes);
		D3D11_TEXTURE2D_DESC texDesc;
		auto texRes = reinterpret_cast<ID3D11Texture2D*>(pRes);
		texRes->GetDesc(&texDesc);
		texRes->Release();

		auto texSize = XMFLOAT2((float)texDesc.Width, (float)texDesc.Height);
		m_pTextureSizeVar->SetFloatVector(reinterpret_cast<float*>(&texSize));

		m_pTransformMatrixVar->SetMatrix(reinterpret_cast<float*>(&m_Transform));

		D3DX11_TECHNIQUE_DESC techDesc;
		m_pTechnique->GetDesc(&techDesc);
		for (uint32_t i{}; i < techDesc.Passes; ++i)
		{
			m_pTechnique->GetPassByIndex(i)->Apply(0, ctx.m_pDeviceContext);
			ctx.m_pDeviceContext->Draw(1, 0);
		}
	}
	
}

