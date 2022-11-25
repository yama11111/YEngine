#pragma once
#include <d3d12.h>
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace DX 
{
	class RootParameterManager
	{
	private:
		// ���[�g�p�����[�^�[�pvector�z��
		std::vector<D3D12_ROOT_PARAMETER> rps_;
		// CBV�J�E���g�p
		UINT cbvIndex_ = 0;
		// �f�X�N���v�^�����W�̐ݒ�
		D3D12_DESCRIPTOR_RANGE descriptorRange_{};
	public:
		// �萔�o�b�t�@�}�� (�߂�l : ���[�g�p�����[�^�ԍ�)
		UINT PushBackCBV();
		// �e�N�X�`�����W�X�^�}�� (�߂�l : ���[�g�p�����[�^�ԍ�)
		UINT PushBackTR();
		// �f�X�N���v�^�[�q�[�v�}�� (�߂�l : ���[�g�p�����[�^�ԍ�)
		UINT PushBackDescriptorTable(const D3D12_DESCRIPTOR_RANGE& descriptorRange);
	public:
		// ���[�g�p�����[�^�[
		std::vector<D3D12_ROOT_PARAMETER>* Get() { return &rps_; }
	};
}
