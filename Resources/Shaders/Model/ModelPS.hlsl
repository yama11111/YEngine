#include "Model.hlsli"

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

PSOutput main(PSInput input)
{
    PSOutput output;

	// �e�N�X�`���}�b�s���O
    float4 texColor = tex.Sample(smp, input.uv * texTiling_ + texOffset_);
    
    clip(texColor.a - 0.1f);
    
    texColor.rgb *= texColorRate_.rgb;
	
    // �F
    float4 color = texColor * baseColor_;

    output.target = color;

    return output;
}