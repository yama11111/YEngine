#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> tex1 : register(t1); // 1�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

PSOutput main(PSInput input)
{
	PSOutput output;
	
	// �e�N�X�`���}�b�s���O
	float4 texColor0 = tex0.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;
	float4 texColor1 = tex1.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;

	output.target_ = texColor1 * baseColor_;

	return output;
}