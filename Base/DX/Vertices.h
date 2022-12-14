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
	// Sprite用 頂点データ構造体
	struct SpriteVData
	{
		Math::Vec3 pos_; // xyz座標
		Math::Vec2 uv_;	 // uv座標
	};
	// Model用 頂点データ構造体
	struct ModelVData
	{
		Math::Vec3 pos_;	 // xyz座標
		Math::Vec3 normal_;	 // 法線ベクトル
		Math::Vec2 uv_;		 // uv座標
		Math::Vec3 tangent_; // 接空間
		Math::Vec4 color_;	 // 頂点色
	};

	template <typename T>
	class Vertices // 頂点
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
	class VertexIndex3D : public Vertices<ModelVData> 
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
		void Initialize(const std::vector<ModelVData> v, const std::vector<uint16_t> idx, const bool normalized);
		// 描画
		void Draw() override;
	private:
		// 法線計算
		void Normalized();
	};
}