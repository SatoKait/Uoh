// WaveShader.hlsl

// 入力構造体 (アプリケーションから頂点データを受け取る)
struct VS_INPUT
{
    float3 position : POSITION; // 頂点の位置 (必須)
    float2 texcoord : TEXCOORD; // UV座標 (オプション)
};

// 出力構造体 (頂点シェーダーからピクセルシェーダーへ渡す)
struct VS_OUTPUT
{
    float4 position : SV_POSITION; // 変換されたクリップ空間座標
    float2 texcoord : TEXCOORD; // UV座標
};

// 頂点シェーダー (エントリポイント: VS_Main)
VS_OUTPUT VS_Main(VS_INPUT input)
{
    VS_OUTPUT output;
    
    // 頂点位置をそのまま出力 (ここで変換行列を掛ける場合が多い)
    output.position = float4(input.position, 1.0f);
    output.texcoord = input.texcoord; // UV座標もそのまま渡す
    
    return output;
}

// ピクセルシェーダー (エントリポイント: PS_Main)
float4 PS_Main(VS_OUTPUT input) : SV_TARGET
{
    // UV座標に基づいて波っぽいグラデーションを生成 (例)
    float waveEffect = sin(input.texcoord.x * 20.0f) * 0.5f + 0.5f;
    return float4(waveEffect, waveEffect, 1.0f, 1.0f); // 波エフェクトの色
}
