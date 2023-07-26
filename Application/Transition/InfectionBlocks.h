#pragma once
#include "BaseTransition.h"
#include "Object.h"
#include "ConstBuffer.h"
#include "CBSprite2DTransform.h"
#include "CBColor.h"
#include "CBTexConfig.h"
#include "Sprite2D.h"
#include <array>

namespace YScene
{
	// 画面を埋め尽くすブロック
	class InfectionBlocks : public BaseTransition
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
			std::unique_ptr<YGame::Transform> transform_; // トランスフォーム
			std::unique_ptr<YGame::Object> obj_; // オブジェクト
			std::unique_ptr<YGame::ConstBuffer<YGame::CBSprite2DTransform>> cbTransform_; // トランスフォーム定数バッファ
			std::unique_ptr<YGame::ConstBuffer<YGame::CBColor>> cbColor_; // 色定数バッファ
			std::unique_ptr<YGame::ConstBuffer<YGame::CBTexConfig>> cbTexConfig_; // テクスチャ設定定数バッファ
			YMath::Timer actTim_; // 動作タイマー
			YMath::Timer colorStartTim_; // 色タイマー (始)
			YMath::Timer colorEndTim_; // 色タイマー (終)

			// タイマー動作
			void SetTimerActive(const bool isAct)
			{
				actTim_.SetActive(isAct);
				colorStartTim_.SetActive(isAct);
				colorEndTim_.SetActive(isAct);
			};
		};

	private:

		// ブロック配列
		std::vector<std::vector<std::unique_ptr<Block>>> blocks_;

		// 段階
		Step step_ = Step::Narrow;

		// イージング
		std::array<YMath::Ease<float>, 2> scaleEas_;
		std::array<YMath::Ease<float>, 2> rotaEas_;
		std::array<YMath::Ease<float>, 2> colorEas_;
		std::array<YMath::Ease<float>, 2> alphaEas_;

		// 現段階のインデックス
		size_t stepIndex_ = 0;


		// 開始位置 (要素番号)
		YMath::Vector2 start_;

		// 終了位置 (要素番号)
		YMath::Vector2 end_;

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

	private:

		
		/// <summary>
		/// シーン遷移更新
		/// </summary>
		void UpdateChange();
		
		/// <summary>
		/// 伝播
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		void PropagateBlock(const size_t x, const size_t y);
		
		/// <summary>
		/// ブロック更新
		/// </summary>
		void UpdateBlock();

	private:

		// スプライト(2D)
		static YGame::Sprite2D* spBlockSpr_;

		// 左上
		static YMath::Vector2 sLeftTop_;

		// 数
		static YMath::Vector2 sNum_;

		// アンカーポイント
		static YMath::Vector2 sAnchor_;

		// 大きさ
		static float sSize_;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pBlockTex"> : ブロックの画像</param>
		static void StaticInitialize(YGame::Texture* pBlockTex);

	public:

		InfectionBlocks() = default;

		~InfectionBlocks() = default;
	};

}
