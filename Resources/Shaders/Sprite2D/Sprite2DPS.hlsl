#include "Sprite2D.hlsli"

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

PSOutput main(PSInput input)
{
	PSOutput output;

	// �e�N�X�`���}�b�s���O
	float4 texColor = tex.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;

	// �v�Z�����F�ŕ`��
	output.target_ = texColor * baseColor_;

	return output;
}