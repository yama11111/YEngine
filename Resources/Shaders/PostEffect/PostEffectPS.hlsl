#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

PSOutput main(PSInput input)
{
	PSOutput output;
	
	// テクスチャマッピング
    float4 texColor0 = tex0.Sample(smp, input.uv_ * texTiling_ + texOffset_);

	output.target_ = texColor0 * baseColor_;

	return output;
}