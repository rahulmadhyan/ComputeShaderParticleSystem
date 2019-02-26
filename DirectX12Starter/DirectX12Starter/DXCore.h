#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "d3dUtil.h"
#include "InputManager.h"
#include "Timer.h"

// link necessary d3d12 libraries
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

class DXCore
{
public:
	static DXCore* GetApplication();

	HINSTANCE ApplicationInstance() const;
	HWND MainWindow() const;
	float AspectRatio() const;

	bool Get4xMsaaState() const;
	void Set4xMsaaStata(bool value);

	int Run();

	virtual bool Initialize();
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	static DXCore* Instance;

	HINSTANCE applicationInstanceHandle = nullptr; // application instance handle
	HWND mainWindowHandle = nullptr;			   // main window handle
	bool applicationPaused = false;				   
	bool applicationMinimized = false;			   
	bool applicationMaximized = false;			   
	bool applicationResizing = false;			   
	bool applicationFullScreen = false;

	// Set true to use 4X MSAA (�4.1.8).  The default is false.
	bool      xMsaaState = false;    // 4X MSAA enabled
	UINT      xMsaaQuality = 0;      // quality level of 4X MSAA

	Timer timer;

	Microsoft::WRL::ComPtr<IDXGIFactory> DXGIFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain;
	Microsoft::WRL::ComPtr<ID3D12Device> Device;

	Microsoft::WRL::ComPtr<ID3D12Fence> Fence;
	UINT64 currentFence = 0;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> CommandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CommandListAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList;

	static const int SwapChainBufferCount = 2;
	int currentBackBuffer = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> SwapChainBuffer[SwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> DepthStencilBuffer;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> RTVHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> DSVHeap;

	D3D12_VIEWPORT ScreenViewPort;
	D3D12_RECT ScissorRect;

	UINT RTVDescriptorSize = 0;
	UINT DSVDescriptorSize = 0;
	UINT CBVSRVUAVDescriptorSize = 0;

	// derived 'Game' class will set to actual values in constructor
	std::wstring MainWindowCaption = L"Junkyard";
	D3D_DRIVER_TYPE D3DDriverType = D3D_DRIVER_TYPE_HARDWARE;
	DXGI_FORMAT BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	int screenWidth = 1280;
	int screenHeight = 720;

	DXCore(HINSTANCE hInstnace);
	DXCore(const DXCore& rhs) = delete;
	DXCore& operator=(const DXCore& rhs) = delete;
	virtual ~DXCore();

	virtual void CreateRTVAndDSVDescriptorHeaps();
	virtual void Resize();
	virtual void Update(const Timer& timer) = 0;
	virtual void Draw(const Timer& timer) = 0;

	bool InitMainWindow();
	bool InitDirect3D();
	void CreateCommandObjects();
	void CreateSwapChain();

	void FlushCommandQueue();

	ID3D12Resource* CurrentBackBuffer() const;
	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView() const;
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const;
};

