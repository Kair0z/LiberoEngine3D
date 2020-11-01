#include "Liber_pch.h"
#include "GraphicsMaster.h"
#include "RenderTarget.h"
#include "Libero/Settings/Settings.h"	
#include "Libero/Engine/Engine.h"
#include "Texture2D.h"
#include "Colors.h"
#include "2DRendering/ImageRenderer.h"
#include "DebugRendering/DebugRenderer.h"

namespace Libero
{
	using namespace Math;
	GraphicsMaster::GraphicsMaster()
		: m_IsInitialized{false}
	{

	}

	GraphicsMaster::~GraphicsMaster()
	{
		SafeRelease(m_pDevice);
		SafeRelease(m_pDeviceContext);
		SafeRelease(m_pSwapchain);
		SafeRelease(m_pDXGIFactory);

		SafeDelete(m_pMainWindowRenderTarget);
		SafeDelete(m_pGameRenderTarget);
		SafeDelete(m_pImageRenderer);
		SafeDelete(m_pDebugRenderer);
	}

	void GraphicsMaster::Initialize(HINSTANCE winInstance)
	{
		if (m_IsInitialized) return;

		m_WinInstance = winInstance;

		InitWindow();
		InitDX();
		InitRenderTargets();

		m_IsInitialized = true;
		GraphicsLocator::Provide(this);

		m_pImageRenderer = new ImageRenderer();
		m_pImageRenderer->Initialize();
	}

	void GraphicsMaster::SetRenderTarget(RenderTarget* pRT)
	{
		if (!pRT) return;

		ID3D11ShaderResourceView* nullSRVs[1] = { nullptr };
		m_pDeviceContext->PSSetShaderResources(0, 1, nullSRVs);

		auto rtView = pRT->GetRenderTargetView();
		m_pDeviceContext->OMSetRenderTargets(1, &rtView, pRT->GetDepthStencilView());

		m_pCurrentRenderTarget = pRT;
	}


