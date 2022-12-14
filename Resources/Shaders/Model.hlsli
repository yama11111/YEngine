// 3D変換行列
cbuffer cbuff0 : register(b0)
{
	matrix mat; // 3D変換行列
}

// マテリアル
cbuffer cbuff1 : register(b1)
{
	float4 color; // 色(RGBA)
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

// 頂点シェーダーの出力構造体 (頂点シェーダー ⇒ ピクセルシェーダー)
struct VSOutput
{
	// システム用頂点座標
	float4 svpos : SV_POSITION;
	// 法線ベクトル
	float3 normal : NORMAL;
	// uv値
	float2 uv : TEXCOORD;
};
