// 3D変換行列
cbuffer cbuff0 : register(b0)
{
	matrix mat; // 3D変換行列
}

// マテリアル
cbuffer cbuff1 : register(b1)
{
	float3 mAmbient  : packoffset(c0);	 // アンビエント係数
	float3 mDiffuse  : packoffset(c1);	 // ディフューズ係数
	float3 mSpecular : packoffset(c2);	 // スペキュラー係数
	float  mAlpha    : packoffset(c2.w); // アルファ
}

// 頂点シェーダーの出力構造体
// (頂点シェーダーからピクセルシェーダーへのやり取りに使用する)
struct VSOutput
{
	// システム様頂点座標
	float4 svpos : SV_POSITION;
	// 法線ベクトル
	float3 normal : NORMAL;
	// uv値
	float2 uv : TEXCOORD;
};
