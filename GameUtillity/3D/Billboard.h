#pragma once
#include "Vertices.h"
#include "PipelineSet.h"
#include "Object.h"
#include "ViewProjection.h"
#include "TextureManager.h"

namespace YGame
{
	class Billboard
	{
	public:
		// 頂点データ
		struct VData
		{
			YMath::Vec3 pos_; // xyz座標
		};
	private:
		// 頂点データ
		YDX::Vertices<VData> vt_;
		// Y軸ビルボード
		bool isAxisY_ = false;
		
		// 非表示
		bool isInvisible_ = false;

		// 定数バッファ(ビルボード)
		YDX::ConstBuffer<YDX::BillboardCBData> cbBlbd_;
	public:
		// 生成
		static Billboard* Create(const bool isYAxisBillboard);
	public:
		// 描画
		void Draw(Object& obj, const ViewProjection& vp, const UINT tex);
	private:
		// コンストラクタ
		Billboard() = default;
	private:
		// パイプライン設定
		static YDX::PipelineSet pplnSet_;
		// 静的テクスチャマネージャーポインタ
		static TextureManager* pTexManager_;
	public:
		// 静的初期化
		static void StaticInitialize(TextureManager* pTexManager, std::vector<D3D12_ROOT_PARAMETER>* rootParams);
		// 静的描画コマンド
		static void StaticSetDrawCommand();
	};
}
