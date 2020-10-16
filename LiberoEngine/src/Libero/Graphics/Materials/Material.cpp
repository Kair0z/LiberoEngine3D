#include "Liber_pch.h"
#include "Material.h"
#include "Libero/Graphics/GraphicsMaster.h"


namespace Libero
{
	IMaterial::IMaterial(const std::string& effectFile, const std::string& techName)
		: m_EffectPath{effectFile}
		, m_TechniqueName{techName}
	{
	}

	void IMaterial::Initialize()
	{
		LoadEffect();
		LoadEffectVariables();
	}

	void IMaterial::LoadEffect()
	{
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

		m_DXData.m_pEffect = pEffect; 
		m_DXData.m_pTechnique = m_DXData.m_pEffect->GetTechniqueByIndex(0);

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},

			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 3 * 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 5 * 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 9 * 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, (3 + 2 + 4 + 3) * 4, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		const auto numElements = 5;

		D3DX11_PASS_DESC passDesc;
		m_DXData.m_pTechnique->GetPassByIndex(0)->GetDesc(&passDesc);
		const auto res = graphicsContext.m_pDevice->CreateInputLayout(layout, numElements, passDesc.pIAInputSignature,
			passDesc.IAInputSignatureSize, &m_DXData.m_pInputLayout);
	}

	const IMaterial::DXData& IMaterial::GetDX() const
	{
		return m_DXData;
	}

	
}

