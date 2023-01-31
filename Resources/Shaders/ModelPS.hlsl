#include "Model.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

//float4 main(PSInput input) : SV_TARGET
//{
//	float3 light = normalize(float3(1, -1, 1)); // 右下奥 向きのライト
//	float diffuse = saturate(dot(-light, input.normal)); // diffuseを[0,1]の範囲にclampする
//	float3 shaderColor = mAmbient; // アンビエント項
//	shaderColor += mDiffuse * diffuse; // ディフューズ項
//	float4 texcolor = float4(tex.Sample(smp, input.uv));
//	//return float4(texcolor.rgb * shaderColor, texcolor.a * mAlpha) * color; // 輝度をRGBに代入して出力
//	return float4(texcolor.rgb * shaderColor, texcolor.a * mAlpha) * color; // 輝度をRGBに代入して出力
//}

float4 main(PSInput input) : SV_TARGET
{
	// テクスチャマッピング
	float4 texColor = tex.Sample(smp, input.uv);
	// 光沢度
	const float shininess = 4.0f;
	// 頂点から視点への方向ベクトル
	float3 eyeDir = normalize(cameraPos - input.worldPos.xyz);

	// 環境反射光
	float3 ambient = mAmbient;

	// シェーディング色
	float4 shaderColor = float4(ambientColor * ambient, mAlpha);

	// ライト毎の計算
	for (int i = 0; i < 3; i++)
	{
		if (direLights[i].active)
		{
			// ライトに向かうベクトルと法線の計算
			float3 dotLightNormal = dot(direLights[i].lightVec, input.normal);
			// 反射光ベクトル
			float3 reflect = normalize(-direLights[i].lightVec + 2 * dotLightNormal * input.normal);
			// 拡散反射光
			float3 diffuse = dotLightNormal * mDiffuse;
			// 鏡面反射光
			float3 specular = pow(saturate(dot(reflect, eyeDir)), shininess) * mSpecular;

			// 全て加算
			shaderColor.rgb += (ambient + diffuse + specular) * direLights[i].lightColor;
		}
	}

	// シェーディング色で描画
	return (shaderColor * texColor) * color;
}