#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> tex1 : register(t1); // 1�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(PSInput input) : SV_TARGET
{
	float _ShiftWidth = 0.005f;
	float _ShiftNum = 3.0f;

	float4 texColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float num = 0.0f;

	for (float py = -_ShiftNum / 2; py <= _ShiftNum / 2; py++)
	{
		for (float px = -_ShiftNum / 2; px <= _ShiftNum / 2; px++)
		{
			texColor += tex0.Sample(smp, input.uv_ + float2(px, py) * _ShiftWidth);
			num++;
		}
	}

	texColor.rgb = texColor.rgb / num;
	texColor.a = 1;
	return texColor;
}