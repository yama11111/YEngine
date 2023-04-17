#include "Sprite3D.hlsli"

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(PSInput input) : SV_TARGET
{
	// �e�N�X�`���F
	float4 texColor = tex.Sample(smp, input.uv) * originalColorRate;

	// �v�Z�����F�ŕ`��
	return texColor * color;
}