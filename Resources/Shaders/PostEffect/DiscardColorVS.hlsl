#include "DiscardColor.hlsli"

PSInput main(VSInput input)
{
    PSInput output; // ピクセルシェーダーに渡す値
    
    output.svpos_ = mul(matWorld_, input.pos_); // 座標に行列を乗算
    output.uv_ = input.uv_;
    
    return output;
}