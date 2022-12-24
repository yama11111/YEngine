#pragma once
#include "GPUResource.h"
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

	template <typename T>
	class ConstBuffer
	{
	public:
		// マッピング用
		T* map_ = nullptr;
	private:
		// バッファ
		GPUResource rsc_;
	public:
		// 定数バッファの生成 + マッピング
		void Create();
		// 描画前コマンド
		void SetDrawCommand();
	private:
		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* pCmdList_;
		// 静的定数バッファ生成時番号保存用
		static UINT rpIndex_;
	public:
		// 静的初期化
		static void StaticInitialize(ID3D12GraphicsCommandList* pCommandList);
		// 静的定数バッファ番号設定
		static void SetRootParameterIndex(UINT rpIndex) { rpIndex_ = rpIndex; }
	};
}