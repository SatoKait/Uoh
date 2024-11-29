#pragma once
#include "stdafx.h"
#include <d3d11.h>
#include <DirectXMath.h>

class Wave {
public:
    // コンストラクタとデストラクタ
    Wave();
    ~Wave();

    // リソースの初期化
    HRESULT InitializeResources(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);

    // 描画処理
    void Render();

    // クリーンアップ
    void Cleanup();

private:
    // シェーダー
    ID3D11VertexShader* pVertexShader;
    ID3D11PixelShader* pPixelShader;

    // バッファ
    ID3D11Buffer* pVertexBuffer;

    // レンダーターゲットビュー
    ID3D11RenderTargetView* pRenderTargetView;

    // Direct3D リソース
    ID3D11Device* pd3dDevice;
    ID3D11DeviceContext* pContext;
};
