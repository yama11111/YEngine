#pragma once
#include "GPUResource.h"
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	// ���_�R�����N���X
	class VertexCommon
	{

	protected:

		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* spCmdList_;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pCommandList"> : �R�}���h���X�g�|�C���^</param>
		static void StaticInitialize(ID3D12GraphicsCommandList* pCommandList);
	};


	// ���_
	template <typename T>
	class Vertices : protected VertexCommon
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

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="v"> : ���_�z��</param>
		void Initialize(const std::vector<T> v);

		/// <summary>
		/// �}�b�v�ɓ]��
		/// </summary>
		/// <param name="v"> : ���_�z��</param>
		void TransferMap(const std::vector<T> v);

		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw();

	protected:

		/// <summary>
		/// �o�b�t�@�ƃr���[�쐬
		/// </summary>
		void Create();

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

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="v"> : ���_�z��</param>
		/// <param name="idx"> : �C���f�b�N�X�z��</param>
		void Initialize(const std::vector<T> v, const std::vector<uint16_t> idx);

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

	public:

		VertexIndex() = default;

		~VertexIndex() = default;

	};
}