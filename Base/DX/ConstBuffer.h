#pragma once
#include "GPUResource.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"

namespace DX
{
	// �萔�o�b�t�@�p�f�[�^�\���� (3D�ϊ��s��)
	struct TransformCBData
	{
		Math::Mat4 mat_; // 3D�ϊ��s��
	};
	// �萔�o�b�t�@�p�f�[�^�\���� (�F)
	struct ColorCBData
	{
		Math::Vec4 color_; // �F (RGBA)
	};
	// �萔�o�b�t�@�p�f�[�^�\���� (�}�e���A��)
	struct MaterialCBData
	{
		Math::Vec3 ambient_;  // �A���r�G���g�W��
		float pad1_; // �p�f�B���O1
		Math::Vec3 diffuse_;  // �f�B�t���[�Y�W��
		float pad2_; // �p�f�B���O2
		Math::Vec3 specular_; // �X�y�L�����[�W��
		float alpha_;		  // �A���t�@
	};

	template <typename T>
	class ConstBuffer
	{
	public:
		// �}�b�s���O�p
		T* map_ = nullptr;
	private:
		// �o�b�t�@
		GPUResource rsc_;
	public:
		// �萔�o�b�t�@�̐��� + �}�b�s���O
		void Create();
		// �`��O�R�}���h
		void SetDrawCommand();
	private:
		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* pCmdList_;
		// �ÓI�萔�o�b�t�@�������ԍ��ۑ��p
		static UINT rpIndex_;
	public:
		// �ÓI������
		static void StaticInitialize(ID3D12GraphicsCommandList* pCommandList);
		// �ÓI�萔�o�b�t�@�ԍ��ݒ�
		static void SetRootParameterIndex(UINT rpIndex) { rpIndex_ = rpIndex; }
	};
}