#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> tex1 : register(t1); // 1�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(PSInput input) : SV_TARGET
{
	// �e�N�X�`���}�b�s���O
	float4 texColor = tex0.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;

	// �v�Z�����F�ŕ`��
	return float4(1.0f - texColor.rgb * baseColor_.rgb, 1.0f) ;
}