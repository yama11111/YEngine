#include "Model.hlsli"

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

//float4 main(PSInput input) : SV_TARGET
//{
//	float3 light = normalize(float3(1, -1, 1)); // �E���� �����̃��C�g
//	float diffuse = saturate(dot(-light, input.normal)); // diffuse��[0,1]�͈̔͂�clamp����
//	float3 shaderColor = mAmbient; // �A���r�G���g��
//	shaderColor += mDiffuse * diffuse; // �f�B�t���[�Y��
//	float4 texcolor = float4(tex.Sample(smp, input.uv));
//	//return float4(texcolor.rgb * shaderColor, texcolor.a * mAlpha) * color; // �P�x��RGB�ɑ�����ďo��
//	return float4(texcolor.rgb * shaderColor, texcolor.a * mAlpha) * color; // �P�x��RGB�ɑ�����ďo��
//}

float4 main(PSInput input) : SV_TARGET
{
	// �e�N�X�`���}�b�s���O
	float4 texColor = tex.Sample(smp, input.uv);
	//texColor.y = texColor.x + (texColor.y - texColor.x) * ratio;
	//texColor.z = texColor.x + (texColor.z - texColor.x) * ratio;
	// ����x
	const float shininess = 4.0f;
	// ���_���王�_�ւ̕����x�N�g��
	float3 eyeDir = normalize(cameraPos - input.worldPos.xyz);

	// �����ˌ�
	float3 ambient = mAmbient;

	// �V�F�[�f�B���O�F
	float4 shaderColor = float4(ambientColor * ambient, mAlpha);

	// ���C�g���̌v�Z
	for (int i = 0; i < DireLightNum; i++)
	{
		// ���s����
		if (direLights[i].active)
		{
			// ���C�g�Ɍ������x�N�g���Ɩ@���̌v�Z
			float3 dotLightNormal = dot(direLights[i].lightVec, input.normal);
			// ���ˌ��x�N�g��
			float3 reflect = normalize(-direLights[i].lightVec + (2.0f * dotLightNormal * input.normal));
			// �g�U���ˌ�
			float3 diffuse = dotLightNormal * mDiffuse;
			// ���ʔ��ˌ�
			float3 specular = pow(saturate(dot(reflect, eyeDir)), shininess) * mSpecular;

			// �S�ĉ��Z
			shaderColor.rgb += (ambient + diffuse + specular) * direLights[i].lightColor;
		}
	}
	for (int j = 0; j < PointLightNum; j++)
	{
		// �_����
		if (pointLights[j].active)
		{
			// ���C�g�̃x�N�g��
			float3 lightVec = pointLights[j].lightPos - input.worldPos.xyz;
			// �x�N�g���̒���
			float d = length(lightVec);
			// ���K��
			lightVec = normalize(lightVec);
			// ���������W��
			float atten = 1.0f / (pointLights[j].lightAtten.x + (pointLights[j].lightAtten.y * d) + (pointLights[j].lightAtten.z * d * d));
			// ���C�g�Ɍ������x�N�g���Ɩ@���̓���
			float3 dotLightNormal = dot(lightVec, input.normal);
			// ���ˌ��x�N�g��
			float3 reflect = normalize(-lightVec + (2.0f * dotLightNormal * input.normal));
			// �g�U���ˌ�
			float3 diffuse = dotLightNormal * mDiffuse;
			// ���ʔ��ˌ�
			float3 specular = pow(saturate(dot(reflect, eyeDir)), shininess) * mSpecular;
			
			// �S�ĉ��Z
			shaderColor.rgb += atten * (diffuse + specular) * pointLights[j].lightColor;
		}
	}
	//for (int k = 0; k < SpotLightNum; k++)
	//{
	//	// �X�|�b�g���C�g����
	//	if (spotLights[k].active)
	//	{
	//		// ���C�g�̃x�N�g��
	//		float3 lightVec = spotLights[k].lightPos - input.worldPos.xyz;
	//		// �x�N�g���̒���
	//		float d = length(lightVec);
	//		// ���K��
	//		lightVec = normalize(lightVec);
	//		// ���������W��
	//		float atten = 1.0f / (spotLights[k].lightAtten.x + (spotLights[k].lightAtten.y * d) + (spotLights[k].lightAtten.z * d * d));
	//		// �p�x����
	//		float cos = dot(lightVec, spotLights[k].lightVec);
	//		// �J�n�p�x���I���p�x�Ɍ��� (�J�n���� : 1�{, �I���O�� : 0�{ �̋P�x)
	//		float angleAtten = smoothstep(spotLights[k].lightEndFactorAngleCos, spotLights[k].lightStartFactorAngleCos, cos);
	//		// �p�x��������Z
	//		atten *= angleAtten;
	//		// ���C�g�Ɍ������x�N�g���Ɩ@���̓���
	//		float3 dotLightNormal = dot(lightVec, input.normal);
	//		// ���ˌ��x�N�g��
	//		float3 reflect = normalize(-lightVec + (2.0f * dotLightNormal * input.normal));
	//		// �g�U���ˌ�
	//		float3 diffuse = dotLightNormal * mDiffuse;
	//		// ���ʔ��ˌ�
	//		float3 specular = pow(saturate(dot(reflect, eyeDir)), shininess) * mSpecular;

	//		// �S�ĉ��Z
	//		shaderColor.rgb += atten * (diffuse + specular) * pointLights[k].lightColor;
	//	}
	//}

	// �V�F�[�f�B���O�F�ŕ`��
	return (shaderColor * texColor) * color;
}