#pragma once
#include <d3d12.h>
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "GPUResource.h"
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	// Sprite�p ���_�f�[�^�\����
	struct SpriteVData
	{
		YMath::Vec3 pos_; // xyz���W
		YMath::Vec2 uv_;	 // uv���W
	};
	// Model�p ���_�f�[�^�\����
	struct ModelVData
	{
		YMath::Vec3 pos_;	 // xyz���W
		YMath::Vec3 normal_;	 // �@���x�N�g��
		YMath::Vec2 uv_;		 // uv���W
		YMath::Vec3 tangent_; // �ڋ��
		YMath::Vec4 color_;	 // ���_�F
	};
	// Billboard�p ���_�f�[�^
	struct BillboardVData 
	{
		YMath::Vec3 pos_; // xyz���W
	};

	template <typename T>
	class Vertices // ���_
	{
	protected:
		// ���_�f�[�^
		std::vector<T> v_;
		// ���_�o�b�t�@
		GPUResource buffer_{};
		// ���_�o�b�t�@�r���[
		D3D12_VERTEX_BUFFER_VIEW view_{};
		// ���z������
		T* vertMap_ = nullptr;
	public:
		// ������
		void Initialize(const std::vector<T> v);
		// �}�b�v�ɓ]��
		void TransferMap(const std::vector<T> v);
		// �`��
		virtual void Draw();
	protected:
		// �o�b�t�@�ƃr���[�쐬
		void Create();
	protected:
		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* pCmdList_;
	public:
		// �ÓI������
		static void StaticInitialize(ID3D12GraphicsCommandList* pCommandList);
	};

	// ���_�C���f�b�N�X
	class VertexIndex3D : public Vertices<ModelVData> 
	{
	private:
		// �C���f�b�N�X�f�[�^
		std::vector<uint16_t> idx_;
		// �C���f�b�N�X�o�b�t�@
		GPUResource idxBuffer_{};
		// �C���f�b�N�X�o�b�t�@�r���[
		D3D12_INDEX_BUFFER_VIEW idxView_{};
	public:
		// ������
		void Initialize(const std::vector<ModelVData> v, const std::vector<uint16_t> idx, const bool normalized);
		// �`��
		void Draw() override;
	private:
		// �@���v�Z
		void Normalized();
	};
}