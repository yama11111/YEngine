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

// 頂点シェーダーの出力構造体
// (頂点シェーダーからピクセルシェーダーへのやり取りに使用する)
struct VSOutput
{
	// システム様頂点座標
	float4 svpos : SV_POSITION;
	// uv値
	float2 uv : TEXCOORD;
};
