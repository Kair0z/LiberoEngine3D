#include "Liber_pch.h"
#include "RenderTarget.h"
#include "Libero/Graphics/GraphicsMaster.h"

namespace Libero
{
	RenderTarget::RenderTarget(ID3D11Device* pDevice)
		: m_pDevice{pDevice}
	{
		
	}

	void RenderTarget::Cleanup()
	{
		SafeRelease(m_pColorBuffer);
		SafeRelease(m_pDepthBuffer);
		SafeRelease(m_pRenderTargetView);
		SafeRelease(m_pColorSRV);
		SafeRelease(m_pDepthSRV);
		SafeRelease(m_pDepthStencilView);
	}

	void RenderTarget::Create(RT_Desc desc)
	{
		if (!desc.IsValid()) return;
		m_Properties = desc;

		// Clean Reset:
		Cleanup();

		CreateColor();
		CreateDepth();
	}

	void RenderTarget::CreateColor()
	{
		if (m_Properties.m_pColorBuffer)
		{
			m_pColorBuffer = m_Properties.m_pColorBuffer;

			D3D11_TEXTURE2D_DESC texDesc;
			ZeroMemory(&texDesc, sizeof(texDesc));

			m_pColorBuffer->GetDesc(&texDesc);
			m_Properties.m_W = (float)texDesc.Width;
			m_Properties.m_H = (float)texDesc.Height;
			m_Properties.m_ColorFormat = texDesc.Format;

			m_Properties.m_bColorSRV = (texDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE) == D3D11_BIND_SHADER_RESOURCE;
		}
		if (m_Properties.m_bColorBuffer)
		{
			if (m_pColorBuffer == nullptr)
			{
				//RESOURCE
				D3D11_TEXTURE2D_DESC textureDesc;
				ZeroMemory(&textureDesc, sizeof(textureDesc));

				textureDesc.Width = (UINT)m_Properties.m_W;
				textureDesc.Height = (UINT)m_Properties.m_H;
				textureDesc.MipLevels = 1;
				textureDesc.ArraySize = 1;
				textureDesc.Format = m_Properties.m_ColorFormat;
				textureDesc.SampleDesc.Count = 1;
				textureDesc.SampleDesc.Quality = 0;
				textureDesc.Usage = D3D11_USAGE_DEFAULT;
				textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | ((m_Properties.m_bColorSRV) ? D3D11_BIND_SHADER_RESOURCE : 0);
				textureDesc.CPUAccessFlags = 0;
				textureDesc.MiscFlags = ((m_Properties.m_bMipMaps_Color) ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0);

				m_pDevice->CreateTexture2D(&textureDesc, nullptr, &m_pColorBuffer);

				m_Properties.m_pColorBuffer = m_pColorBuffer;
			}

			//RENDERTARGET SRV
			m_pDevice->CreateRenderTargetView(m_pColorBuffer, nullptr, &m_pRenderTargetView);

			//SHADER SRV
			if (m_Properties.m_bColorSRV)
			{
				m_pDevice->CreateShaderResourceView(m_pColorBuffer, nullptr, &m_pColorSRV);
			}
		}
		else
		{
			SafeRelease(m_pColorBuffer);
			SafeRelease(m_pRenderTargetView);
			SafeRelease(m_pColorSRV);
		}
	}

