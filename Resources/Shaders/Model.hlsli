#include "Light.hlsli"

// �g�����X�t�H�[��
cbuffer cbuff0 : register(b0)
{
	matrix matWorld_; // ���[���h�s��
	matrix matViewProj_; // �r���[�v���W�F�N�V�����s��
	float3 cameraPos_; // �J�������W
}

// �F
cbuffer cbuff1 : register(b1)
{
	float4 baseColor_; // �F(RGBA)
	float4 texColorRate_; // ���̐F�̊���
}

// �}�e���A��
cbuffer cbuff2 : register(b2)
{
	float3 mAmbient_  : packoffset(c0); // �A���r�G���g�W��
	float3 mDiffuse_  : packoffset(c1); // �f�B�t���[�Y�W��
	float3 mSpecular_ : packoffset(c2); // �X�y�L�����[�W��
	float  mAlpha_ : packoffset(c2.w); // �A���t�@
}

// ��
cbuffer cbuff3 : register(b3)
{
	float3 ambientColor_; // �����F
	DireLight direLights_[DireLightNum]; // ���s����
	PointLight pointLights_[PointLightNum]; // �_����
	//SpotLight spotLights[SpotLightNum]; // �X�|�b�g���C�g����
}

// �e�N�X�`���ݒ�
cbuffer cbuff4 : register(b4)
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
