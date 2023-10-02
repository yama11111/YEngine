#pragma once
#include "BaseTransition.h"
#include "DrawObjectForSprite2D.h"
#include "CBColor.h"
#include <array>

namespace YGame
{
	class WindBlocks : public BaseTransition
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

		WindBlocks() = default;

		~WindBlocks() = default;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticInitialize();
	
	private:

		// 段階
		enum class Step
		{
			Close,	 // 閉じる
			Load,	 // ロード時間
			Open,	 // 開く
		};

	private:

		// ブロック
		struct Block
		{
			std::unique_ptr<YGame::DrawObjectForSprite2D> obj_; // オブジェクト
			std::unique_ptr<YGame::ConstBufferObject<YGame::CBColor>> cbColor_; // 色定数バッファ
			YMath::Timer actTim_; // 動作タイマー
			bool isActColorPow_ = false;
			YMath::Power colorPow_; // 色タイマー
		};

	private:

		// ブロック配列
		std::vector<std::unique_ptr<Block>> blocks_;

		// 段階
		Step step_ = Step::Close;

		// イージング
		std::array<YMath::Ease<float>, 2> posXEas_;
		YMath::Ease<YMath::Vector4> colorEas_;

	private:

		/// <summary>
		/// シーン遷移更新
		/// </summary>
		void UpdateChange();

		/// <summary>
		/// 伝播
		/// </summary>
		/// <param name="index"></param>
		void PropagateBlock(const size_t index, const bool isActColorPow);

		/// <summary>
		/// ブロック更新
		/// </summary>
		void UpdateBlock();

	private:

		// スプライト(2D)
		static YGame::Sprite2D* spBlockSpr_;
	};
}
