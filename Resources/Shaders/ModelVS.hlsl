#include "Model.hlsli"

//PSInput main(VSInput input)
//{
//	PSInput output; // �s�N�Z���V�F�[�_�[�ɓn���l
//	output.svpos = mul(matWorld, input.pos); // ���W�ɍs�����Z
//	output.normal = input.normal;
//	output.uv = input.uv;
//	return output;
//}

PSInput main(VSInput input)
{
	// �@���Ƀ��[���h�s��ɂ��X�P�[�����O�A��]��K�p
	float4 wNormal = normalize(mul(matWorld, float4(input.normal, 0)));
	float4 wPos = mul(matWorld, input.pos);

	// �s�N�Z���V�F�[�_�[�ɓn���l
	PSInput output;
	output.svPos = mul(mul(matViewProj, matWorld), input.pos);
	output.worldPos = wPos;
	output.normal = wNormal.xyz;
	output.uv = input.uv;

	return output;
}