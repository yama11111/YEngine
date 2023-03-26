#pragma once
#include "Vertices.h"
#include "ShaderCommon.h"
#include "PipelineSet.h"
#include "TextureManager.h"
#include "Color.h"
#include "Vector2.h"
#include "Matrix4.h"
#include <memory>

namespace YGame
{
	// スプライト2D用オブジェクトコモンクラス
	class Sprite2DObjectCommon
	{
	protected:
		// 定数バッファデータ構造体
		struct CBData
		{
			YMath::Matrix4 matWorld_; // 3D変換行列
		};
	protected:
		// 静的射影変換行列(平行投影)
		static YMath::Matrix4 sProjection_;
		// 色 (デフォルト)
		static std::unique_ptr<Color> sDefColor_;
	public:
		// 静的初期化 (デフォルト値設定)
		static void StaticInitialize();
	};
	
	// スプライト2Dコモンクラス
	class Sprite2DCommon
	{
	public:
		// 頂点データ構造体
		struct VData
		{
			YMath::Vector3 pos_; // xyz座標
			YMath::Vector2 uv_;  // uv座標
		};
	public:
		// ルートパラメータ番号
		enum class RootParameterIndex
		{
			TransformCB	 = 0, // 行列
			ColorCB		 = 1, // 色
			TexDT		 = 2, // テクスチャ
		};
	private:
		// シェーダーセット
		class ShaderSet : public YDX::ShaderCommon
		{
		public:
			// 頂点シェーダオブジェクト
			Microsoft::WRL::ComPtr<ID3DBlob> vsBlob_ = nullptr;
			// ピクセルシェーダオブジェクト
			Microsoft::WRL::ComPtr<ID3DBlob> psBlob_ = nullptr;
		public:
			// シェーダーファイル読み込み
			void Load(ID3DBlob* errorBlob);
		};
		// パイプライン設定構造体
		struct PipelineSetStatus : public YDX::PipelineSet::IStatus
		{
			// 初期化
			void Initialize(ID3DBlob* errorBlob_) override;
		};
	protected:
		// パイプライン設定
		static YDX::PipelineSet sPipelineSet_;
		// 静的テクスチャマネージャーポインタ
		static TextureManager* spTexManager_;
	public:
		// 静的初期化
		static void StaticInitialize();
		// 静的描画コマンド
		static void StaticSetDrawCommand();
	};
}
