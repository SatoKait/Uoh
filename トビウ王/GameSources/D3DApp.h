#pragma once
#include <wrl.h>
#include <d3d11.h>

class D3DApp {
public:
    D3DApp();
    ~D3DApp();

    bool Initialize(HWND hwnd, UINT width, UINT height);

    Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() const { return m_device; }
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetContext() const { return m_context; }

private:
    Microsoft::WRL::ComPtr<ID3D11Device> m_device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context;
    Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
};