#include "Sprite2D.hlsli"

PSInput main(VSInput input)
{
	PSInput output; // �s�N�Z���V�F�[�_�[�ɓn���l
	output.svpos = mul(matWorld, input.pos); // ���W�ɍs�����Z
	output.uv = input.uv;
	return output;
}