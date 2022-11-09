#pragma once
#include "ConstBufferManager.h"
#include "Vec3.h"
#include "Mat4.h"

namespace Game
{
	class Transform
	{
	public:
		// 行列
		Math::Mat4 m_;
		// 位置
		Math::Vec3 pos_;
		// 回転
		Math::Vec3 rota_;
		// 大きさ
		Math::Vec3 scale_;
	private:
		// 定数バッファ(マテリアル)
		DX::ConstBuffer<DX::MaterialData> cbMtrl_;
		// 定数バッファ(3D変換行列)
		DX::ConstBuffer<DX::TransformData> cbTrfm_;
		// 親行列
		Math::Mat4* parent_ = nullptr;
	public:
		// 設定用ステータス(位置、回転、大きさ)
		struct Status
		{
			Math::Vec3 pos_ = { 0.0f, 0.0f, 0.0f };
			Math::Vec3 rota_ = { 0.0f, 0.0f, 0.0f };
			Math::Vec3 scale_ = { 1.0f, 1.0f, 1.0f };
		};
	public:
		// コンストラクタ
		Transform();
		// コンストラクタ(引数有)
		Transform(const Status& state, const Math::Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
		// 初期化
		void Initialize(const Status& state, const Math::Vec4& color = {1.0f,1.0f,1.0f,1.0f});
		// アフィン変換→ビュープロジェクション変換→転送
		void Update();
		// 演出用特殊変換
		void UniqueUpdate(const Status& state);
		// 描画前コマンド
		void SetDrawCommand(const Math::Mat4& view, const Math::Mat4& projection);
	public:
		// 親行列設定
		void SetParent(Math::Mat4* parent);
		// 色設定
		void SetColor(const Math::Vec4& color);
	private:
		// 静的定数バッファマネージャーポインタ
		static DX::ConstBufferManager* pCBManager_;
	public:
		// 静的初期化
		static void StaticInitialize(DX::ConstBufferManager* pCBManager);
	};
}
