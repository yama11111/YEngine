#include "Model.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

PSOutput main(PSInput input)
{
    PSOutput output;

	// テクスチャマッピング
    float4 texColor = tex.Sample(smp, input.uv * texTiling_ + texOffset_);
    
    clip(texColor.a - 0.1f);
    
    texColor.rgb *= texColorRate_.rgb;
	
    // 色
    float4 color = texColor * baseColor_;

    output.target = color;

    return output;
}