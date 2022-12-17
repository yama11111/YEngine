#include "Sprite.hlsli"

PSInput main(VSInput input)
{
	PSInput output; // ピクセルシェーダーに渡す値
	output.svpos = mul(mat, input.pos); // 座標に行列を乗算
	output.uv = input.uv;
	return output;
}