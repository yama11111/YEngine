// 3D変換行列
cbuffer cbuff0 : register(b0)
{
	matrix mat; // 3D変換行列
	matrix matBillboard; // ビルボード行列
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
};
// ジオメトリシェーダーの入力構造体 
struct GSInput 
{
	// 頂点座標
	float4 pos : POSITION;
};
// ピクセルシェーダーの入力構造体 
struct PSInput
{
	// システム用頂点座標
	float4 svpos : SV_POSITION;
	// uv値
	float2 uv : TEXCOORD;
};
