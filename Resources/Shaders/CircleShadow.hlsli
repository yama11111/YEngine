// �ۉe
static const float CircleShadowNum = 30;
struct CircleShadow
{
    float3 shadowDir_; // ����
    float3 casterPos_; // �L���X�^�[���W
    float distanceFromCasterToShadow_; // �L���X�^�[����e�̋���
    float3 shadowAtten_; // ���������W��
    float shadowStartFactorAngleCos_; // �����J�n�p�x
    float shadowEndFactorAngleCos_; // �����I���p�x
    float active_; // ����t���O
};