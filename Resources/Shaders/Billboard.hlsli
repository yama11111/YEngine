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
// �r���{�[�h
cbuffer cbuff3 : register(b3)
{
	matrix matBillboard; // �r���{�[�h�s��
}

// ���_�V�F�[�_�[�̓��͍\���� 
struct VSInput 
{
	// ���_���W
	float4 pos : POSITION;
};
// �W�I���g���V�F�[�_�[�̓��͍\���� 
struct GSInput 
{
	// ���_���W
	float4 pos : POSITION;
};
// �s�N�Z���V�F�[�_�[�̓��͍\���� 
struct PSInput
{
	// �V�X�e���p���_���W
	float4 svpos : SV_POSITION;
	//// �@���x�N�g��
	//float3 normal : NORMAL;
	// uv�l
	float2 uv : TEXCOORD;
};
