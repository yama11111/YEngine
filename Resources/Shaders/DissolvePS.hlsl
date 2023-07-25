#include "Dissolve.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
Texture2D<float4> mask : register(t1); // 1番スロットに設定されたマスクテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

PSOutput main(PSInput input)
{
	PSOutput output;

	// テクスチャマッピング
	float4 texColor = tex.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;
	float4 maskColor = mask.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;

	clip(maskColor.r - time_);
	
	// 計算した色で描画
	output.target_ = texColor * baseColor_;

	return output;
}