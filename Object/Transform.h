#pragma once
#include "ConstBufferManager.h"
#include "MatWorld.h"

namespace Object
{
	class Transform
	{
	private:
		// 転送用行列
		Math::MatWorld mw_;
		// 定数バッファ(マテリアル)
		DX::ConstBuffer<DX::MaterialData> cbMtrl_;
		// 定数バッファ(3D変換行列)
		DX::ConstBuffer<DX::TransformData> cbTrfm_;
		// 親行列
		Math::MatWorld* parent_ = nullptr;
	public:
		// コンストラクタ
		Transform();
		// コンストラクタ(引数有)
		Transform(const Math::MatWorld::InitStatus& init, const Math::Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
		// 初期化
		void Initialize(const Math::MatWorld::InitStatus& init, const Math::Vec4& color = {1.0f,1.0f,1.0f,1.0f});
		// アフィン変換→ビュープロジェクション変換→転送
		void Update();
		// 演出用特殊変換
		void UniqueUpdate(const Math::MatWorld::InitStatus& state);
		// 描画前コマンド
		void SetDrawCommand(const Math::Mat4& view, const Math::Mat4& projection);
	public:
		// 位置設定
		void SetPos(const Math::Vec3& pos) { mw_.pos_ = pos; }
		// 角度設定
		void SetRota(const Math::Vec3& rota) { mw_.rota_ = rota; }
		// 大きさ設定
		void SetScale(const Math::Vec3& scale) { mw_.scale_ = scale; }
		// 親行列設定
		void SetParent(Math::MatWorld* parent);
		// 色設定
		void SetColor(const Math::Vec4& color) { cbMtrl_.map_->color_ = color; }
	private:
		// 静的定数バッファマネージャーポインタ
		static DX::ConstBufferManager* pCBManager_;
	public:
		// 静的初期化
		static void StaticInitialize(DX::ConstBufferManager* pCBManager);
	};
}
