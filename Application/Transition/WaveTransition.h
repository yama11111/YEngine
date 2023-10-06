#pragma once
#include "BaseTransition.h"
#include "DrawObjectForSprite2D.h"
#include "CBColor.h"
#include <array>

namespace YGame
{
	class WaveTransition final : public BaseTransition
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		virtual void Initialize() override;

		/// <summary>
		/// リセット (中身だけ初期化)
		/// </summary>
		virtual void Reset() override;

		/// <summary>
		/// 終了処理
		/// </summary>
		virtual void Finalize() override;

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw() override;

	public:

		/// <summary> 
		/// 動作開始
		/// </summary>
		/// <param name="loadFrame"> : 読み込む時間</param>
		/// <param name="leftTop"> : 1番左上のブロックの位置</param>
		virtual void Activate(const uint32_t changeFrame, const uint32_t loadFrame) override;

	public:

		WaveTransition() = delete;
		
		WaveTransition(const bool isReverce) : isReverce_(isReverce){}

		~WaveTransition() = default;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

	private:

		// 波
		struct Wave
		{
			std::unique_ptr<DrawObjectForSprite2D> obj_; // オブジェクト
			std::unique_ptr<ConstBufferObject<CBColor>> cbColor_; // 色定数バッファ
			YMath::Timer actTim_; // 動作タイマー
		};

	private:

		// 反転フラグ
		bool isReverce_ = false;

		// 波
		std::array<std::unique_ptr<Wave>, 3> waves_;

		// イージング
		std::array<YMath::Ease<float>, 2> scaleXEas_;

	private:

		/// <summary>
		/// シーン遷移更新
		/// </summary>
		void UpdateChange();

		/// <summary>
		/// ブロック更新
		/// </summary>
		void UpdateBlock();

	private:

		// スプライト(2D)
		static YGame::Sprite2D* spBlockSpr_;
	};
}
