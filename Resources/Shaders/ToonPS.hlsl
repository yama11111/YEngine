#include "Model.hlsli"

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(PSInput input) : SV_TARGET
{
	// �e�N�X�`���}�b�s���O
	float4 texColor = tex.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;

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
	float3 dotLightNormal = dot(direLightVec, input.normal_);


	// �����ˌ�
	float3 ambient = color.rgb * mAmbient_;


	// ���C�g�Ɍ������x�N�g���Ɩ@���̓��ς��N�����v
	float3 intensity = saturate(dotLightNormal);

	// ���ςɃX���[�X�X�e�b�v��K��
	intensity = smoothstep(thresholdStart, thresholdEnd, intensity);

	// �g�U���ˌ�
	float3 diffuse = intensity * color.rgb * mDiffuse_;


	// ���ˌ��x�N�g��
	float3 reflectDir = normalize(-direLightVec + (2.0f * dotLightNormal * input.normal_));

	// ���ʔ��ˌ�
	float3 specular = pow(saturate(dot(reflectDir, input.eyeDir_)), shininess) * mSpecular_;

	// ���ʔ��ˌ��ɃX���[�X�X�e�b�v��K��
	specular = smoothstep(thresholdStart, thresholdEnd, specular);


	// �S�ĉ��Z
	float3 shaderColor = (ambient + diffuse + specular) * direLightColor;


	// �v�Z�����F�ŕ`��
	return float4(shaderColor, color.a * mAlpha_);
}