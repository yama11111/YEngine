#pragma once
#include "GPUResource.h"
#include <vector>

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
	template <typename VData>
	class Vertices : protected VertexCommon
	{

	protected:

		// ���_�f�[�^
		std::vector<VData> v_;

		// ���_�o�b�t�@
		GPUResource buffer_{};

		// ���_�o�b�t�@�r���[
		D3D12_VERTEX_BUFFER_VIEW view_{};

		// ���z������
		VData* vertMap_ = nullptr;

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="v"> : ���_�z��</param>
		void Initialize(const std::vector<VData>& v);

		/// <summary>
		/// �}�b�v�ɓ]��
		/// </summary>
		/// <param name="v"> : ���_�z��</param>
		void TransferMap(const std::vector<VData>& v);

		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw() const;

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
	template <typename VData>
	class VertexIndex : public Vertices<VData>
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
		void Initialize(const std::vector<VData>& v, const std::vector<uint16_t>& idx);

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() const override;

	public:

		VertexIndex() = default;

		~VertexIndex() = default;

	};
}