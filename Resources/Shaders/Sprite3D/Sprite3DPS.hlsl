#include "Sprite3D.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

PSOutput main(PSInput input)
{
	PSOutput output;

	// テクスチャマッピング
	float4 texColor = tex.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;

    float4 color = texColor * baseColor_;

    clip(color.a - 0.0001f);
	
	// 計算した色で描画
	output.target_ = color;

	return output;
}