// マテリアル
cbuffer ConstBufferDataMaterial : register(b0)
{
	float4 color; // 色(RGBA)
}

float4 main() : SV_TARGET
{
	return color;
}