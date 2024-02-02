// �g�����X�t�H�[��
cbuffer cbTransform : register(b0)
{
    matrix matWorld_; // ���[���h�s��
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

// �����F�ݒ�
cbuffer cbDiscardColor : register(b3)
{
    float3 discardColor_; // �F(RGB)
    float threshold_; // 臒l
}

// ���_�V�F�[�_�[�̓��͍\����
struct VSInput
{
	// ���_���W
    float4 pos_ : POSITION;
	// uv�l
    float2 uv_ : TEXCOORD;
};

// �s�N�Z���V�F�[�_�[�̓��͍\����
struct PSInput
{
	// �V�X�e���p���_���W
    float4 svpos_ : SV_POSITION;
	// uv�l
    float2 uv_ : TEXCOORD;
};

// �s�N�Z���V�F�[�_�[�̏o�͍\����
struct PSOutput
{
	// �`��
    float4 target_ : SV_TARGET0;
};
