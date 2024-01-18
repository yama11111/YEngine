#include "Model.hlsli"

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

PSOutput main(PSInput input)
{
	PSOutput output;

	// �e�N�X�`���}�b�s���O
	float4 texColor = tex.Sample(smp, input.uv * texTiling_ + texOffset_) * texColorRate_;

	// �F
	float4 color = texColor * baseColor_;

	output.target = color;

	return output;


	// ����x
	const float shininess = 4.0f;


	// �����ˌ�
	float3 ambient = color.rgb * ambient_ * ambientColor_;

	// �V�F�[�f�B���O�F
	float3 shaderColor = ambient;


	// ���C�g���̌v�Z
	for (float i = 0; i < DireLightNum; i++)
	{
		// ���s����
		if (direLights_[i].active)
		{
			// ���C�g�Ɍ������x�N�g���Ɩ@���̌v�Z
			float3 dotLightNormal = dot(direLights_[i].lightVec, input.normal);


			// ���C�g�Ɍ������x�N�g���Ɩ@���̓��ς��N�����v
			float3 intensity = saturate(dotLightNormal);

			// �g�U���ˌ�
			float3 diffuse = intensity * color.rgb * diffuse_;


			// ���ˌ��x�N�g��
			float3 reflectDir = normalize(-direLights_[i].lightVec + (2.0f * dotLightNormal * input.normal));
			
			// ���ʔ��ˌ�
			float3 specular = pow(saturate(dot(reflectDir, input.eyeDir)), shininess) * specular_;


			// �S�ĉ��Z
			shaderColor += (diffuse + specular) * direLights_[i].lightColor;
		}
	}
	for (int j = 0; j < PointLightNum; j++)
	{
		// �_����
		if (pointLights_[j].active)
		{
			// ���C�g�̃x�N�g��
			float3 lightVec = normalize(pointLights_[j].lightPos - input.worldPos.xyz);
			
			// ���C�g�Ɍ������x�N�g���Ɩ@���̓���
			float3 dotLightNormal = dot(lightVec, input.normal);
			

			// ���C�g�Ɍ������x�N�g���Ɩ@���̓��ς��N�����v
			float3 intensity = saturate(dotLightNormal);

			// �g�U���ˌ�
			float3 diffuse = intensity * color.rgb * diffuse_;
			

			// ���ˌ��x�N�g��
			float3 reflectDir = normalize(-lightVec + (2.0f * dotLightNormal * input.normal));
			
			// ���ʔ��ˌ�
			float3 specular = pow(saturate(dot(reflectDir, input.eyeDir)), shininess) * specular_;
			

			// �x�N�g���̒���
			float d = length(lightVec);

			// ���������W��
			float atten = 1.0f /
				((pointLights_[j].lightAtten.x) +
					(pointLights_[j].lightAtten.y * d) +
					(pointLights_[j].lightAtten.z * d * d));

			// �S�ĉ��Z
			shaderColor += atten * (diffuse + specular) * pointLights_[j].lightColor;
		}
	}
	for (int k = 0; k < SpotLightNum; k++)
	{
		// �X�|�b�g���C�g����
        if (spotLights_[k].active)
        {
			// ���C�g�̃x�N�g��
            float3 lightVec = spotLights_[k].lightPos - input.worldPos.xyz;
			// �x�N�g���̒���
            float d = length(lightVec);
			// ���K��
            lightVec = normalize(lightVec);
			// ���������W��
            float atten = 1.0f / 
				(spotLights_[k].lightAtten.x + 
				(spotLights_[k].lightAtten.y * d) + 
				(spotLights_[k].lightAtten.z * d * d));
			// �p�x����
            float cos = dot(lightVec, spotLights_[k].lightVec);
			// �J�n�p�x���I���p�x�Ɍ��� (�J�n���� : 1�{, �I���O�� : 0�{ �̋P�x)
            float angleAtten = smoothstep(spotLights_[k].lightEndFactorAngleCos, spotLights_[k].lightStartFactorAngleCos, cos);
			// �p�x��������Z
            atten *= angleAtten;
			// ���C�g�Ɍ������x�N�g���Ɩ@���̓���
            float3 dotLightNormal = dot(lightVec, input.normal);
			// ���ˌ��x�N�g��
            float3 reflect = normalize(-lightVec + (2.0f * dotLightNormal * input.normal));
			// �g�U���ˌ�
            float3 diffuse = dotLightNormal * diffuse_;
			// ���ʔ��ˌ�
            float3 specular = pow(saturate(dot(reflect, input.eyeDir)), shininess) * specular_;

			// �S�ĉ��Z
            shaderColor += atten * (diffuse + specular) * pointLights_[k].lightColor;
        }
    }

	// �v�Z�����F�ŕ`��
	output.target = float4(shaderColor, color.a * alpha_);

	return output;
}