	void GraphicsMaster::OpenGameRender()
	{
		SetRenderTarget(m_pGameRenderTarget);
		ColorRGBA color = WithAlpha(Libero::Colors::Purple, 1.f);
		m_pDeviceContext->ClearRenderTargetView(m_pCurrentRenderTarget->GetRenderTargetView(), &color.x);
		m_pDeviceContext->ClearDepthStencilView(m_pCurrentRenderTarget->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void GraphicsMaster::OpenWindowRender()
	{
		SetRenderTarget(m_pMainWindowRenderTarget);
		const float color[4]{ 0.f, 0.f, 0.f, 255.f };
		m_pDeviceContext->ClearRenderTargetView(m_pCurrentRenderTarget->GetRenderTargetView(), color);
		m_pDeviceContext->ClearDepthStencilView(m_pCurrentRenderTarget->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	}

	void GraphicsMaster::Present()
	{
		// Present Backbuffer
		m_pSwapchain->Present(0, 0);
	}

	ID3D11ShaderResourceView* GraphicsMaster::GetGameFrame()
	{
		return m_pGameRenderTarget->GetColorSRV();
	}

	void GraphicsMaster::RenderGameFrame()
	{
		m_pImageRenderer->RenderImmediate(GetGameFrame(), {});
	}

	Texture2D* GraphicsMaster::CreateTexture(const std::string& fName) const
	{
		Texture2D* res = new Texture2D();
		std::wstring wName = s2ws(fName);
		CreateWICTextureFromFile(m_pDevice, wName.c_str(), (ID3D11Resource**)&res->m_pTexture, &res->m_pSRV);

		D3D11_TEXTURE2D_DESC desc{};
		res->m_pTexture->GetDesc(&desc);

		res->m_Data.m_Dimensions = { (float)desc.Width, (float)desc.Height };
		res->m_Data.m_Filename = fName;

		return res;
	}

	GraphicsContext GraphicsMaster::GetGraphicsContext()
	{
		GraphicsContext ctx{};
		ctx.m_pCurrentRenderTarget = nullptr;
		ctx.m_pDevice = nullptr;
		ctx.m_pDeviceContext = nullptr;
		ctx.m_WindowHandle = m_WindowHandle;

		if (!m_IsInitialized) return ctx;

		ctx.m_pCurrentRenderTarget = m_pCurrentRenderTarget;
		ctx.m_pDevice = m_pDevice;
		ctx.m_pDeviceContext = m_pDeviceContext;
		ctx.m_WindowHandle = m_WindowHandle;

		return ctx;
	}


#pragma region Initialization

	void GraphicsMaster::InitRenderTargets()
	{
		// Game RT:
		m_pGameRenderTarget = new RenderTarget(m_pDevice);
		RT_Desc d{};
		d.m_bColorBuffer = true;
		d.m_bColorBufferSupplied = false;
		d.m_bColorSRV = true;
		d.m_bMipMaps_Color = true;
		d.m_ColorFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
		d.m_W = Settings::Window.Dimensions.x;
		d.m_H = Settings::Window.Dimensions.y;
		d.m_bDepthBuffer = true;
		d.m_bDepthBufferSupplied = false;
		d.m_bDepthSRV = true;
		m_pGameRenderTarget->Create(d);

		// Create final Window render target:
		m_pMainWindowRenderTarget = new RenderTarget(m_pDevice);
		RT_Desc desc2{};
		// Set colorbuffer as the backbuffer of the swapchain:
		ID3D11Texture2D* pBackBuffer = nullptr;
		m_pSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
		RT_Desc rtDesc;
		rtDesc.m_pColorBuffer = pBackBuffer;
		rtDesc.m_W = Settings::Window.Dimensions.x;
		rtDesc.m_H = Settings::Window.Dimensions.y;
		m_pMainWindowRenderTarget->Create(rtDesc);
	}

	void GraphicsMaster::InitWindow()
	{
		// Windowclass:
		WNDCLASS wc;
		ZeroMemory(&wc, sizeof(WNDCLASS));

		// Fill in windowclass:
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = Engine::WindowsProcedureStatic;
		wc.hInstance = m_WinInstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszClassName = L"LiberoWindowClass";

		// Register windowclass:
		RegisterClass(&wc);

		// Create window & store handle:
		m_WindowHandle = CreateWindow(
			L"LiberoWindowClass",
			L"Libero Engine", 
			WS_OVERLAPPEDWINDOW,
			0,
			0,
			(int)Settings::Window.Dimensions.x,
			(int)Settings::Window.Dimensions.y,
			NULL,
			NULL,
			m_WinInstance,
			NULL);

		ShowWindow(m_WindowHandle, SW_SHOWMAXIMIZED);
	}

	void GraphicsMaster::InitDX()
	{
		auto hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&m_pDXGIFactory));
		if (FAILED(hr)) return;

		// Setup Adapter
		if (!Settings::DX.pAdapter)
		{
			hr = m_pDXGIFactory->EnumAdapters(0, &Settings::DX.pAdapter);
			if (FAILED(hr)) return;
		}

		// Setup output
		if (!Settings::DX.pOutput)
		{
			IDXGIOutput* tempOutput;
			hr = Settings::DX.pAdapter->EnumOutputs(0, &tempOutput);
			if (FAILED(hr)) return;

			hr = tempOutput->QueryInterface(__uuidof(IDXGIOutput), reinterpret_cast<void**>(&Settings::DX.pOutput));
			if (FAILED(hr)) return;
			SafeRelease(tempOutput);
		}

		// Creating Dx11 Device & context:
		UINT flags = 0;

#if defined (DEBUG) ||defined (_DEBUG)
		flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL featureLvl = D3D_FEATURE_LEVEL_11_0;
		auto res = D3D11CreateDevice(Settings::DX.pAdapter,
			D3D_DRIVER_TYPE_UNKNOWN,
			nullptr,
			flags,
			nullptr, 0,
			D3D11_SDK_VERSION,
			&m_pDevice,
			&featureLvl,
			&m_pDeviceContext);
		res;

		// Create swapchain
		DXGI_SWAP_CHAIN_DESC swapDesc;
		ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		swapDesc.BufferDesc.Width = (UINT)Settings::Window.Dimensions.x;
		swapDesc.BufferDesc.Height = (UINT)Settings::Window.Dimensions.y;
		swapDesc.BufferDesc.RefreshRate.Numerator = 1;
		swapDesc.BufferDesc.RefreshRate.Denominator = 60;
		swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapDesc.SampleDesc.Count = 1;
		swapDesc.SampleDesc.Quality = 0;
		swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		swapDesc.BufferCount = 1;
		swapDesc.OutputWindow = m_WindowHandle;
		swapDesc.Windowed = true;
		swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapDesc.Flags = 0;

		m_pDXGIFactory->CreateSwapChain(m_pDevice, &swapDesc, &m_pSwapchain);

		m_Viewport.Width = static_cast<FLOAT>(Settings::Window.Dimensions.x);
		m_Viewport.Height = static_cast<FLOAT>(Settings::Window.Dimensions.y);
		m_Viewport.TopLeftX = 0;
		m_Viewport.TopLeftY = 0;
		m_Viewport.MinDepth = 0.0f;
		m_Viewport.MaxDepth = 1.0f;
		m_pDeviceContext->RSSetViewports(1, &m_Viewport);
	}
#pragma endregion
}