#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

// 臒l
static const float kThreshold = 1.0f;

PSOutput main(PSInput input)
{
    PSOutput output;
	
    // �e�N�X�`���}�b�s���O
    float4 texColor0 = tex0.Sample(smp, input.uv_ * texTiling_ + texOffset_) * texColorRate_;

    output.target_ = texColor0 * baseColor_;
    
    // �A���t�@�l�̊���
    // �}�[���^�̎���0�ɂȂ�
    float alphaRatio = 1.0f - (step(kThreshold, texColor0.r) * step(kThreshold, texColor0.b));
    
    output.target_.a *= alphaRatio;

    return output;
}