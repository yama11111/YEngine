#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0番スロットに設定されたサンプラー

// 閾値
static const float kThreshold = 1.0f;

PSOutput main(PSInput input)
{
    PSOutput output;
	
    // テクスチャマッピング
    float4 texColor0 = tex0.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;

    output.target_ = texColor0 * baseColor_;
    
    // アルファ値の割合
    // マゼンタの時に0になる
    float alphaRatio = 1.0f - (step(kThreshold, texColor0.r) * step(kThreshold, texColor0.b));
    
    output.target_.a *= alphaRatio;

    return output;
}