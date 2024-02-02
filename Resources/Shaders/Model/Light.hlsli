// ���s����
static const float DireLightNum = 3;
struct DireLight
{
	float3 lightVec;	 // ����
	float3 lightColor;	 // �F
	float active;		 // ����t���O
};

// �_����
static const float PointLightNum = 3;
struct PointLight
{
	float3 lightPos;	 // ���W
	float3 lightColor;	 // �F
	float3 lightAtten;	 // ���������W��
	float active;		 // ����t���O
};

// �X�|�b�g���C�g����
static const float SpotLightNum = 3;
struct SpotLight
{
    float3 lightPos; // ���W
    float3 lightVec; // ����
    float3 lightColor; // �F
    float3 lightAtten; // ���������W��
    float lightStartFactorAngleCos; // �����J�n�p�x
    float lightEndFactorAngleCos; // �����I���p�x
    float active; // ����t���O
};

struct LightGroup
{
	float3 ambientColor; // �����F
	DireLight direLights[DireLightNum]; // ���s����
	PointLight pointLights[PointLightNum]; // �_����
	SpotLight spotLights[SpotLightNum]; // �X�|�b�g���C�g����
};