#include "Outline.hlsli"

PSInput main(VSInput input)
{
	// 法線にワールド行列によるスケーリング、回転を適用
    float4 wNormal = normalize(mul(matWorld_, float4(input.normal, 0)));	
    float4 wPos = mul(matWorld_, input.pos);

	// ピクセルシェーダーに渡す値
	PSInput output;

	// 法線方向に拡張した座標を計算
    float4 extendPos = input.pos;
    extendPos += float4(input.normal * range_, 0.0f);

	// システム頂点
    output.svPos = mul(mul(matViewProj_, matWorld_), extendPos);

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