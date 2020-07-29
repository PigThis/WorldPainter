//*********************************************************
//refer to Microsoft project D3D12HelloTriangle
//code with Direct3D 12
//*********************************************************

#pragma once

#include <d3d12.h>
#include <dxgi1_2.h>
#include <dxgi1_3.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include <D3Dcompiler.h>

#include "GameDirector.h"
#include "d3dx12.h"
#include "winHelper.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr; //Œ¢»Ìµƒ÷«ƒ‹÷∏’Î

class D3DDirector : public Director
{
private:
	static const unsigned int FrameCount = 2;

	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};
	// Pipeline objects.
	CD3DX12_VIEWPORT _viewport;
	CD3DX12_RECT _scissorRect;
	ComPtr<IDXGISwapChain3> _swapChain;
	ComPtr<ID3D12Device> _device;
	ComPtr<ID3D12Resource> _renderTargets[FrameCount];
	ComPtr<ID3D12CommandAllocator> _commandAllocator;
	ComPtr<ID3D12CommandQueue> _commandQueue;
	ComPtr<ID3D12RootSignature> _rootSignature;
	ComPtr<ID3D12DescriptorHeap> _rtvHeap;
	ComPtr<ID3D12PipelineState> _pipelineState;
	ComPtr<ID3D12GraphicsCommandList> _commandList;

	ComPtr<ID3D12Resource> _vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW _vertexBufferView;

	UINT _rtvDescriptorSize;
	UINT _frameIndex;

	HANDLE _fenceEvent;
	ComPtr<ID3D12Fence> _fence;
	UINT64 _fenceValue;

	void loadPipeline();
	void loadAssets();
	void populateCommandList();
	void waitForPreviousFrame();

public:
	D3DDirector(unsigned int width, unsigned int height, std::wstring title);
	virtual void initGameProcedure() override;
	virtual void endGame() override;

	virtual void onUpdate() override;
	virtual void onRender() override;

protected:
	HWND _shareHwnd;
	void bindHwnd(HWND hwnd) override;
	void getHardwareAdapter(_In_ IDXGIFactory2* pFactory, _Outptr_result_maybenull_ IDXGIAdapter1** ppAdapter);
};