#include "Dissolve.hlsli"

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> mask : register(t1); // 1�ԃX���b�g�ɐݒ肳�ꂽ�}�X�N�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

PSOutput main(PSInput input)
{
	PSOutput output;

	// �e�N�X�`���}�b�s���O
	float4 texColor = tex.Sample(smp, input.uv * texTiling_ + texOffset_);
	
    clip(texColor.a - 0.1f);
    
    texColor *= texColorRate_;
	
	float4 maskColor = mask.Sample(smp, input.uv * texTiling_ + texOffset_);

	// (�ԐF�l - ����) < 0 �Ȃ�`��؂�
	clip(maskColor.r - time_);
	
	// �v�Z�����F�ŕ`��
	output.target = texColor * baseColor_;

	return output;
}