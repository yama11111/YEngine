#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0); // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1); // 1番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

PSOutput main(PSInput input)
{
	PSOutput output;
	
	// テクスチャマッピング
	float4 texColor0 = tex0.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;
	float4 texColor1 = tex1.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;

	output.target_ = texColor1 * baseColor_;

	return output;
}