#pragma once
#include "ShaderCommon.h"
#include "PipelineSet.h"
#include "TextureManager.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Mat4.h"
#include <memory>

namespace YGame
{
	class Sprite2DCommon
	{
	public:
		// 頂点データ構造体
		struct VData
		{
			YMath::Vec3 pos_; // xyz座標
			YMath::Vec2 uv_;  // uv座標
		};
		// 定数バッファデータ構造体
		struct CBData
		{
			YMath::Mat4 matWorld_; // 3D変換行列
		};
	public:
		// ルートパラメータ番号
		enum class RootParameterIndex
		{
			SpriteCB = 0,
			ColorCB = 1,
			TexDT = 2,
		};
	protected:
		// 静的射影変換行列(平行投影)
		static YMath::Mat4 projection_;
		// パイプライン設定
		static YDX::PipelineSet pipelineSet_;
		// 静的テクスチャマネージャーポインタ
		static TextureManager* pTexManager_;
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
			void Initialize(ID3DBlob* errorBlob_) override;
		};
	public:
		// 静的初期化ステータス
		struct StaticInitStatus
		{
			// テクスチャマネージャーポインタ
			TextureManager* pTexManager_;
		};
	public:
		// 静的初期化
		static void StaticInitialize(const StaticInitStatus& state);
		// 静的描画コマンド
		static void StaticSetDrawCommand();
	};
}
