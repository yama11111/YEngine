#pragma once
#include "GPUResource.h"
#include "DescriptorHeap.h"

namespace YDX
{
	// �萔�o�b�t�@�R�����N���X
	class ConstBufferCommon 
	{
	protected:
		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* pCommandList_;
		// �ÓI�f�X�N���v�^�[�q�[�v�N���X
		static DescriptorHeap* pDescHeap_;
	public:
		// �ÓI�������ݒ�
		struct StaticInitStatus
		{
			ID3D12GraphicsCommandList* pCommandList_;
			DescriptorHeap* pDescHeap_;
		};
	public:
		// �ÓI������
		static void StaticInitialize(const StaticInitStatus& state);
	};

	// �萔�o�b�t�@
	template <typename T>
	class ConstBuffer : private ConstBufferCommon
	{
	public:
		// �}�b�s���O�p
		T* map_ = nullptr;
	private:
		// �o�b�t�@
		GPUResource rsc_;
		// CBV�ݒ�
		D3D12_CONSTANT_BUFFER_VIEW_DESC viewDesc_{};
	public:
		// �萔�o�b�t�@�̐��� + �}�b�s���O
		void Create();
		// �`��O�R�}���h
		void SetDrawCommand(const UINT rootParamIndex);
	};
}