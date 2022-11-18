// 3D�ϊ��s��
cbuffer cbuff0 : register(b0)
{
	matrix mat; // 3D�ϊ��s��
}

// �}�e���A��
cbuffer cbuff1 : register(b1)
{
	float3 mAmbient  : packoffset(c0);	 // �A���r�G���g�W��
	float3 mDiffuse  : packoffset(c1);	 // �f�B�t���[�Y�W��
	float3 mSpecular : packoffset(c2);	 // �X�y�L�����[�W��
	float  mAlpha    : packoffset(c2.w); // �A���t�@
}

// ���_�V�F�[�_�[�̏o�͍\����
// (���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����)
struct VSOutput
{
	// �V�X�e���l���_���W
	float4 svpos : SV_POSITION;
	// �@���x�N�g��
	float3 normal : NORMAL;
	// uv�l
	float2 uv : TEXCOORD;
};
