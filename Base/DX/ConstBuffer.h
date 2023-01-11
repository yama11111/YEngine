#pragma once
#include "GPUResource.h"
#include "DescriptorHeap.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"

namespace YDX
{
	// �萔�o�b�t�@�f�[�^�\���� (3D�ϊ��s��)
	struct TransformCBData
	{
		YMath::Mat4 mat_; // 3D�ϊ��s��
	};
	// �萔�o�b�t�@�f�[�^�\���� (�F)
	struct ColorCBData
	{
		YMath::Vec4 color_; // �F (RGBA)
	};
	// �萔�o�b�t�@�f�[�^�\���� (�}�e���A��)
	struct MaterialCBData
	{
		YMath::Vec3 ambient_;  // �A���r�G���g�W��
		float pad1_; // �p�f�B���O1
		YMath::Vec3 diffuse_;  // �f�B�t���[�Y�W��
		float pad2_; // �p�f�B���O2
		YMath::Vec3 specular_; // �X�y�L�����[�W��
		float alpha_;		   // �A���t�@
	};
	// �萔�o�b�t�@�f�[�^�\���� (�r���{�[�h)
	struct BillboardCBData
	{
		YMath::Mat4 matBlbd_; // �r���{�[�h�s��
	};

	// �萔�o�b�t�@�R�����N���X
	class ConstBufferCommon 
	{
	protected:
		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* pCmdList_;
		// �ÓI�f�X�N���v�^�[�q�[�v�N���X
		static DescriptorHeap* pDescHeap_;
	public:
		// �ÓI�������ݒ�
		struct StaticInitStatus
		{
			ID3D12GraphicsCommandList* pCmdList_;
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
		void SetDrawCommand();
	private:
		// �ÓI�萔�o�b�t�@�ԍ�
		static UINT rpIndex_;
	public:
		// �ÓI�萔�o�b�t�@�ԍ��ݒ�
		static void StaticSetRootParamIndex(const UINT rpIndex);
	};
}