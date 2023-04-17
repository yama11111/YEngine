#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")
namespace YDX
{
	class DescriptorHeap
	{
	private:

		// 不変 SRV 数
		static const UINT ImmutableSRVCount_ = 2056;

		// 不変 UAV 数
		static const UINT ImmutableUAVCount_ = 2056;

		// 不変 CBV 数
		static const UINT ImmutableCBVCount_ = 2056;


		// 最大 SRV 数
		static const UINT MaxSRVCount_ = 262144;

		// 最大 UAV 数
		static const UINT MaxUAVCount_ = 262144;

		// 最大 CBV 数
		static const UINT MaxCBVCount_ = 262144;

	public:

		// ハンドル (CPU, GPU)
		struct Handle
		{

			// CPU
			D3D12_CPU_DESCRIPTOR_HANDLE cpu_;

			// GPU
			D3D12_GPU_DESCRIPTOR_HANDLE gpu_;

		};

	private:

		// デスクリプター計数器
		struct DescriptorCounter
		{
		public:

			// SRV 数
			UINT srvCount_ = 0;

			// UAV 数
			UINT uavCount_ = 0;

			// CBV 数
			UINT cbvCount_ = 0;

			// 初期位置ハンドル
			Handle startHandle_{};

		public:

			/// <summary>
			/// カウント初期化
			/// </summary>
			void ResetCount() { srvCount_ = uavCount_ = cbvCount_ = 0; }

		};

	private:

		// デスクリプターヒープ
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_ = nullptr;

		// インクリメント用
		UINT incSize_ = 0;


		// 不変 (リセットしない)
		DescriptorCounter immutableCounter_;

		// 可変 (リセットする)
		DescriptorCounter mutableCounter_;

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 描画前コマンド (最初に一回)
		/// </summary>
		void SetDrawCommand();

	public:

		/// <summary>
		/// SRV 生成
		/// </summary>
		/// <param name="buff"> : バッファ</param>
		/// <param name="srvDesc"> : SRV 設定</param>
		/// <param name="isMutable"> : リセットするか</param>
		/// <returns>ハンドル (CPU, GPU)</returns>
		Handle CreateSRV(ID3D12Resource* buff, const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc, const bool isMutable);

		/// <summary>
		/// UAV 生成
		/// </summary>
		/// <param name="buff"> : バッファ</param>
		/// <param name="srvDesc"> : UAV 設定</param>
		/// <param name="isMutable"> : リセットするか</param>
		/// <returns>ハンドル (CPU, GPU)</returns>
		Handle CreateUAV(ID3D12Resource* buff, const D3D12_UNORDERED_ACCESS_VIEW_DESC& uavDesc, const bool isMutable);

		/// <summary>
		/// CBV 生成
		/// </summary>
		/// <param name="buff"> : バッファ</param>
		/// <param name="srvDesc"> : CBV 設定</param>
		/// <param name="isMutable"> : リセットするか</param>
		/// <returns>ハンドル (CPU, GPU)</returns>
		Handle CreateCBV(const D3D12_CONSTANT_BUFFER_VIEW_DESC& cbvDesc, const bool isMutable);

	public:

		/// <summary>
		/// SRV 追加
		/// </summary>
		/// <param name="isMutable"> : リセットするか</param>
		/// <returns>ハンドル (CPU, GPU)</returns>
		Handle AddSRV(const bool isMutable);

		/// <summary>
		/// UAV 追加
		/// </summary>
		/// <param name="isMutable"> : リセットするか</param>
		/// <returns>ハンドル (CPU, GPU)</returns>
		Handle AddUAV(const bool isMutable);

		/// <summary>
		/// CBV 追加
		/// </summary>
		/// <param name="isMutable"> : リセットするか</param>
		/// <returns>ハンドル (CPU, GPU)</returns>
		Handle AddCBV(const bool isMutable);

	public:

		/// <summary>
		/// 可変のデスクリプタカウントをクリア
		/// </summary>
		void ClearMutableCount() { mutableCounter_.ResetCount(); }

	public:

		/// <summary>
		/// ポインタ取得
		/// </summary>
		/// <returns>デスクリプターヒープのポインタ</returns>
		ID3D12DescriptorHeap* Get() { return descriptorHeap_.Get(); }

		/// <summary>
		/// カウント表示 (デバッグ時のみ)
		/// </summary>
		void ShowCount();

	private:

		// 静的デバイスポインタ
		static ID3D12Device* pDevice_;

		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* pCmdList_;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pDevice"> : デバイスポインタ</param>
		/// <param name="pCmdList"> : コマンドリストポインタ</param>
		static void StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCmdList);

	public:

		DescriptorHeap() = default;

		~DescriptorHeap() = default;
	};
}
