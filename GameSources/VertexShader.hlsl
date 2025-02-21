// 定数バッファ
cbuffer ConstantBuffer : register(b0)
{
    float2 TexOffset;
    float SpringPower;
    float2 AddWavePos;
    float AddWaveHeight;
}

// 頂点シェーダーの入力
struct VS_INPUT
{
    float4 Pos : POSITION;
    float2 Tex : TEXCOORD0;
};

// 頂点シェーダーの出力
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

// 頂点シェーダー
VS_OUTPUT main(VS_INPUT In)
{
    VS_OUTPUT Out;
    Out.Pos = In.Pos;
    Out.Tex = In.Tex;
    return Out;
}
