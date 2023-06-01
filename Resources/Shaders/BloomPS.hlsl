#include "PostEffect.hlsli"

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

// ����
static const float ArrayNum = 3;

// 1�s�N�Z��
static const float2 Pixel = float2(1.0f, 1.0f) / float2(1280.0f, 720.0f);

// 臒l
static const float Threshold = 0.4f;

float4 main(PSInput input) : SV_TARGET
{
	// ����p
	float4 decisionColor = tex.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;

	// �s�N�Z���̖��邳
	float bright = (decisionColor.r + decisionColor.g + decisionColor.b) / 3.0f;

	// 臒l�ȉ��͍�
	float colorRate = 1.0f - step(Threshold, bright);


	// �v�Z�p
	float4 resultColor = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// �����UV�l
	float2 leftTopUV = input.uv_ * texTiling_ + texOffset_ - float2((ArrayNum - 1), (ArrayNum - 1)) / 2.0f;

	// y��
	for (float y = 0; y < ArrayNum; y++)
	{
		// x��
		for (float x = 0; x < ArrayNum; x++)
		{
			// ����镪
			float2 offsetUV = Pixel * float2(x, y);

			// �e�N�X�`���}�b�s���O
			float4 texColor = tex.Sample(smp, leftTopUV + offsetUV) * texColorRate_ * float4(colorRate, colorRate, colorRate, colorRate);

			// �����Ă���
			resultColor += texColor;
		}
	}

	// ���ω�
	resultColor /= float(ArrayNum * ArrayNum);

	// �v�Z�����F�ŕ`��
	return float4(resultColor.xyz * baseColor_.xyz, 1.0f);
}