	void RenderTarget::CreateDepth()
	{
		if (m_Properties.m_pDepthBuffer)
		{
			m_pDepthBuffer = m_Properties.m_pDepthBuffer;

			D3D11_TEXTURE2D_DESC texDesc;
			ZeroMemory(&texDesc, sizeof(texDesc));

			m_pDepthBuffer->GetDesc(&texDesc);
			m_Properties.m_W = (float)texDesc.Width;
			m_Properties.m_H = (float)texDesc.Height;
			m_Properties.m_DepthFormat = texDesc.Format;
		}

		if (m_Properties.m_bDepthBuffer)
		{
			if (!m_pDepthBuffer)
			{
				//RESOURCE
				D3D11_TEXTURE2D_DESC textureDesc;
				ZeroMemory(&textureDesc, sizeof(textureDesc));

				textureDesc.Width = (UINT)m_Properties.m_W;
				textureDesc.Height = (UINT)m_Properties.m_H;
				textureDesc.MipLevels = 1;
				textureDesc.ArraySize = 1;
				textureDesc.Format = GetDepthResourceFormat(m_Properties.m_DepthFormat);
				textureDesc.SampleDesc.Count = 1;
				textureDesc.SampleDesc.Quality = 0;
				textureDesc.Usage = D3D11_USAGE_DEFAULT;
				textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | ((m_Properties.m_bDepthSRV) ? D3D11_BIND_SHADER_RESOURCE : 0);
				textureDesc.MiscFlags = 0;

				m_pDevice->CreateTexture2D(&textureDesc, nullptr, &m_pDepthBuffer);

				m_Properties.m_pDepthBuffer = m_pDepthBuffer;
			}

			//DEPTHSTENCIL VIEW
			D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
			ZeroMemory(&descDSV, sizeof(descDSV));

			descDSV.Format = m_Properties.m_DepthFormat;
			descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			descDSV.Texture2D.MipSlice = 0;

			m_pDevice->CreateDepthStencilView(m_pDepthBuffer, &descDSV, &m_pDepthStencilView);

			//SHADER SRV
			if (m_Properties.m_bDepthSRV)
			{
				D3D11_SHADER_RESOURCE_VIEW_DESC depthSrvDesc;
				ZeroMemory(&depthSrvDesc, sizeof(depthSrvDesc));

				depthSrvDesc.Format = GetDepthSRVFormat(m_Properties.m_DepthFormat);
				depthSrvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				depthSrvDesc.Texture2D.MipLevels = 1;
				depthSrvDesc.Texture2D.MostDetailedMip = 0;

				m_pDevice->CreateShaderResourceView(m_pDepthBuffer, &depthSrvDesc, &m_pDepthSRV);
			}
		}
		else
		{
			SafeRelease(m_pDepthBuffer);
			SafeRelease(m_pDepthSRV);
		}
	}

	

	void RenderTarget::Clear(ID3D11DeviceContext* pDevCon, const ColorRGBA& color)
	{
		if (!pDevCon) return;

		FLOAT nColor[4]{ color.r, color.g, color.b, color.a };
		
		if (m_Properties.m_bColorBuffer)
			pDevCon->ClearRenderTargetView(GetRenderTargetView(), nColor);

		if (m_Properties.m_bDepthBuffer)
			pDevCon->ClearDepthStencilView(GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

#pragma region Get
	ID3D11RenderTargetView* RenderTarget::GetRenderTargetView() const
	{
		return m_pRenderTargetView;
	}

	ID3D11DepthStencilView* RenderTarget::GetDepthStencilView() const
	{
		return m_pDepthStencilView;
	}

	ID3D11ShaderResourceView* RenderTarget::GetColorSRV() const
	{
		return m_pColorSRV;
	}

	ID3D11ShaderResourceView* RenderTarget::GetDepthSRV() const
	{
		return m_pDepthSRV;
	}

	ID3D11ShaderResourceView* RenderTarget::GetTexture() 
	{
		GraphicsLocator::Get()->GetGraphicsContext().m_pDevice->CreateShaderResourceView(m_pColorBuffer, NULL, &m_pTextureSRV);
		return m_pTextureSRV;
	}

	DXGI_FORMAT RenderTarget::GetDepthResourceFormat(DXGI_FORMAT initFormat)
	{
		DXGI_FORMAT resourceFormat = {};
		switch (initFormat)
		{
		case DXGI_FORMAT::DXGI_FORMAT_D16_UNORM:
			resourceFormat = DXGI_FORMAT::DXGI_FORMAT_R16_TYPELESS;
			break;
		case DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT:
			resourceFormat = DXGI_FORMAT::DXGI_FORMAT_R24G8_TYPELESS;
			break;
		case DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT:
			resourceFormat = DXGI_FORMAT::DXGI_FORMAT_R32_TYPELESS;
			break;
		case DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
			resourceFormat = DXGI_FORMAT::DXGI_FORMAT_R32G8X24_TYPELESS;
			break;
		default:
			// Format not supported:
			break;
		}

		return resourceFormat;
	}

	DXGI_FORMAT RenderTarget::GetDepthSRVFormat(DXGI_FORMAT initFormat)
	{
		DXGI_FORMAT srvFormat = {};
		switch (initFormat)
		{
		case DXGI_FORMAT::DXGI_FORMAT_D16_UNORM:
			srvFormat = DXGI_FORMAT::DXGI_FORMAT_R16_FLOAT;
			break;
		case DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT:
			srvFormat = DXGI_FORMAT::DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
			break;
		case DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT:
			srvFormat = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
			break;
		case DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
			srvFormat = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
			break;
		default:
			//Format not supported
			break;
		}

		return srvFormat;
	}
#pragma endregion
}

