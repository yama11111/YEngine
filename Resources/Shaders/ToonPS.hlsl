#include "Toon.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

PSOutput main(PSInput input)
{
	PSOutput output;

	// テクスチャマッピング
	float4 texColor = tex.Sample(smp, input.uv * texTiling_ + texOffset_) * texColorRate_;

	// 色
	float4 color = texColor * baseColor_;


	// 光沢度
	const float shininess = 4.0f;

	// 閾値 (限界) 初期値
	const float thresholdStart = 0.4f;

	// 閾値 (限界) 最終値
	const float thresholdEnd = thresholdStart + 0.05f;


	// 平行光源の向き
	float3 direLightVec = normalize(float3(-1.0f, +1.0f, -1.0f));

	// 平行光源の色
	float3 direLightColor = float3(1.0f, 1.0f, 1.0f);


	// ライトに向かうベクトルと法線の計算
	float3 dotLightNormal = dot(direLightVec, input.normal);


	// 環境反射光
	float3 ambient = color.rgb * ambient_;


	// ライトに向かうベクトルと法線の内積をクランプ
	float3 intensity = saturate(dotLightNormal);

	// 内積にスムースステップを適応
	intensity = smoothstep(thresholdStart, thresholdEnd, intensity);

	// 拡散反射光
	float3 diffuse = intensity * color.rgb * diffuse_;


	// 反射光ベクトル
	float3 reflectDir = normalize(-direLightVec + (2.0f * dotLightNormal * input.normal));

	// 鏡面反射光
	float3 specular = pow(saturate(dot(reflectDir, input.eyeDir)), shininess) * specular_;

	// 鏡面反射光にスムースステップを適応
	specular = smoothstep(thresholdStart, thresholdEnd, specular);


	// 全て加算
	float3 shaderColor = (ambient + diffuse + specular) * direLightColor;

	// 計算した色で描画
	output.target = float4(shaderColor, color.a * alpha_);

	return output;
}