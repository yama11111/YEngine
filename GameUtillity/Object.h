#pragma once
#include "ConstBuffer.h"
#include "Vec3.h"
#include "Mat4.h"

namespace YGame
{
	class Object
	{
	public:
		// 行列
		YMath::Mat4 m_;
		// 位置
		YMath::Vec3 pos_;
		// 回転
		YMath::Vec3 rota_;
		// 大きさ
		YMath::Vec3 scale_;
		// 色
		YMath::Vec4 color_;
	private:
		// 定数バッファ(3D変換行列)
		YDX::ConstBuffer<YDX::TransformCBData> cbTrfm_;
		// 定数バッファ(マテリアル1)
		YDX::ConstBuffer<YDX::ColorCBData> cbColor_;
		// 親行列
		YMath::Mat4* parent_ = nullptr;
	public:
		// 設定用ステータス(位置、回転、大きさ)
		struct Status
		{
			YMath::Vec3 pos_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vec3 rota_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vec3 scale_ = { 1.0f, 1.0f, 1.0f };
		};
	public:
		// 初期化
		void Initialize(const Status& state, const YMath::Vec4& color = {1.0f,1.0f,1.0f,1.0f});
		// アフィン変換→ビュープロジェクション変換→転送
		void Update();
		// 演出用特殊変換
		void UniqueUpdate(const Status& state);
		// 描画前コマンド
		void SetDrawCommand(const YMath::Mat4& view, const YMath::Mat4& projection);
	public:
		// 親行列設定
		void SetParent(YMath::Mat4* parent);
	public:
		// コンストラクタ
		Object();
	};
}
