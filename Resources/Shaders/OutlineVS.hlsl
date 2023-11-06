#include "Outline.hlsli"

PSInput main(VSInput input)
{
	matrix matW = mul(matWorld_, matrix(
		1.0f + range_, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f + range_, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f + range_, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f));

	// 法線にワールド行列によるスケーリング、回転を適用
	float4 wNormal = normalize(mul(matW, float4(input.normal_, 0)));
	float4 wPos = mul(matW, input.pos_);


	// ピクセルシェーダーに渡す値
	PSInput output;


	// システム頂点
	output.svPos_ = mul(mul(matViewProj_, matW), input.pos_);

	// ワールド座標
	output.worldPos_ = wPos;

	// 法線ベクトル
	output.normal_ = wNormal.xyz;

	// UV座標
	output.uv_ = input.uv_;

	// 頂点から視点への方向ベクトル
	output.eyeDir_ = normalize(cameraPos_ - wPos.xyz);


	return output;
}