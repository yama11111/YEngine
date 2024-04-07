#include "DiscardColor.hlsli"

Texture2D<float4> tex0 : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

PSOutput main(PSInput input)
{
    PSOutput output;
	
    // �e�N�X�`���}�b�s���O
    float4 texColor0 = tex0.Sample(smp, input.uv_);
    
    output.target_ = texColor0;
    output.target_.a = 1.0f;
    
    // �����F�Ɠ����F�Ȃ�`��e��
    // �F�̃x�N�g���̍��̒�����0�Ȃ瓯���F
    float dis = distance(output.target_.rgb, discardColor_);
    clip(dis - threshold_);
    
    //step(output.target_.rgb, discardColor_);
    
    return output;
}