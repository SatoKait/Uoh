// 定数バッファ
cbuffer ConstantBuffer : register(b0)
{
    float2 TexOffset;
    float SpringPower;
    float2 AddWavePos;
    float AddWaveHeight;
}

// テクスチャ & サンプラー
Texture2D tex0 : register(t0);
SamplerState Sampler : register(s0);

// 頂点シェーダーからの入力
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

// 波の計算を行うピクセルシェーダー
float4 PS_WaveMap(VS_OUTPUT In) : SV_Target
{
    float4 Wave = tex0.Sample(Sampler, In.Tex);
    
    float H1 = tex0.Sample(Sampler, In.Tex + float2(TexOffset.x, 0.0f)).r;
    float H2 = tex0.Sample(Sampler, In.Tex + float2(0.0f, TexOffset.y)).r;
    float H3 = tex0.Sample(Sampler, In.Tex + float2(-TexOffset.x, 0.0f)).r;
    float H4 = tex0.Sample(Sampler, In.Tex + float2(0.0f, -TexOffset.y)).r;

    float V = ((H1 + H2 + H3 + H4) * 0.25f - Wave.r) * SpringPower + Wave.g;
    float H = Wave.r + V;

    if (distance(In.Tex, AddWavePos) < 0.005f)
    {
        V += AddWaveHeight;
    }

    return float4(H, V, 1.0f, 1.0f);
}

// 頂点シェーダーエントリーポイント
VS_OUTPUT main(float4 Pos : POSITION, float2 Tex : TEXCOORD0)
{
    VS_OUTPUT Out;
    Out.Pos = Pos;
    Out.Tex = Tex;
    return Out;
}

// 法線マップを作るピクセルシェーダー
float4 PS_BumpMap(VS_OUTPUT In) : SV_Target
{
    float H1 = tex0.Sample(Sampler, In.Tex + float2(TexOffset.x, 0.0f)).r;
    float H2 = tex0.Sample(Sampler, In.Tex + float2(0.0f, TexOffset.y)).r;
    float H3 = tex0.Sample(Sampler, In.Tex + float2(-TexOffset.x, 0.0f)).r;
    float H4 = tex0.Sample(Sampler, In.Tex + float2(0.0f, -TexOffset.y)).r;

    float3 normal = normalize(float3(H1 - H3, H2 - H4, 1.0f));
    return float4(normal * 0.5f + 0.5f, 1.0f);
}

// テクニックでシェーダーを指定
technique10 Render
{
    pass P0
    {
        VertexShader = compile vs_5_0 main();
        PixelShader = compile ps_5_0 PS_WaveMap();
    }
}
