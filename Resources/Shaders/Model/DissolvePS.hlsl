#include "Dissolve.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
Texture2D<float4> mask : register(t1); // 1番スロットに設定されたマスクテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

PSOutput main(PSInput input)
{
	PSOutput output;

	// テクスチャマッピング
	float4 texColor = tex.Sample(smp, input.uv * texTiling_ + texOffset_);
	
    clip(texColor.a - 0.1f);
    
    texColor *= texColorRate_;
	
	float4 maskColor = mask.Sample(smp, input.uv * texTiling_ + texOffset_);

	// (赤色値 - 時間) < 0 なら描画切る
	clip(maskColor.r - time_);
	
	// 計算した色で描画
	output.target = texColor * baseColor_;

	return output;
}