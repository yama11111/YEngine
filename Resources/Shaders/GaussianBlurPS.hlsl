#include "PostEffect.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

// 
static const float _Sigma = 0.5f;

// 幅
static const float _StepWidth = 0.5f;


float Gaussian(float2 drawUV, float2 pickUV, float sigma)
{
	float d = distance(drawUV, pickUV);
	return exp(-(d * d) / (2 * sigma * sigma));
}

float4 main(PSInput input) : SV_TARGET
{
	// 合計ウェイト
	float totalWeight = 0;

	// 計算用
	float4 resultColor = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// y軸
	for (float py = -_Sigma * 2.0f; py <= _Sigma * 2; py += _StepWidth)
	{
		// x軸
		for (float px = -_Sigma * 2.0f; px <= _Sigma * 2; px += _StepWidth)
		{
			float2 pickUV = input.uv_ + float2(px, py);
			float weight = Gaussian(input.uv_, pickUV, _Sigma);
			resultColor += tex.Sample(smp, pickUV) * weight;
			totalWeight += weight;
		}
	}

	// 平均化
	resultColor = float4(resultColor.rgb / totalWeight, 1.0f);
	
	// 計算した色で描画
	return resultColor;
}