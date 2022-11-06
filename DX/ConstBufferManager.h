#pragma once
#include "GPUResource.h"
#include "Vec4.h"
#include "Mat4.h"

namespace DX
{
	// �萔�o�b�t�@�p�f�[�^�\���� (�}�e���A��)
	struct MaterialData
	{
		Math::Vec4 color_; // �F (RGBA)
	};
	// �萔�o�b�t�@�p�f�[�^�\���� (3D�ϊ��s��)
	struct TransformData
	{
		Math::Mat4 mat_; // 3D�ϊ��s��
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
		// �萔�o�b�t�@(�}�e���A��)�������ԍ��ۑ��p
		UINT rpIndexM_ = 0;
		// �萔�o�b�t�@(3D�ϊ��s��)�������ԍ��ۑ��p
		UINT rpIndexT_ = 0;
	public:
		// �萔�o�b�t�@(�}�e���A��)�̐��� + �}�b�s���O
		void CreateCB(ConstBuffer<MaterialData>& cb, const Math::Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
		// �萔�o�b�t�@(3D�ϊ��s��)�̐��� + �}�b�s���O
		void CreateCB(ConstBuffer<TransformData>& cb);
		// �`��O�R�}���h(�}�e���A��)
		void SetDrawCommand(ConstBuffer<MaterialData>& cb);
		// �`��O�R�}���h(3D�ϊ��s��)
		void SetDrawCommand(ConstBuffer<TransformData>& cb);
	public:
		// �萔�o�b�t�@(�}�e���A��)�ԍ��ݒ�
		void SetRootParameterIndexMaterial(UINT rpIndex) { rpIndexM_ = rpIndex; }
		// �萔�o�b�t�@(3D�ϊ��s��)�ԍ��ݒ�
		void SetRootParameterIndexTransform(UINT rpIndex) { rpIndexT_ = rpIndex; }
	private:
		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* pCmdList_;
	public:
		// �ÓI������
		static void StaticInitialize(ID3D12GraphicsCommandList* pCommandList);
	};
}