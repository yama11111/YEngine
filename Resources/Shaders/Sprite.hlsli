// 3D�ϊ��s��
cbuffer cbuff0 : register(b0)
{
	matrix mat; // 3D�ϊ��s��
}

// �}�e���A��
cbuffer cbuff1 : register(b1)
{
	float4 color; // �F(RGBA)
}

// ���_�V�F�[�_�[�̏o�͍\����
// (���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����)
struct VSOutput
{
	// �V�X�e���l���_���W
	float4 svpos : SV_POSITION;
	// uv�l
	float2 uv : TEXCOORD;
};
