#pragma once
#include "GPUResource.h"
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	// 頂点
	template <typename T>
	class Vertices
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
		// 初期化
		void Initialize(const std::vector<T> v);
		// マップに転送
		void TransferMap(const std::vector<T> v);
		// 描画
		virtual void Draw();
	protected:
		// バッファとビュー作成
		void Create();
	protected:
		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* pCmdList_;
	public:
		// 静的初期化
		static void StaticInitialize(ID3D12GraphicsCommandList* pCommandList);
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
		// 初期化
		void Initialize(const std::vector<T> v, const std::vector<uint16_t> idx);
		// 描画
		void Draw() override;
	};
}