#pragma once
#include "Transform.h"
#include "Vertices.h"
#include "PipelineSet.h"
#include "TextureManager.h"

namespace Object
{
	class Sprite
	{
	public:
		// サイズ
		const Math::Vec2 size_;
	private:
		// 頂点データ
		DX::Vertices<DX::SpriteVData> vt_;
	public:
		// コンストラクタ
		Sprite(const Math::Vec2& size);
		// 描画
		void Draw(Transform& trfm, const UINT tex);
	private:
		// 静的射影変換行列(平行投影)
		static Math::Mat4 projection_;
		// パイプライン設定
		static DX::PipelineSet pplnSet_;
		// 静的テクスチャマネージャーポインタ
		static DX::TextureManager* pTexManager_;
	public:
		// 静的初期化
		static void StaticInitialize(DX::TextureManager* pTexManager, std::vector<D3D12_ROOT_PARAMETER>* rootParams);
		// 静的描画コマンド
		static void StaticSetDrawCommand();
	};
}
