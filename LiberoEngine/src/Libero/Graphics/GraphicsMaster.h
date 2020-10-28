#pragma once
#include <d3d11.h>
#include "Libero/Interfaces/ILocator.h"

namespace Libero
{
	struct Settings;
	class RenderTarget;
	class Texture2D;

	struct GraphicsContext
	{
		ID3D11Device* m_pDevice = nullptr;
		ID3D11DeviceContext* m_pDeviceContext = nullptr;
		RenderTarget* m_pCurrentRenderTarget = nullptr;
		HWND m_WindowHandle;
	};

	class GraphicsMaster final
	{
	public:
		GraphicsMaster();
		~GraphicsMaster();

		void Initialize(HINSTANCE winInstance);
		void SetRenderTarget(RenderTarget* pRenderTarget);

		void OpenGameRender();
		void OpenWindowRender();
		void Present();

		ID3D11ShaderResourceView* GetGameFrame();
		void RenderGameFrame();

		Texture2D* CreateTexture(const std::string& fName) const;

		GraphicsContext GetGraphicsContext();

	private:
		bool m_IsInitialized;

		void InitWindow();
		void InitDX();
		void InitRenderTargets();

		// ImageRenderer:
		class ImageRenderer* m_pImageRenderer;
		class DebugRenderer* m_pDebugRenderer;

		// Window/DX-related data:
		HINSTANCE m_WinInstance;
		HWND m_WindowHandle;
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;
		IDXGISwapChain* m_pSwapchain;
		IDXGIFactory* m_pDXGIFactory;

		RenderTarget* m_pCurrentRenderTarget = nullptr;
		RenderTarget* m_pMainWindowRenderTarget = nullptr;
		RenderTarget* m_pGameRenderTarget = nullptr;

		D3D11_VIEWPORT m_Viewport;
	};

	class GraphicsLocator : public ILocator<GraphicsMaster>{};
}

