// �g�����X�t�H�[��
cbuffer cbuff0 : register(b0)
{
	matrix matWorld_; // 3D�ϊ��s��
	matrix matBillboard_; // �r���{�[�h�s��
}

// �F
cbuffer cbuff1 : register(b1)
{
	float4 baseColor_; // �F(RGBA)
	float4 texColorRate_; // ���̐F�̊���
}

// �e�N�X�`���ݒ�
cbuffer cbuff2 : register(b2)
{
	float2 texTiling_; // �^�C�����O
	float2 texOffset_; // �I�t�Z�b�g
}


// ���_�V�F�[�_�[�̓��͍\���� 
struct VSInput 
{
	// ���_���W
	float4 pos_ : POSITION;
};

// �W�I���g���V�F�[�_�[�̓��͍\���� 
struct GSInput 
{
	// ���_���W
	float4 pos_ : POSITION;
};

// �s�N�Z���V�F�[�_�[�̓��͍\���� 
struct PSInput
{
	// �V�X�e���p���_���W
	float4 svpos_ : SV_POSITION;
	// uv�l
	float2 uv_ : TEXCOORD;
};
