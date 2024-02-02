// �ۉe
static const float CircleShadowNum = 30;
struct CircleShadow
{
    float3 shadowDir; // ����
    float3 casterPos; // �L���X�^�[���W
    float distanceFromCasterToShadow; // �L���X�^�[����e�̋���
    float3 shadowAtten; // ���������W��
    float shadowStartFactorAngleCos; // �����J�n�p�x
    float shadowEndFactorAngleCos; // �����I���p�x
    float active; // ����t���O
};

/// <summary>
/// �ۉe�̉e�F�l���v�Z����
/// </summary>
/// <returns>�e�F�l</returns>
float CalcCircleShadowColor(
	CircleShadow circleShadows_[CircleShadowNum], 
	const float3 worldPos)
{
    float result = 0.0f;
	
    for (float i = 0; i < CircleShadowNum; i++)
    {
        if (circleShadows_[i].active <= 0.0f) { continue; }
		
		// �����𔽓]
        float3 shadowDir = -circleShadows_[i].shadowDir;
		
		// �I�u�W�F�N�g �� �L���X�^�[ �̃x�N�g��
        float3 objToCasterVec = circleShadows_[i].casterPos - worldPos;
			
		// ���e�����̋���
        float d = dot(objToCasterVec, shadowDir);
			
		// ���������W��
        float atten = 
			saturate(1.0f /
				(circleShadows_[i].shadowAtten.x +
				circleShadows_[i].shadowAtten.y * d +
				circleShadows_[i].shadowAtten.z * d * d));
			
		// ���� 0�ȉ� �� 0 ��
        atten *= step(0, d);

		// �e(���z���C�g)�̍��W
        float3 shadowPos =
			circleShadows_[i].casterPos +
			shadowDir * circleShadows_[i].distanceFromCasterToShadow;
			
		// �I�u�W�F�N�g �� �e �̃x�N�g��
        float3 objToShadowVec = normalize(shadowPos - worldPos);

		// �p�x����
		// �����J�n�p �� �����I���p �ɂ����Č���
		// ���� �� 1�{�A�O�� �� 0�{ �̋P�x
        float cosAngle = dot(objToShadowVec, shadowDir);
        float angelAtten = 
			smoothstep(
				cos(circleShadows_[i].shadowEndFactorAngleCos),
				cos(circleShadows_[i].shadowStartFactorAngleCos),
				cosAngle);
			
		// �p�x��������Z
        atten *= angelAtten;
			
		// �S�Č��Z����
        result -= atten;
    }
	
    return result;
}