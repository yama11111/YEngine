#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	class GPUResource
	{

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="pHeapProp"> : �o�b�t�@�ݒ�|�C���^</param>
		/// <param name="pResourceDesc"> : ���\�[�X�ݒ�|�C���^</param>
		/// <param name="resourceState"> : ���\�[�X�X�e�[�g</param>
		/// <param name="pClearValue"> : �N���A�l�|�C���^</param>
		void Create(
			const D3D12_HEAP_PROPERTIES* pHeapProp,
			const D3D12_RESOURCE_DESC* pResourceDesc,
			const D3D12_RESOURCE_STATES resourceState = D3D12_RESOURCE_STATE_GENERIC_READ,
			const D3D12_CLEAR_VALUE* pClearValue = nullptr);

	public:

		/// <summary>
		/// �o�b�t�@�|�C���^�擾
		/// </summary>
		/// <returns>�o�b�t�@�|�C���^</returns>
		ID3D12Resource* Get() { return buffer_.Get(); }

		/// <summary>
		/// �o�b�t�@�|�C���^�|�C���^�擾
		/// </summary>
		/// <returns>�o�b�t�@�|�C���^�|�C���^</returns>
		ID3D12Resource** GetAddressOf() { return buffer_.GetAddressOf(); }

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pDevice"> : �f�o�C�X�|�C���^</param>
		static void StaticInitialize(ID3D12Device* pDevice);
	
	private:
		
		// �o�b�t�@
		Microsoft::WRL::ComPtr<ID3D12Resource> buffer_ = nullptr;

	private:
		
		// �ÓI�f�o�C�X�|�C���^
		static ID3D12Device* spDevice_;
	
	};
}