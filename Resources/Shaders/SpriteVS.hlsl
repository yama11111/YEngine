#include "Sprite.hlsli"

PSInput main(VSInput input)
{
	PSInput output; // �s�N�Z���V�F�[�_�[�ɓn���l
	output.svpos = mul(mat, input.pos); // ���W�ɍs�����Z
	output.uv = input.uv;
	return output;
}