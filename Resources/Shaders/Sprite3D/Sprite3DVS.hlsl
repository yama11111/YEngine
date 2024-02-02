#include "Sprite3D.hlsli"

GSInput main(VSInput input)
{
	GSInput output; // ジオメトリシェーダーに渡す値
	output.pos_ = input.pos_;
	return output;
}