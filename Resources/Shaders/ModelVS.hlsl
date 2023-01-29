#include "Model.hlsli"

//PSInput main(VSInput input)
//{
//	PSInput output; // ピクセルシェーダーに渡す値
//	output.svpos = mul(matWorld, input.pos); // 座標に行列を乗算
//	output.normal = input.normal;
//	output.uv = input.uv;
//	return output;
//}

PSInput main(VSInput input)
{
	// 法線にワールド行列によるスケーリング、回転を適用
	float4 wNormal = normalize(mul(matWorld, float4(input.normal, 0)));
	float4 wPos = mul(matWorld, input.pos);

	// ピクセルシェーダーに渡す値
	PSInput output;
	output.svPos = mul(mul(matViewProj, matWorld), input.pos);
	output.worldPos = wPos;
	output.normal = wNormal.xyz;
	output.uv = input.uv;

	return output;
}