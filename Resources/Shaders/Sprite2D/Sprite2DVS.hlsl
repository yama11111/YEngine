#include "Sprite2D.hlsli"

PSInput main(VSInput input)
{
	PSInput output; // �s�N�Z���V�F�[�_�[�ɓn���l
	output.svpos_ = mul(matWorld_, input.pos_); // ���W�ɍs�����Z
	output.uv_ = input.uv_;
	return output;
}