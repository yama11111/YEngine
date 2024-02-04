#include "Sprite3D.hlsli"

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

PSOutput main(PSInput input)
{
	PSOutput output;

	// �e�N�X�`���}�b�s���O
	float4 texColor = tex.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;

    float4 color = texColor * baseColor_;

    clip(color.a - 0.0001f);
	
	// �v�Z�����F�ŕ`��
	output.target_ = color;

	return output;
}