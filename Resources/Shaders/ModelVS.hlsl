#include "Model.hlsli"

VSOutput main(VSInput input)
{
	VSOutput output; // ピクセルシェーダーに渡す値
	output.svpos = mul(mat, input.pos); // 座標に行列を乗算
	output.normal = input.normal;
	output.uv = input.uv;
	return output;
}