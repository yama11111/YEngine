#include "Light.hlsli"

// �g�����X�t�H�[��
cbuffer cbTransform : register(b0)
{
	matrix matWorld_; // ���[���h�s��
	matrix matViewProj_; // �r���[�v���W�F�N�V�����s��
	float3 cameraPos_; // �J�������W
}

// �F
cbuffer cbColor : register(b1)
{
	float4 baseColor_; // �F(RGBA)
	float4 texColorRate_; // ���̐F�̊���
}

// �e�N�X�`���ݒ�
cbuffer cbTexConfig : register(b2)
{
	float2 texTiling_; // �^�C�����O
	float2 texOffset_; // �I�t�Z�b�g
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
	// �V�X�e���p���_���W
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
