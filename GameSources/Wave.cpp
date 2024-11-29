#include "stdafx.h"
#include "Project.h"
#include <d3dcompiler.h>

Wave::Wave()
    : pVertexShader(nullptr), pPixelShader(nullptr), pVertexBuffer(nullptr), pRenderTargetView(nullptr),
    pd3dDevice(nullptr), pContext(nullptr) {}

Wave::~Wave() {
    Cleanup();
}

HRESULT Wave::InitializeResources(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext) {
    this->pd3dDevice = pd3dDevice;
    this->pContext = pContext;

    HRESULT hr;

    // シェーダーファイルのバイナリを読み込んでコンパイルする
    ID3DBlob* pVSBlob = nullptr;
    ID3DBlob* pPSBlob = nullptr;

    // 頂点シェーダーのコンパイルと作成
    hr = D3DCompileFromFile(L"Wave.hlsl", nullptr, nullptr, "VS_main", "vs_5_0", 0, 0, &pVSBlob, nullptr);
    if (FAILED(hr)) {
        std::cout << "頂点シェーダーのコンパイルに失敗しました。" << std::endl;
        return hr;
    }
    hr = pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &pVertexShader);
    if (FAILED(hr)) {
        std::cout << "頂点シェーダーの作成に失敗しました。" << std::endl;
        return hr;
    }

    // ピクセルシェーダーのコンパイルと作成
    hr = D3DCompileFromFile(L"Wave.hlsl", nullptr, nullptr, "PS_main", "ps_5_0", 0, 0, &pPSBlob, nullptr);
    if (FAILED(hr)) {
        std::cout << "ピクセルシェーダーのコンパイルに失敗しました。" << std::endl;
        return hr;
    }
    hr = pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &pPixelShader);
    if (FAILED(hr)) {
        std::cout << "ピクセルシェーダーの作成に失敗しました。" << std::endl;
        return hr;
    }

    // 頂点バッファの作成
    // ここで頂点データを作成し、頂点バッファを作成します
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(DirectX::XMFLOAT3) * 3; // 三角形の頂点3つ
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    DirectX::XMFLOAT3 vertices[] = {
        DirectX::XMFLOAT3(0.0f, 0.5f, 0.0f),  // 上の頂点
        DirectX::XMFLOAT3(0.5f, -0.5f, 0.0f), // 右下の頂点
        DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f) // 左下の頂点
    };

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices;

    hr = pd3dDevice->CreateBuffer(&bufferDesc, &initData, &pVertexBuffer);
    if (FAILED(hr)) {
        std::cout << "頂点バッファの作成に失敗しました。" << std::endl;
        return hr;
    }

    return S_OK;
}

void Wave::Render() {
    // シェーダーを設定
    //pContext->VSSetShader(pVertexShader, nullptr, 0);
    //pContext->PSSetShader(pPixelShader, nullptr, 0);

    // 頂点バッファをセットして描画
    UINT stride = sizeof(DirectX::XMFLOAT3);
    UINT offset = 0;
    //pContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
    //pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // 三角形リストとして描画

    // 描画コマンドを発行
    //pContext->Draw(3, 0); // 三角形を描画（3つの頂点）

    // 他の描画処理（例えば、レンダーターゲットのスワップなど）
}

void Wave::Cleanup() {
    if (pVertexShader) pVertexShader->Release();
    if (pPixelShader) pPixelShader->Release();
    if (pVertexBuffer) pVertexBuffer->Release();
    if (pRenderTargetView) pRenderTargetView->Release();
}
