#pragma once
#include "GPUResource.h"
#include <vector>

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
	template <typename VData>
	class Vertices : protected VertexCommon
	{

	protected:

		// 頂点データ
		std::vector<VData> v_;

		// 頂点バッファ
		GPUResource buffer_{};

		// 頂点バッファビュー
		D3D12_VERTEX_BUFFER_VIEW view_{};

		// 仮想メモリ
		VData* vertMap_ = nullptr;

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="v"> : 頂点配列</param>
		void Initialize(const std::vector<VData>& v);

		/// <summary>
		/// マップに転送
		/// </summary>
		/// <param name="v"> : 頂点配列</param>
		void TransferMap(const std::vector<VData>& v);

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw() const;

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
	template <typename VData>
	class VertexIndex : public Vertices<VData>
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
		void Initialize(const std::vector<VData>& v, const std::vector<uint16_t>& idx);

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() const override;

	public:

		VertexIndex() = default;

		~VertexIndex() = default;

	};
}