#pragma once
#include "GPUResource.h"
#include "DescriptorHeap.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"

namespace YDX
{
	// 定数バッファデータ構造体 (3D変換行列)
	struct TransformCBData
	{
		YMath::Mat4 mat_; // 3D変換行列
	};
	// 定数バッファデータ構造体 (色)
	struct ColorCBData
	{
		YMath::Vec4 color_; // 色 (RGBA)
	};
	// 定数バッファデータ構造体 (マテリアル)
	struct MaterialCBData
	{
		YMath::Vec3 ambient_;  // アンビエント係数
		float pad1_; // パディング1
		YMath::Vec3 diffuse_;  // ディフューズ係数
		float pad2_; // パディング2
		YMath::Vec3 specular_; // スペキュラー係数
		float alpha_;		   // アルファ
	};
	// 定数バッファデータ構造体 (ビルボード)
	struct BillboardCBData
	{
		YMath::Mat4 matBlbd_; // ビルボード行列
	};

	// 定数バッファコモンクラス
	class ConstBufferCommon 
	{
	protected:
		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* pCmdList_;
		// 静的デスクリプターヒープクラス
		static DescriptorHeap* pDescHeap_;
	public:
		// 静的初期化設定
		struct StaticInitStatus
		{
			ID3D12GraphicsCommandList* pCmdList_;
			DescriptorHeap* pDescHeap_;
		};
	public:
		// 静的初期化
		static void StaticInitialize(const StaticInitStatus& state);
	};

	// 定数バッファ
	template <typename T>
	class ConstBuffer : private ConstBufferCommon
	{
	public:
		// マッピング用
		T* map_ = nullptr;
	private:
		// バッファ
		GPUResource rsc_;
		// CBV設定
		D3D12_CONSTANT_BUFFER_VIEW_DESC viewDesc_{};
	public:
		// 定数バッファの生成 + マッピング
		void Create();
		// 描画前コマンド
		void SetDrawCommand();
	private:
		// 静的定数バッファ番号
		static UINT rpIndex_;
	public:
		// 静的定数バッファ番号設定
		static void StaticSetRootParamIndex(const UINT rpIndex);
	};
}