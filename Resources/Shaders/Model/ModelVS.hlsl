#include "Model.hlsli"

PSInput main(VSInput input)
{
	// �@���Ƀ��[���h�s��ɂ��X�P�[�����O�A��]��K�p
	float4 wNormal = normalize(mul(matWorld_, float4(input.normal, 0)));
	float4 wPos = mul(matWorld_, input.pos);


	// �s�N�Z���V�F�[�_�[�ɓn���l
	PSInput output;
	

	// �V�X�e�����_
	output.svPos = mul(mul(matViewProj_, matWorld_), input.pos);
	
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