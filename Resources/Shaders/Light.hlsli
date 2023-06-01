// ���s����
static const float DireLightNum = 3;
struct DireLight
{
	float3 lightVec_;	 // ����
	float3 lightColor_;	 // �F
	float active_;		 // ����t���O
};

// �_����
static const float PointLightNum = 3;
struct PointLight
{
	float3 lightPos_;	 // ���W
	float3 lightColor_;	 // �F
	float3 lightAtten_;	 // ���������W��
	float active_;		 // ����t���O
};

// �X�|�b�g���C�g����
static const float SpotLightNum = 3;
//struct SpotLight
//{
//	float3 lightPos_;	 // ���W
//	float3 lightVec_;	 // ����
//	float3 lightColor_;	 // �F
//	float3 lightAtten_;	 // ���������W��
//	float  lightStartFactorAngleCos_; // �����J�n�p�x
//	float  lightEndFactorAngleCos_;	 // �����I���p�x
//	float active_;		 // ����t���O
//};

struct LightGroup
{
	float3 ambientColor_; // �����F
	DireLight direLights_[DireLightNum]; // ���s����
	PointLight pointLights_[PointLightNum]; // �_����
	//SpotLight spotLights_[SpotLightNum]; // �X�|�b�g���C�g����
};