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

// ���_�V�F�[�_�[�̏o�͍\���� (���_�V�F�[�_�[ �� �s�N�Z���V�F�[�_�[)
struct VSOutput
{
	// �V�X�e���p���_���W
	float4 svpos : SV_POSITION;
	// �@���x�N�g��
	float3 normal : NORMAL;
	// uv�l
	float2 uv : TEXCOORD;
};
