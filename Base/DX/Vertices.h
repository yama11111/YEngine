#pragma once
#include "GPUResource.h"
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	// ���_
	template <typename T>
	class Vertices
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
	public:
		Vertices() = default;
		virtual ~Vertices() = default;
	};

	// ���_�C���f�b�N�X
	template <typename T>
	class VertexIndex : public Vertices<T>
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
		void Initialize(const std::vector<T> v, const std::vector<uint16_t> idx);
		// �`��
		void Draw() override;
	public:
		VertexIndex() = default;
		~VertexIndex() = default;
	};
}