// ���s����
static const int DireLightNum = 3;
struct DireLight
{
	float3 lightVec;	 // ����
	float3 lightColor;	 // �F
	uint active;		 // ����t���O
};
// �_����
static const int PointLightNum = 3;
struct PointLight
{
	float3 lightPos;	 // ���W
	float3 lightColor;	 // �F
	float3 lightAtten;	 // ���������W��
	uint active;		 // ����t���O
};
// �X�|�b�g���C�g����
static const int SpotLightNum = 3;
//struct SpotLight
//{
//	float3 lightPos;	 // ���W
//	float3 lightVec;	 // ����
//	float3 lightColor;	 // �F
//	float3 lightAtten;	 // ���������W��
//	float  lightStartFactorAngleCos; // �����J�n�p�x
//	float  lightEndFactorAngleCos;	 // �����I���p�x
//	uint active;		 // ����t���O
//};