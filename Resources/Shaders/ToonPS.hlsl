#include "Toon.hlsli"

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

PSOutput main(PSInput input)
{
	PSOutput output;

	// �e�N�X�`���}�b�s���O
	float4 texColor = tex.Sample(smp, input.uv * texTiling_ + texOffset_) * texColorRate_;

	// �F
	float4 color = texColor * baseColor_;


	// ����x
	const float shininess = 4.0f;

	// 臒l (���E) �����l
	const float thresholdStart = 0.4f;

	// 臒l (���E) �ŏI�l
	const float thresholdEnd = thresholdStart + 0.05f;


	// ���s�����̌���
	float3 direLightVec = normalize(float3(-1.0f, +1.0f, -1.0f));

	// ���s�����̐F
	float3 direLightColor = float3(1.0f, 1.0f, 1.0f);


	// ���C�g�Ɍ������x�N�g���Ɩ@���̌v�Z
	float3 dotLightNormal = dot(direLightVec, input.normal);


	// �����ˌ�
	float3 ambient = color.rgb * ambient_;


	// ���C�g�Ɍ������x�N�g���Ɩ@���̓��ς��N�����v
	float3 intensity = saturate(dotLightNormal);

	// ���ςɃX���[�X�X�e�b�v��K��
	intensity = smoothstep(thresholdStart, thresholdEnd, intensity);

	// �g�U���ˌ�
	float3 diffuse = intensity * color.rgb * diffuse_;


	// ���ˌ��x�N�g��
	float3 reflectDir = normalize(-direLightVec + (2.0f * dotLightNormal * input.normal));

	// ���ʔ��ˌ�
	float3 specular = pow(saturate(dot(reflectDir, input.eyeDir)), shininess) * specular_;

	// ���ʔ��ˌ��ɃX���[�X�X�e�b�v��K��
	specular = smoothstep(thresholdStart, thresholdEnd, specular);


	// �S�ĉ��Z
	float3 shaderColor = (ambient + diffuse + specular) * direLightColor;

	// �v�Z�����F�ŕ`��
	output.target = float4(shaderColor, color.a * alpha_);

	return output;
}