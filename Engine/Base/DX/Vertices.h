#pragma once
#include "GPUResource.h"
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	// 頂点コモンクラス
	class VertexCommon
	{

	protected:

		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* spCmdList_;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pCommandList"> : コマンドリストポインタ</param>
		static void StaticInitialize(ID3D12GraphicsCommandList* pCommandList);
	};


	// 頂点
	template <typename T>
	class Vertices : protected VertexCommon
	{

	protected:

		// 頂点データ
		std::vector<T> v_;

		// 頂点バッファ
		GPUResource buffer_{};

		// 頂点バッファビュー
		D3D12_VERTEX_BUFFER_VIEW view_{};

		// 仮想メモリ
		T* vertMap_ = nullptr;

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="v"> : 頂点配列</param>
		void Initialize(const std::vector<T> v);

		/// <summary>
		/// マップに転送
		/// </summary>
		/// <param name="v"> : 頂点配列</param>
		void TransferMap(const std::vector<T> v);

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw();

	protected:

		/// <summary>
		/// バッファとビュー作成
		/// </summary>
		void Create();

	public:

		Vertices() = default;

		virtual ~Vertices() = default;

	};


	// 頂点インデックス
	template <typename T>
	class VertexIndex : public Vertices<T>
	{

	private:

		// インデックスデータ
		std::vector<uint16_t> idx_;

		// インデックスバッファ
		GPUResource idxBuffer_{};

		// インデックスバッファビュー
		D3D12_INDEX_BUFFER_VIEW idxView_{};

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="v"> : 頂点配列</param>
		/// <param name="idx"> : インデックス配列</param>
		void Initialize(const std::vector<T> v, const std::vector<uint16_t> idx);

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

	public:

		VertexIndex() = default;

		~VertexIndex() = default;

	};
}