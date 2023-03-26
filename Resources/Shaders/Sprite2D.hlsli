// 3D�ϊ��s��
cbuffer cbuff0 : register(b0)
{
	matrix matWorld; // 3D�ϊ��s��
}
// �F
cbuffer cbuff1 : register(b1)
{
	float4 color; // �F(RGBA)
}

// ���_�V�F�[�_�[�̓��͍\����
struct VSInput
{
	// ���_���W
	float4 pos : POSITION;
	// uv�l
	float2 uv : TEXCOORD;
};
// �s�N�Z���V�F�[�_�[�̓��͍\����
struct PSInput
{
	// �V�X�e���p���_���W
	float4 svpos : SV_POSITION;
	// uv�l
	float2 uv : TEXCOORD;
};
