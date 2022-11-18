#pragma once
#include "GPUResource.h"
#include "Material.h"
#include "Vec4.h"
#include "Mat4.h"

namespace DX
{
	// 定数バッファ用データ構造体 (3D変換行列)
	struct TransformData
	{
		Math::Mat4 mat_; // 3D変換行列
	};
	// 定数バッファ用データ構造体 (マテリアル1)
	struct MaterialData1
	{
		Math::Vec4 color_; // 色 (RGBA)
	};
	// 定数バッファ用データ構造体 (マテリアル2)
	struct MaterialData2
	{
		Math::Vec3 ambient_;  // アンビエント係数
		float pad1_; // パディング1
		Math::Vec3 diffuse_;  // ディフューズ係数
		float pad2_; // パディング2
		Math::Vec3 specular_; // スペキュラー係数
		float alpha_;		  // アルファ
	};

	template <typename T>
	class ConstBuffer
	{
	public:
		// バッファ
		GPUResource rsc_;
		// マッピング用
		T* map_ = nullptr;
	};

	class ConstBufferManager
	{
	private:
		// 定数バッファ(3D変換行列)生成時番号保存用
		UINT rpIndexT_ = 0;
		// 定数バッファ(マテリアル1)生成時番号保存用
		UINT rpIndexM1_ = 0;
		// 定数バッファ(マテリアル2)生成時番号保存用
		UINT rpIndexM2_ = 0;
	public:
		// 定数バッファ(3D変換行列)の生成 + マッピング
		void CreateCB(ConstBuffer<TransformData>& cb);
		// 定数バッファ(マテリアル1)の生成 + マッピング
		void CreateCB(ConstBuffer<MaterialData1>& cb, const Math::Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
		// 定数バッファ(マテリアル2)の生成 + マッピング
		void CreateCB(ConstBuffer<MaterialData2>& cb, const Game::Material& material);
		// 描画前コマンド(3D変換行列)
		void SetDrawCommand(ConstBuffer<TransformData>& cb);
		// 描画前コマンド(マテリアル1)
		void SetDrawCommand(ConstBuffer<MaterialData1>& cb);
		// 描画前コマンド(マテリアル2)
		void SetDrawCommand(ConstBuffer<MaterialData2>& cb);
	public:
		// 定数バッファ(3D変換行列)番号設定
		void SetRootParameterIndexTransform(UINT rpIndex) { rpIndexT_ = rpIndex; }
		// 定数バッファ(マテリアル1)番号設定
		void SetRootParameterIndexMaterial1(UINT rpIndex) { rpIndexM1_ = rpIndex; }
		// 定数バッファ(マテリアル2)番号設定
		void SetRootParameterIndexMaterial2(UINT rpIndex) { rpIndexM2_ = rpIndex; }
	private:
		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* pCmdList_;
	public:
		// 静的初期化
		static void StaticInitialize(ID3D12GraphicsCommandList* pCommandList);
	};
}