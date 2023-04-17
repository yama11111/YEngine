#include "Light.hlsli"

// 3D�ϊ��s��
cbuffer cbuff0 : register(b0)
{
	matrix matWorld;	 // ���[���h�s��
	matrix matViewProj;	 // �r���[�v���W�F�N�V�����s��
	float3 cameraPos;	 // �J�������W
}
// �F
cbuffer cbuff1 : register(b1)
{
	float4 color; // �F(RGBA)
	float4 originalColorRate; // ���̐F�̊���
}
// ��
cbuffer cbuff2 : register(b2)
{
	float3 ambientColor;		 // �����F
	DireLight direLights[DireLightNum];	 // ���s����
	PointLight pointLights[PointLightNum];	 // �_����
	//SpotLight spotLights[SpotLightNum];	 // �X�|�b�g���C�g����
}
// �}�e���A��2
cbuffer cbuff3 : register(b3)
{
	float3 mAmbient  : packoffset(c0);	 // �A���r�G���g�W��
	float3 mDiffuse  : packoffset(c1);	 // �f�B�t���[�Y�W��
	float3 mSpecular : packoffset(c2);	 // �X�y�L�����[�W��
	float  mAlpha    : packoffset(c2.w); // �A���t�@
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
	// �ڋ��
	float3 tangent : TANGENT;
	// ���_�F
	float4 color : COLOR;
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
};
