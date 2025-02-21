//#include "Shader.h"
//#include <fstream>
#include "stdafx.h"
#include "Project.h"

using namespace DirectX;

struct ConstantBufferType
{
    XMFLOAT2 TexOffset;
    float SpringPower;
    XMFLOAT2 AddWavePos;
    float AddWaveHeight;
};

Shader::Shader() :
    m_vertexShader(nullptr),
    m_pixelShader(nullptr),
    m_layout(nullptr),
    m_constantBuffer(nullptr)
{
}

Shader::~Shader()
{
    Shutdown();
}

bool Shader::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const wchar_t* vsFilename, const wchar_t* psFilename)
{
    HRESULT hr;
    ID3DBlob* vertexShaderBuffer = nullptr;
    ID3DBlob* pixelShaderBuffer = nullptr;

    // 頂点シェーダーのコンパイル
    if (!CompileShader(vsFilename, "VS_Wave", "vs_5_0", &vertexShaderBuffer))
    {
        return false;
    }

    // ピクセルシェーダーのコンパイル
    if (!CompileShader(psFilename, "PS_WaveMap", "ps_5_0", &pixelShaderBuffer))
    {
        return false;
    }

    // シェーダーの作成
    hr = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &m_vertexShader);
    if (FAILED(hr))
    {
        return false;
    }

    hr = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &m_pixelShader);
    if (FAILED(hr))
    {
        return false;
    }

    // 頂点レイアウト
    D3D11_INPUT_ELEMENT_DESC polygonLayout[2] = {};
    polygonLayout[0].SemanticName = "POSITION";
    polygonLayout[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    polygonLayout[0].AlignedByteOffset = 0;

    polygonLayout[1].SemanticName = "TEXCOORD";
    polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
    polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

    hr = device->CreateInputLayout(polygonLayout, 2, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);
    if (FAILED(hr))
    {
        return false;
    }

    // 解放
    vertexShaderBuffer->Release();
    pixelShaderBuffer->Release();

    // 定数バッファ
    D3D11_BUFFER_DESC constantBufferDesc = {};
    constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    constantBufferDesc.ByteWidth = sizeof(ConstantBufferType);
    constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    hr = device->CreateBuffer(&constantBufferDesc, nullptr, &m_constantBuffer);
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

void Shader::Shutdown()
{
    if (m_constantBuffer) { m_constantBuffer->Release(); m_constantBuffer = nullptr; }
    if (m_layout) { m_layout->Release(); m_layout = nullptr; }
    if (m_pixelShader) { m_pixelShader->Release(); m_pixelShader = nullptr; }
    if (m_vertexShader) { m_vertexShader->Release(); m_vertexShader = nullptr; }
}

void Shader::SetShaderParameters(ID3D11DeviceContext* deviceContext, XMFLOAT2 texOffset, float springPower, XMFLOAT2 addWavePos, float addWaveHeight)
{
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    HRESULT hr = deviceContext->Map(m_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (FAILED(hr))
    {
        return;
    }

    ConstantBufferType* dataPtr = (ConstantBufferType*)mappedResource.pData;
    dataPtr->TexOffset = texOffset;
    dataPtr->SpringPower = springPower;
    dataPtr->AddWavePos = addWavePos;
    dataPtr->AddWaveHeight = addWaveHeight;

    deviceContext->Unmap(m_constantBuffer, 0);
    deviceContext->VSSetConstantBuffers(0, 1, &m_constantBuffer);
    deviceContext->PSSetConstantBuffers(0, 1, &m_constantBuffer);
}

void Shader::Render(ID3D11DeviceContext* deviceContext)
{
    // シェーダーをセット
    deviceContext->IASetInputLayout(m_layout);
    deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
    deviceContext->PSSetShader(m_pixelShader, nullptr, 0);
}

bool Shader::CompileShader(const wchar_t* filename, const char* entryPoint, const char* shaderModel, ID3DBlob** blob)
{
    HRESULT hr;
    ID3DBlob* errorMessage = nullptr;

    hr = D3DCompileFromFile(filename, nullptr, nullptr, entryPoint, shaderModel, D3DCOMPILE_ENABLE_STRICTNESS, 0, blob, &errorMessage);
    if (FAILED(hr))
    {
        if (errorMessage)
        {
            OutputDebugStringA((char*)errorMessage->GetBufferPointer());
            errorMessage->Release();
        }
        return false;
    }
    return true;
}
