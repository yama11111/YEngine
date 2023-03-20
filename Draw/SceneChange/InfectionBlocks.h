#pragma once
#include "ITransition.h"
#include "Sprite2D.h"
#include <array>

namespace YGame
{
	// 画面を埋め尽くすブロック
	class InfectionBlocks : public ITransition
	{
	private:
		// 段階
		enum class Step
		{
			Narrow,	 // 狭まる
			Load,	 // ロード時間
			Spread,	 // 広がる
		};
	private:
		// ブロック
		struct Block
		{
			std::unique_ptr<ObjectSprite2D> obj_; // オブジェクト
			YMath::Timer actTim_; // 動作タイマー
		};
	private:
		// ブロック配列
		std::vector<std::vector<std::unique_ptr<Block>>> blocks_;

		// 段階
		Step step_ = Step::Narrow;

		// イージング
		std::array<YMath::Ease<float>, 2> scaleEas_;
		std::array<YMath::Ease<float>, 2> rotaEas_;
		// 現段階のインデックス
		size_t stepIndex_ = 0;

		// アンカーポイント
		YMath::Vector2 anchor_;
		// 開始位置 (要素番号)
		YMath::Vector2 start_;
		// 終了位置 (要素番号)
		YMath::Vector2 end_;
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="changeFrame"> : ブロック１つが変化する時間</param>
		/// <param name="loadFrame"> : 読み込む時間</param>
		/// <param name="leftTop"> : 1番左上のブロックの位置</param>
		/// <param name="size"> : ブロック1つの大きさ</param>
		/// <param name="num"> : 要素数 (小数点切り捨て)</param>
		/// <param name="anchor"> : 開始点のアンカーポイント (初期値は中心)</param>
		void Initialize(
			const uint32_t changeFrame, const uint32_t loadFrame, 
			const YMath::Vector2& leftTop, const float size, const YMath::Vector2& num,
			const YMath::Vector2& anchor = { 0.5f,0.5f });
		// リセット(中身だけ初期化)
		void Reset() override;
		// 更新
		void Update() override;
		// 描画
		void Draw() override;
	public:
		// 動作開始
		void Activate() override;
		// アンカーポイント設定
		void SetAnchorPoint(const YMath::Vector2& anchor);
	private:
		// シーン遷移更新
		void ChangeUpdate();
		// ブロック更新
		void BlockUpdate();
		// 伝播
		void BlockPropagate(const size_t x, const size_t y);
	private:
		// スプライト(2D)
		static std::unique_ptr<Sprite2D> sBlockSpr_;
	public:
		// 静的初期化
		static void StaticInitialize();
	public:
		InfectionBlocks() = default;
		~InfectionBlocks() = default;
	};

}
