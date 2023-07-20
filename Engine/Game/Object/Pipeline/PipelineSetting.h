#pragma once
#include <d3d12.h>
#include <vector>

namespace YGame
{
	struct PipelineSetting
	{
		// ���_���C�A�E�g
		std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;
		
		// �e�N�X�`���T���v���[
		std::vector<D3D12_STATIC_SAMPLER_DESC> samplerDescs;
		
		// �|���S���̓h���
		D3D12_FILL_MODE fillMode = D3D12_FILL_MODE_SOLID;
		
		// �J�����O�ݒ�
		D3D12_CULL_MODE cullMode;
		
		// �[�x�e�X�g���s����
		bool depthEnable;

		// �`��ݒ�
		D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType;

		// �`��
		D3D_PRIMITIVE_TOPOLOGY primitive;
	};
}

