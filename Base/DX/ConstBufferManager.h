#pragma once
#include "GPUResource.h"
#include "Material.h"
#include "Vec4.h"
#include "Mat4.h"

namespace DX
{
	// �萔�o�b�t�@�p�f�[�^�\���� (3D�ϊ��s��)
	struct TransformData
	{
		Math::Mat4 mat_; // 3D�ϊ��s��
	};
	// �萔�o�b�t�@�p�f�[�^�\���� (�}�e���A��1)
	struct MaterialData1
	{
		Math::Vec4 color_; // �F (RGBA)
	};
	// �萔�o�b�t�@�p�f�[�^�\���� (�}�e���A��2)
	struct MaterialData2
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
		// �o�b�t�@
		GPUResource rsc_;
		// �}�b�s���O�p
		T* map_ = nullptr;
	};

	class ConstBufferManager
	{
	private:
		// �萔�o�b�t�@(3D�ϊ��s��)�������ԍ��ۑ��p
		UINT rpIndexT_ = 0;
		// �萔�o�b�t�@(�}�e���A��1)�������ԍ��ۑ��p
		UINT rpIndexM1_ = 0;
		// �萔�o�b�t�@(�}�e���A��2)�������ԍ��ۑ��p
		UINT rpIndexM2_ = 0;
	public:
		// �萔�o�b�t�@(3D�ϊ��s��)�̐��� + �}�b�s���O
		void CreateCB(ConstBuffer<TransformData>& cb);
		// �萔�o�b�t�@(�}�e���A��1)�̐��� + �}�b�s���O
		void CreateCB(ConstBuffer<MaterialData1>& cb, const Math::Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
		// �萔�o�b�t�@(�}�e���A��2)�̐��� + �}�b�s���O
		void CreateCB(ConstBuffer<MaterialData2>& cb, const Game::Material& material);
		// �`��O�R�}���h(3D�ϊ��s��)
		void SetDrawCommand(ConstBuffer<TransformData>& cb);
		// �`��O�R�}���h(�}�e���A��1)
		void SetDrawCommand(ConstBuffer<MaterialData1>& cb);
		// �`��O�R�}���h(�}�e���A��2)
		void SetDrawCommand(ConstBuffer<MaterialData2>& cb);
	public:
		// �萔�o�b�t�@(3D�ϊ��s��)�ԍ��ݒ�
		void SetRootParameterIndexTransform(UINT rpIndex) { rpIndexT_ = rpIndex; }
		// �萔�o�b�t�@(�}�e���A��1)�ԍ��ݒ�
		void SetRootParameterIndexMaterial1(UINT rpIndex) { rpIndexM1_ = rpIndex; }
		// �萔�o�b�t�@(�}�e���A��2)�ԍ��ݒ�
		void SetRootParameterIndexMaterial2(UINT rpIndex) { rpIndexM2_ = rpIndex; }
	private:
		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* pCmdList_;
	public:
		// �ÓI������
		static void StaticInitialize(ID3D12GraphicsCommandList* pCommandList);
	};
}