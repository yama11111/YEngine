#include "PostEffect.hlsli"

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

// 
static const float _Sigma = 0.5f;

// ��
static const float _StepWidth = 0.5f;


float Gaussian(float2 drawUV, float2 pickUV, float sigma)
{
	float d = distance(drawUV, pickUV);
	return exp(-(d * d) / (2 * sigma * sigma));
}

float4 main(PSInput input) : SV_TARGET
{
	// ���v�E�F�C�g
	float totalWeight = 0;

	// �v�Z�p
	float4 resultColor = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// y��
	for (float py = -_Sigma * 2.0f; py <= _Sigma * 2; py += _StepWidth)
	{
		// x��
		for (float px = -_Sigma * 2.0f; px <= _Sigma * 2; px += _StepWidth)
		{
			float2 pickUV = input.uv_ + float2(px, py);
			float weight = Gaussian(input.uv_, pickUV, _Sigma);
			resultColor += tex.Sample(smp, pickUV) * weight;
			totalWeight += weight;
		}
	}

	// ���ω�
	resultColor = float4(resultColor.rgb / totalWeight, 1.0f);
	
	// �v�Z�����F�ŕ`��
	return resultColor;
}