#pragma once
#include "ShaderCommon.h"
#include "PipelineSet.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"
#include <memory>

namespace YGame
{
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
		// 定数バッファデータ構造体
		struct CBData
		{
			YMath::Matrix4 matWorld_; // 3D変換行列
		};
	public:
		// ルートパラメータ番号
		enum class RootParameterIndex
		{
			ObjCB	 = 0, // 行列
			ColorCB	 = 1, // 色
			TexDT	 = 2, // テクスチャ
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
		// 静的射影変換行列(平行投影)
		static YMath::Matrix4 projection_;
		// パイプライン設定
		static YDX::PipelineSet pipelineSet_;
		// 静的テクスチャマネージャーポインタ
		static TextureManager* pTexManager_;
	public:
		// 静的初期化
		static void StaticInitialize();
		// 静的描画コマンド
		static void StaticSetDrawCommand();
	};
}
