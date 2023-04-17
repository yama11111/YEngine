#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")
namespace YDX
{
	class DescriptorHeap
	{
	private:

		// �s�� SRV ��
		static const UINT ImmutableSRVCount_ = 2056;

		// �s�� UAV ��
		static const UINT ImmutableUAVCount_ = 2056;

		// �s�� CBV ��
		static const UINT ImmutableCBVCount_ = 2056;


		// �ő� SRV ��
		static const UINT MaxSRVCount_ = 262144;

		// �ő� UAV ��
		static const UINT MaxUAVCount_ = 262144;

		// �ő� CBV ��
		static const UINT MaxCBVCount_ = 262144;

	public:

		// �n���h�� (CPU, GPU)
		struct Handle
		{

			// CPU
			D3D12_CPU_DESCRIPTOR_HANDLE cpu_;

			// GPU
			D3D12_GPU_DESCRIPTOR_HANDLE gpu_;

		};

	private:

		// �f�X�N���v�^�[�v����
		struct DescriptorCounter
		{
		public:

			// SRV ��
			UINT srvCount_ = 0;

			// UAV ��
			UINT uavCount_ = 0;

			// CBV ��
			UINT cbvCount_ = 0;

			// �����ʒu�n���h��
			Handle startHandle_{};

		public:

			/// <summary>
			/// �J�E���g������
			/// </summary>
			void ResetCount() { srvCount_ = uavCount_ = cbvCount_ = 0; }

		};

	private:

		// �f�X�N���v�^�[�q�[�v
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_ = nullptr;

		// �C���N�������g�p
		UINT incSize_ = 0;


		// �s�� (���Z�b�g���Ȃ�)
		DescriptorCounter immutableCounter_;

		// �� (���Z�b�g����)
		DescriptorCounter mutableCounter_;

	public:

		/// <summary>
		/// ������
		/// </summary>
		void Initialize();

		/// <summary>
		/// �`��O�R�}���h (�ŏ��Ɉ��)
		/// </summary>
		void SetDrawCommand();

	public:

		/// <summary>
		/// SRV ����
		/// </summary>
		/// <param name="buff"> : �o�b�t�@</param>
		/// <param name="srvDesc"> : SRV �ݒ�</param>
		/// <param name="isMutable"> : ���Z�b�g���邩</param>
		/// <returns>�n���h�� (CPU, GPU)</returns>
		Handle CreateSRV(ID3D12Resource* buff, const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc, const bool isMutable);

		/// <summary>
		/// UAV ����
		/// </summary>
		/// <param name="buff"> : �o�b�t�@</param>
		/// <param name="srvDesc"> : UAV �ݒ�</param>
		/// <param name="isMutable"> : ���Z�b�g���邩</param>
		/// <returns>�n���h�� (CPU, GPU)</returns>
		Handle CreateUAV(ID3D12Resource* buff, const D3D12_UNORDERED_ACCESS_VIEW_DESC& uavDesc, const bool isMutable);

		/// <summary>
		/// CBV ����
		/// </summary>
		/// <param name="buff"> : �o�b�t�@</param>
		/// <param name="srvDesc"> : CBV �ݒ�</param>
		/// <param name="isMutable"> : ���Z�b�g���邩</param>
		/// <returns>�n���h�� (CPU, GPU)</returns>
		Handle CreateCBV(const D3D12_CONSTANT_BUFFER_VIEW_DESC& cbvDesc, const bool isMutable);

	public:

		/// <summary>
		/// SRV �ǉ�
		/// </summary>
		/// <param name="isMutable"> : ���Z�b�g���邩</param>
		/// <returns>�n���h�� (CPU, GPU)</returns>
		Handle AddSRV(const bool isMutable);

		/// <summary>
		/// UAV �ǉ�
		/// </summary>
		/// <param name="isMutable"> : ���Z�b�g���邩</param>
		/// <returns>�n���h�� (CPU, GPU)</returns>
		Handle AddUAV(const bool isMutable);

		/// <summary>
		/// CBV �ǉ�
		/// </summary>
		/// <param name="isMutable"> : ���Z�b�g���邩</param>
		/// <returns>�n���h�� (CPU, GPU)</returns>
		Handle AddCBV(const bool isMutable);

	public:

		/// <summary>
		/// �ς̃f�X�N���v�^�J�E���g���N���A
		/// </summary>
		void ClearMutableCount() { mutableCounter_.ResetCount(); }

	public:

		/// <summary>
		/// �|�C���^�擾
		/// </summary>
		/// <returns>�f�X�N���v�^�[�q�[�v�̃|�C���^</returns>
		ID3D12DescriptorHeap* Get() { return descriptorHeap_.Get(); }

		/// <summary>
		/// �J�E���g�\�� (�f�o�b�O���̂�)
		/// </summary>
		void ShowCount();

	private:

		// �ÓI�f�o�C�X�|�C���^
		static ID3D12Device* pDevice_;

		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* pCmdList_;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pDevice"> : �f�o�C�X�|�C���^</param>
		/// <param name="pCmdList"> : �R�}���h���X�g�|�C���^</param>
		static void StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCmdList);

	public:

		DescriptorHeap() = default;

		~DescriptorHeap() = default;
	};
}
