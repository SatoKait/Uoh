#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

// シェーダークラス
class Shader
{
public:
    Shader();
    ~Shader();

    bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const wchar_t* vsFilename, const wchar_t* psFilename);
    void Shutdown();
    void SetShaderParameters(ID3D11DeviceContext* deviceContext, DirectX::XMFLOAT2 texOffset, float springPower, DirectX::XMFLOAT2 addWavePos, float addWaveHeight);
    void Render(ID3D11DeviceContext* deviceContext);

private:
    bool CompileShader(const wchar_t* filename, const char* entryPoint, const char* shaderModel, ID3DBlob** blob);

    ID3D11VertexShader* m_vertexShader;
    ID3D11PixelShader* m_pixelShader;
    ID3D11InputLayout* m_layout;
    ID3D11Buffer* m_constantBuffer;
};
