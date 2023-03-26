#pragma once
#include "ITransition.h"
#include "Sprite2D.h"

namespace YGame
{
	// 暗転
	class Blackout : public ITransition
	{
	private:
		// 暗転段階
		enum class Step
		{
			Dark,	 // 暗
			Load,	 // ロード時間
			Bright,	 // 明
		};
	private:
		// オブジェクト
		std::unique_ptr<Sprite2DObject> obj_;
		// 色
		std::unique_ptr<Color> color_;

		// 段階
		Step step_ = Step::Dark;

		// 透過度イージング
		YMath::Ease<float> blendEas_;
		// 透過度パワー
		YMath::Power blendPow_;
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="changeFrame"> : 変化する時間</param>
		/// <param name="loadFrame"> : 読み込む時間</param>
		void Initialize(const uint32_t changeFrame, const uint32_t loadFrame);
		// リセット(中身だけ初期化)
		void Reset() override;
		// 更新
		void Update() override;
		// 描画
		void Draw() override;
	public:
		// 動作開始
		void Activate() override;
		// 切り替わりの瞬間か
		bool IsChangeMoment() const { return isChangeMoment_; }
		// 終了しているか
		bool IsEnd() const { return isEnd_; }
	private:
		// 切り替え処理更新
		void UpdateChange();
		// 透過処理更新
		void UpdateBlend();
	private:
		// スプライト(2D)
		static std::unique_ptr<Sprite2D> sCurtenSpr_;
	public:
		// 静的初期化
		static void StaticInitialize();
	public:
		Blackout() = default;
		~Blackout() = default;
	};
}
