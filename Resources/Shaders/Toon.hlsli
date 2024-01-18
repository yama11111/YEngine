#include "Light.hlsli"

// トランスフォーム
cbuffer cbuff0 : register(b0)
{
    matrix matWorld_; // ワールド行列
    matrix matViewProj_; // ビュープロジェクション行列
    float3 cameraPos_; // カメラ座標
}

// 色
cbuffer cbuff1 : register(b1)
{
    float4 baseColor_; // 色(RGBA)
    float4 texColorRate_; // 元の色の割合
}

// マテリアル
cbuffer cbuff2 : register(b2)
{
    float3 ambient_ : packoffset(c0); // アンビエント係数
    float3 diffuse_ : packoffset(c1); // ディフューズ係数
    float3 specular_ : packoffset(c2); // スペキュラー係数
    float alpha_ : packoffset(c2.w); // アルファ
}

// テクスチャ設定
cbuffer cbuff4 : register(b3)
{
    float2 texTiling_; // タイリング
    float2 texOffset_; // オフセット
}


// 頂点シェーダーの入力構造体 
struct VSInput
{
	// 頂点座標
    float4 pos : POSITION;
	// 法線ベクトル
    float3 normal : NORMAL;
	// uv値
    float2 uv : TEXCOORD;
};

// ピクセルシェーダーの入力構造体 
struct PSInput
{
	// システム用頂点座標
    float4 svPos : SV_POSITION;
	// ワールド座標
    float4 worldPos : POSITION;
	// 法線ベクトル
    float3 normal : NORMAL;
	// uv値
    float2 uv : TEXCOORD;
	// 視線ベクトル
    float3 eyeDir : EYE_DIRECTION;
};

// ピクセルシェーダーの出力構造体
struct PSOutput
{
	// 描画
    float4 target : SV_TARGET;
};
