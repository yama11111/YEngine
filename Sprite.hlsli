// �}�e���A��
cbuffer ConstBufferDataMaterial : register(b0)
{
	float4 color; // �F(RGBA)
}

// 3D�ϊ��s��
cbuffer ConstBufferDataTransform : register(b1)
{
	matrix mat; // 3D�ϊ��s��
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
