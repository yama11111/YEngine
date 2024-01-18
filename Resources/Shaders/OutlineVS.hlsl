#include "Outline.hlsli"

PSInput main(VSInput input)
{
	// range分拡大
	matrix matW = mul(matWorld_, matrix(
		1.0f + range_, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f + range_, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f + range_, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f));

	// 法線にワールド行列によるスケーリング、回転を適用
	float4 wNormal = normalize(mul(matW, float4(input.normal, 0)));
	float4 wPos = mul(matW, input.pos);


	// ピクセルシェーダーに渡す値
	PSInput output;


	// システム頂点
	output.svPos = mul(mul(matViewProj_, matW), input.pos);

	// ワールド座標
	output.worldPos = wPos;

	// 法線ベクトル
	output.normal = wNormal.xyz;

	// UV座標
	output.uv = input.uv;

	// 頂点から視点への方向ベクトル
	output.eyeDir = normalize(cameraPos_ - wPos.xyz);


	return output;
}