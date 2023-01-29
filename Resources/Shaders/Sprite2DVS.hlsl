#include "Sprite2D.hlsli"

PSInput main(VSInput input)
{
	PSInput output; // ピクセルシェーダーに渡す値
	output.svpos = mul(matWorld, input.pos); // 座標に行列を乗算
	output.uv = input.uv;
	return output;
}