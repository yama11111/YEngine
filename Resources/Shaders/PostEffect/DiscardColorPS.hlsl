#include "DiscardColor.hlsli"

Texture2D<float4> tex0 : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0番スロットに設定されたサンプラー

PSOutput main(PSInput input)
{
    PSOutput output;
	
    // テクスチャマッピング
    float4 texColor0 = tex0.Sample(smp, input.uv_);
    
    output.target_ = texColor0;
    output.target_.a = 1.0f;
    
    // 消去色と同じ色なら描画弾く
    // 色のベクトルの差の長さが0なら同じ色
    float dis = distance(output.target_.rgb, discardColor_);
    clip(dis - threshold_);
    
    //step(output.target_.rgb, discardColor_);
    
    return output;
}