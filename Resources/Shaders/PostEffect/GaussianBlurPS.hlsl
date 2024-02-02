#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0); // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1); // 1番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

// 
static const float _Sigma = 0.005f;

// 幅
static const float _StepWidth = 0.001f;


float Gaussian(float2 drawUV, float2 pickUV, float sigma)
{
	float d = distance(drawUV, pickUV);
	return exp(-(d * d) / (2.0f * sigma * sigma));
}

float4 main(PSInput input) : SV_TARGET
{
	// 合計ウェイト
	float totalWeight = 0.0f;

	// 計算用
	float4 resultColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

	// y軸
	for (float py = -_Sigma * 2.0f; py <= _Sigma * 2.0f; py += _StepWidth)
	{
		// x軸
		for (float px = -_Sigma * 2.0f; px <= _Sigma * 2.0f; px += _StepWidth)
		{
			float2 pickUV = input.uv_ + float2(px, py);
			float weight = Gaussian(input.uv_, pickUV, _Sigma);
			resultColor += tex0.Sample(smp, pickUV) * weight;
			totalWeight += weight;
		}
	}

	// 平均化
	resultColor = float4(resultColor.rgb / totalWeight, 1.0f);
	
	// 計算した色で描画
	return resultColor;
}