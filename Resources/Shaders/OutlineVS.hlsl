#include "Outline.hlsli"

PSInput main(VSInput input)
{
	// range���g��
	matrix matW = mul(matWorld_, matrix(
		1.0f + range_, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f + range_, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f + range_, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f));

	// �@���Ƀ��[���h�s��ɂ��X�P�[�����O�A��]��K�p
	float4 wNormal = normalize(mul(matW, float4(input.normal, 0)));
	float4 wPos = mul(matW, input.pos);


	// �s�N�Z���V�F�[�_�[�ɓn���l
	PSInput output;


	// �V�X�e�����_
	output.svPos = mul(mul(matViewProj_, matW), input.pos);

	// ���[���h���W
	output.worldPos = wPos;

	// �@���x�N�g��
	output.normal = wNormal.xyz;

	// UV���W
	output.uv = input.uv;

	// ���_���王�_�ւ̕����x�N�g��
	output.eyeDir = normalize(cameraPos_ - wPos.xyz);


	return output;
}