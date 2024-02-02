#include "Model.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

PSOutput main(PSInput input)
{
	PSOutput output;

	// テクスチャマッピング
	float4 texColor = tex.Sample(smp, input.uv * texTiling_ + texOffset_) * texColorRate_;

	// 色
	float4 color = texColor * baseColor_;

	output.target = color;

	return output;


	// 光沢度
	const float shininess = 4.0f;


	// 環境反射光
	float3 ambient = color.rgb * ambient_ * ambientColor_;

	// シェーディング色
	float3 shaderColor = ambient;


	// ライト毎の計算
	for (float i = 0; i < DireLightNum; i++)
	{
		// 平行光源
		if (direLights_[i].active)
		{
			// ライトに向かうベクトルと法線の計算
			float3 dotLightNormal = dot(direLights_[i].lightVec, input.normal);


			// ライトに向かうベクトルと法線の内積をクランプ
			float3 intensity = saturate(dotLightNormal);

			// 拡散反射光
			float3 diffuse = intensity * color.rgb * diffuse_;


			// 反射光ベクトル
			float3 reflectDir = normalize(-direLights_[i].lightVec + (2.0f * dotLightNormal * input.normal));
			
			// 鏡面反射光
			float3 specular = pow(saturate(dot(reflectDir, input.eyeDir)), shininess) * specular_;


			// 全て加算
			shaderColor += (diffuse + specular) * direLights_[i].lightColor;
		}
	}
	for (int j = 0; j < PointLightNum; j++)
	{
		// 点光源
		if (pointLights_[j].active)
		{
			// ライトのベクトル
			float3 lightVec = normalize(pointLights_[j].lightPos - input.worldPos.xyz);
			
			// ライトに向かうベクトルと法線の内積
			float3 dotLightNormal = dot(lightVec, input.normal);
			

			// ライトに向かうベクトルと法線の内積をクランプ
			float3 intensity = saturate(dotLightNormal);

			// 拡散反射光
			float3 diffuse = intensity * color.rgb * diffuse_;
			

			// 反射光ベクトル
			float3 reflectDir = normalize(-lightVec + (2.0f * dotLightNormal * input.normal));
			
			// 鏡面反射光
			float3 specular = pow(saturate(dot(reflectDir, input.eyeDir)), shininess) * specular_;
			

			// ベクトルの長さ
			float d = length(lightVec);

			// 距離減衰係数
			float atten = 1.0f /
				((pointLights_[j].lightAtten.x) +
					(pointLights_[j].lightAtten.y * d) +
					(pointLights_[j].lightAtten.z * d * d));

			// 全て加算
			shaderColor += atten * (diffuse + specular) * pointLights_[j].lightColor;
		}
	}
	for (int k = 0; k < SpotLightNum; k++)
	{
		// スポットライト光源
        if (spotLights_[k].active)
        {
			// ライトのベクトル
            float3 lightVec = spotLights_[k].lightPos - input.worldPos.xyz;
			// ベクトルの長さ
            float d = length(lightVec);
			// 正規化
            lightVec = normalize(lightVec);
			// 距離減衰係数
            float atten = 1.0f / 
				(spotLights_[k].lightAtten.x + 
				(spotLights_[k].lightAtten.y * d) + 
				(spotLights_[k].lightAtten.z * d * d));
			// 角度減衰
            float cos = dot(lightVec, spotLights_[k].lightVec);
			// 開始角度→終了角度に減衰 (開始内側 : 1倍, 終了外側 : 0倍 の輝度)
            float angleAtten = smoothstep(spotLights_[k].lightEndFactorAngleCos, spotLights_[k].lightStartFactorAngleCos, cos);
			// 角度減衰を乗算
            atten *= angleAtten;
			// ライトに向かうベクトルと法線の内積
            float3 dotLightNormal = dot(lightVec, input.normal);
			// 反射光ベクトル
            float3 reflect = normalize(-lightVec + (2.0f * dotLightNormal * input.normal));
			// 拡散反射光
            float3 diffuse = dotLightNormal * diffuse_;
			// 鏡面反射光
            float3 specular = pow(saturate(dot(reflect, input.eyeDir)), shininess) * specular_;

			// 全て加算
            shaderColor += atten * (diffuse + specular) * pointLights_[k].lightColor;
        }
    }

	// 計算した色で描画
	output.target = float4(shaderColor, color.a * alpha_);

	return output;
}