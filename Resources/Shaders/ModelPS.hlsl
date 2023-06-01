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


	// �����ˌ�
	float3 ambient = color.rgb * mAmbient_ * ambientColor_;

	// �V�F�[�f�B���O�F
	float3 shaderColor = ambient;


	// ���C�g���̌v�Z
	for (float i = 0; i < DireLightNum; i++)
	{
		// ���s����
		if (direLights_[i].active_)
		{
			// ���C�g�Ɍ������x�N�g���Ɩ@���̌v�Z
			float3 dotLightNormal = dot(direLights_[i].lightVec_, input.normal_);


			// ���C�g�Ɍ������x�N�g���Ɩ@���̓��ς��N�����v
			float3 intensity = saturate(dotLightNormal);

			// �g�U���ˌ�
			float3 diffuse = intensity * color.rgb * mDiffuse_;


			// ���ˌ��x�N�g��
			float3 reflectDir = normalize(-direLights_[i].lightVec_ + (2.0f * dotLightNormal * input.normal_));
			
			// ���ʔ��ˌ�
			float3 specular = pow(saturate(dot(reflectDir, input.eyeDir_)), shininess) * mSpecular_;


			// �S�ĉ��Z
			shaderColor += (diffuse + specular) * direLights_[i].lightColor_;
		}
	}
	for (int j = 0; j < PointLightNum; j++)
	{
		// �_����
		if (pointLights_[j].active_)
		{
			// ���C�g�̃x�N�g��
			float3 lightVec = normalize(pointLights_[j].lightPos_ - input.worldPos_.xyz);
			
			// ���C�g�Ɍ������x�N�g���Ɩ@���̓���
			float3 dotLightNormal = dot(lightVec, input.normal_);
			

			// ���C�g�Ɍ������x�N�g���Ɩ@���̓��ς��N�����v
			float3 intensity = saturate(dotLightNormal);

			// �g�U���ˌ�
			float3 diffuse = intensity * color.rgb * mDiffuse_;
			

			// ���ˌ��x�N�g��
			float3 reflectDir = normalize(-lightVec + (2.0f * dotLightNormal * input.normal_));
			
			// ���ʔ��ˌ�
			float3 specular = pow(saturate(dot(reflectDir, input.eyeDir_)), shininess) * mSpecular_;
			

			// �x�N�g���̒���
			float d = length(lightVec);

			// ���������W��
			float atten = 1.0f /
				((pointLights_[j].lightAtten_.x) +
					(pointLights_[j].lightAtten_.y * d) +
					(pointLights_[j].lightAtten_.z * d * d));

			// �S�ĉ��Z
			shaderColor += atten * (diffuse + specular) * pointLights_[j].lightColor_;
		}
	}
	for (int k = 0; k < SpotLightNum; k++)
	{
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
	//		shaderColor += atten * (diffuse + specular) * pointLights[k].lightColor;
	//	}
	}

	// �v�Z�����F�ŕ`��
	return float4(shaderColor, color.a * mAlpha_);
}