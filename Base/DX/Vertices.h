#pragma once
#include <d3d12.h>
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "GPUResource.h"
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	// Sprite�p ���_�f�[�^�\����
	struct SpriteVData
	{
		Math::Vec3 pos_; // xyz���W
		Math::Vec2 uv_;	 // uv���W
	};
	// Model�p ���_�f�[�^�\����
	struct ModelVData
	{
		Math::Vec3 pos_;	 // xyz���W
		Math::Vec3 normal_;	 // �@���x�N�g��
		Math::Vec2 uv_;		 // uv���W
		Math::Vec3 tangent_; // �ڋ��
		Math::Vec4 color_;	 // ���_�F
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