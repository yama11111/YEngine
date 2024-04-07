#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0); // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1); // 1番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

// 軸数
static const float ArrayNum = 3;

// 1ピクセル
static const float2 Pixel = float2(1.0f, 1.0f) / float2(1280.0f, 720.0f);

// 閾値
static const float Threshold = 0.4f;

float4 main(PSInput input) : SV_TARGET
{
	// 判定用
	float4 decisionColor = tex0.Sample(smp, input.uv_ * texTiling_ + texOffset_);

	// ピクセルの明るさ
	float bright = (decisionColor.r + decisionColor.g + decisionColor.b) / 3.0f;

	// 閾値以下は黒
	float colorRate = 1.0f - step(Threshold, bright);


	// 計算用
	float4 resultColor = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// 左上のUV値
	float2 leftTopUV = input.uv_ * texTiling_ + texOffset_ - float2((ArrayNum - 1), (ArrayNum - 1)) / 2.0f;

	// y軸
	for (float y = 0; y < ArrayNum; y++)
	{
		// x軸
		for (float x = 0; x < ArrayNum; x++)
		{
			// ずれる分
			float2 offsetUV = Pixel * float2(x, y);

			// テクスチャマッピング
			float4 texColor = tex0.Sample(smp, leftTopUV + offsetUV) * texColorRate_ * float4(colorRate, colorRate, colorRate, colorRate);

			// 足していく
			resultColor += texColor;
		}
	}

	// 平均化
	resultColor /= float(ArrayNum * ArrayNum);

	// 計算した色で描画
	return float4(resultColor.xyz * baseColor_.xyz, 1.0f);
}