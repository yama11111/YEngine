#include "Sprite2D.hlsli"

Texture2D<float4> tex0 : register(t0); // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1); // 1番スロットに設定されたテクスチャ
Texture2D<float4> mask : register(t2); // 2番スロットに設定されたマスクテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

PSOutput main(PSInput input)
{
	PSOutput output;

	// テクスチャマッピング
	float4 tex0Color = tex0.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;
	float4 tex1Color = tex1.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;
	float4 maskColor = mask.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;

	// 計算した色で描画
	output.target_ = lerp(tex0Color, tex1Color, maskColor.r);

	return output;
}