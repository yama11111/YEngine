// �g�����X�t�H�[��
cbuffer cbuff0 : register(b0)
{
	matrix matWorld_; // ���[���h�s��
	matrix matViewProj_; // �r���[�v���W�F�N�V�����s��
	float3 cameraPos_; // �J�������W
}

// �A�E�g���C��
cbuffer cbuff1 : register(b1)
{
	float4 color_; // �F(RGBA)
	float range_; // �͈�
}

// ���_�V�F�[�_�[�̓��͍\���� 
struct VSInput
{
	// ���_���W
	float4 pos : POSITION;
	// �@���x�N�g��
	float3 normal : NORMAL;
	// uv�l
	float2 uv : TEXCOORD;
};

// �s�N�Z���V�F�[�_�[�̓��͍\���� 
struct PSInput
{
	// �V�X�e���l���_���W
	float4 svPos : SV_POSITION;
	// ���[���h���W
	float4 worldPos : POSITION;
	// �@���x�N�g��
	float3 normal : NORMAL;
	// uv�l
	float2 uv : TEXCOORD;
	// �����x�N�g��
	float3 eyeDir : EYE_DIRECTION;
};

// �s�N�Z���V�F�[�_�[�̏o�͍\����
struct PSOutput
{
	// �`��
	float4 target : SV_TARGET;
};
