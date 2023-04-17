#include "Light.hlsli"

// 3D変換行列
cbuffer cbuff0 : register(b0)
{
	matrix matWorld;	 // ワールド行列
	matrix matViewProj;	 // ビュープロジェクション行列
	float3 cameraPos;	 // カメラ座標
}
// 色
cbuffer cbuff1 : register(b1)
{
	float4 color; // 色(RGBA)
	float4 originalColorRate; // 元の色の割合
}
// 光
cbuffer cbuff2 : register(b2)
{
	float3 ambientColor;		 // 環境光色
	DireLight direLights[DireLightNum];	 // 平行光源
	PointLight pointLights[PointLightNum];	 // 点光源
	//SpotLight spotLights[SpotLightNum];	 // スポットライト光源
}
// マテリアル2
cbuffer cbuff3 : register(b3)
{
	float3 mAmbient  : packoffset(c0);	 // アンビエント係数
	float3 mDiffuse  : packoffset(c1);	 // ディフューズ係数
	float3 mSpecular : packoffset(c2);	 // スペキュラー係数
	float  mAlpha    : packoffset(c2.w); // アルファ
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
	// 接空間
	float3 tangent : TANGENT;
	// 頂点色
	float4 color : COLOR;
};
// ピクセルシェーダーの入力構造体 
struct PSInput
{
	// システム様頂点座標
	float4 svPos : SV_POSITION;
	// ワールド座標
	float4 worldPos : POSITION;
	// 法線ベクトル
	float3 normal : NORMAL;
	// uv値
	float2 uv : TEXCOORD;
};
