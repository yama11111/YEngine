// �g�����X�t�H�[��
cbuffer cbuff0 : register(b0)
{
	matrix matWorld_; // ���[���h�s��
	matrix matViewProj_; // �r���[�v���W�F�N�V�����s��
	float3 cameraPos_; // �J�������W
}

// ����
cbuffer cbuff1 : register(b1)
{
	float time_; // ����
}

// �F
cbuffer cbuff2 : register(b2)
{
	float4 baseColor_; // �F(RGBA)
	float4 texColorRate_; // ���̐F�̊���
}

// �e�N�X�`���ݒ�
cbuffer cbuff3 : register(b3)
{
	float2 texTiling_; // �^�C�����O
	float2 texOffset_; // �I�t�Z�b�g
}

// ���_�V�F�[�_�[�̓��͍\���� 
struct VSInput
{
	// ���_���W
	float4 pos_ : POSITION;
	// �@���x�N�g��
	float3 normal_ : NORMAL;
	// uv�l
	float2 uv_ : TEXCOORD;
	//// �ڋ��
	//float3 tangent_ : TANGENT;
	//// ���_�F
	//float4 color_ : COLOR;
};

// �s�N�Z���V�F�[�_�[�̓��͍\���� 
struct PSInput
{
	// �V�X�e���l���_���W
	float4 svPos_ : SV_POSITION;
	// ���[���h���W
	float4 worldPos_ : POSITION;
	// �@���x�N�g��
	float3 normal_ : NORMAL;
	// uv�l
	float2 uv_ : TEXCOORD;

	// �����x�N�g��
	float3 eyeDir_ : EYE_DIRECTION;
};

// �s�N�Z���V�F�[�_�[�̏o�͍\����
struct PSOutput
{
	// �`��
	float4 target_ : SV_TARGET;
};
