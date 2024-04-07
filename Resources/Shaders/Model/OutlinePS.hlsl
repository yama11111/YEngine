#include "Outline.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

PSOutput main(PSInput input)
{
	PSOutput output;
	
    clip(color_.a - 0.1f);
	
	output.target = color_;

	return output;
}