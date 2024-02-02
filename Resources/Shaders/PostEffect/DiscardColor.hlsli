// トランスフォーム
cbuffer cbTransform : register(b0)
{
    matrix matWorld_; // ワールド行列
}

// 色
cbuffer cbColor : register(b1)
{
    float4 baseColor_; // 色(RGBA)
    float4 texColorRate_; // 元の色の割合
}

// テクスチャ設定
cbuffer cbTexConfig : register(b2)
{
    float2 texTiling_; // タイリング
    float2 texOffset_; // オフセット
}

// 消去色設定
cbuffer cbDiscardColor : register(b3)
{
    float3 discardColor_; // 色(RGB)
    float threshold_; // 閾値
}

// 頂点シェーダーの入力構造体
struct VSInput
{
	// 頂点座標
    float4 pos_ : POSITION;
	// uv値
    float2 uv_ : TEXCOORD;
};

// ピクセルシェーダーの入力構造体
struct PSInput
{
	// システム用頂点座標
    float4 svpos_ : SV_POSITION;
	// uv値
    float2 uv_ : TEXCOORD;
};

// ピクセルシェーダーの出力構造体
struct PSOutput
{
	// 描画
    float4 target_ : SV_TARGET0;
};
