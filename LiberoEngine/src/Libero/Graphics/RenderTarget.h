#pragma once
#include "../Math/LiberoMath.h"

namespace Libero
{
	struct RT_Desc
	{
	public:
		float m_W{-1.f};
		float m_H{-1.f};

		bool m_bDepthBuffer = true;
		bool m_bDepthSRV = false;
		bool m_bColorBuffer = true;
		bool m_bColorSRV = false;
		bool m_bMipMaps_Color = false;

		DXGI_FORMAT m_DepthFormat = DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;
		DXGI_FORMAT m_ColorFormat = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;

		ID3D11Texture2D* m_pColorBuffer = nullptr;
		bool m_bColorBufferSupplied = false;
		ID3D11Texture2D* m_pDepthBuffer = nullptr;
		bool m_bDepthBufferSupplied = false;

		bool IsValid() const
		{
			// No color OR depth
			if (!m_pColorBuffer && m_bColorBufferSupplied) return false;
			if (!m_pDepthBuffer && m_bDepthBufferSupplied) return false;

			// Invalid dimensions
			if (m_W <= 0.f || m_H <= 0.f) return false;

			// Obvious
			if (m_bDepthSRV && !m_bDepthBuffer) return false;
			if (m_bColorSRV && !m_bColorBuffer) return false;

			return true;
		}
	};

	class RenderTarget final
	{
	public:
		RenderTarget(ID3D11Device* pDevice);
		~RenderTarget() { Cleanup(); };

		void Create(RT_Desc desc);
		ID3D11RenderTargetView* GetRenderTargetView() const;
		ID3D11DepthStencilView* GetDepthStencilView() const;
		ID3D11ShaderResourceView* GetColorSRV() const;
		ID3D11ShaderResourceView* GetDepthSRV() const;
		ID3D11ShaderResourceView* GetTexture();

		void Clear(ID3D11DeviceContext* pDevCon, const ColorRGBA& color);

	private:
		RT_Desc m_Properties;
		ID3D11Device* m_pDevice = nullptr;
		ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
		ID3D11ShaderResourceView* m_pColorSRV = nullptr;
		ID3D11ShaderResourceView* m_pDepthSRV = nullptr;
		ID3D11ShaderResourceView* m_pTextureSRV = nullptr;
		ID3D11Texture2D* m_pColorBuffer = nullptr;
		ID3D11Texture2D* m_pDepthBuffer = nullptr;
		ID3D11DepthStencilView* m_pDepthStencilView = nullptr;

	private:
		void CreateColor();
		void CreateDepth();
		void CreateTexture();
		static DXGI_FORMAT GetDepthResourceFormat(DXGI_FORMAT initFormat);
		static DXGI_FORMAT GetDepthSRVFormat(DXGI_FORMAT initFormat);
		void Cleanup();
	};
}


