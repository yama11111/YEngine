#include "SingleColor.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

PSOutput main(PSInput input)
{
	PSOutput output;
	
    clip(baseColor_.a - 0.1f);
	
	output.target = baseColor_;

	return output;
}