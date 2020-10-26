#pragma once
namespace Libero
{
	class ImageRenderer
	{
	public:
		struct ImageVertex
		{
			XMFLOAT4 TransformData;
			XMFLOAT4 TransformData2;
		};

		~ImageRenderer();
		void RenderImmediate(ID3D11ShaderResourceView* pSRV,
			XMFLOAT2 pos, XMFLOAT2 pivot = { 0, 0 }, XMFLOAT2 scale = { 1, 1 }, float rot = {});

		void Initialize();

	private:
		bool m_IsInitialized = false;

		ID3DX11Effect* m_pEffect;
		ID3DX11EffectTechnique* m_pTechnique;
		ID3D11InputLayout* m_pInputLayout;

		ID3D11Buffer* m_pImmediateVertexBuffer;

		ID3DX11EffectShaderResourceVariable* m_pTextureSRV;
		ID3DX11EffectVectorVariable* m_pTextureSizeVar;

		XMFLOAT4X4 m_Transform; // set in update:
		ID3DX11EffectMatrixVariable* m_pTransformMatrixVar;

		
	};
}


