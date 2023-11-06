#include "Outline.hlsli"

PSInput main(VSInput input)
{
	matrix matW = mul(matWorld_, matrix(
		1.0f + range_, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f + range_, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f + range_, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f));

	// �@���Ƀ��[���h�s��ɂ��X�P�[�����O�A��]��K�p
	float4 wNormal = normalize(mul(matW, float4(input.normal_, 0)));
	float4 wPos = mul(matW, input.pos_);


	// �s�N�Z���V�F�[�_�[�ɓn���l
	PSInput output;


	// �V�X�e�����_
	output.svPos_ = mul(mul(matViewProj_, matW), input.pos_);

	// ���[���h���W
	output.worldPos_ = wPos;

	// �@���x�N�g��
	output.normal_ = wNormal.xyz;

	// UV���W
	output.uv_ = input.uv_;

	// ���_���王�_�ւ̕����x�N�g��
	output.eyeDir_ = normalize(cameraPos_ - wPos.xyz);


	return output;
}