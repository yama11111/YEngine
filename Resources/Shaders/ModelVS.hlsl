#include "Model.hlsli"

VSOutput main(VSInput input)
{
	VSOutput output; // �s�N�Z���V�F�[�_�[�ɓn���l
	output.svpos = mul(mat, input.pos); // ���W�ɍs�����Z
	output.normal = input.normal;
	output.uv = input.uv;
	return output;
}