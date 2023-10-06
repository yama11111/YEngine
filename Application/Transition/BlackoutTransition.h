#pragma once
#include "BaseTransition.h"
#include "DrawObjectForSprite2D.h"
#include "ConstBufferObject.h"
#include "CBSprite2DTransform.h"
#include "CBColor.h"
#include "CBTexConfig.h"
#include "Sprite2D.h"

namespace YGame
{
	// 暗転
	class BlackoutTransition : public BaseTransition
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		virtual void Initialize() override;

		/// <summary>
		/// 終了処理
		/// </summary>
		virtual void Finalize() override;

		/// <summary>
		/// リセット (中身だけ初期化)
		/// </summary>
		virtual void Reset() override;

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

		BlackoutTransition() = default;

		~BlackoutTransition() = default;

	public:

		// 静的初期化
		static void LoadResource();
	
	private:
		
		// オブジェクト
		std::unique_ptr<YGame::DrawObjectForSprite2D> obj_;
		
		// 色定数バッファ
		std::unique_ptr<YGame::ConstBufferObject<YGame::CBColor>> cbColor_;
		

		// 透過度パワー
		YMath::Power blendPow_;

	private:
		
		// 切り替え処理更新
		void UpdateChange();
		
		// 透過処理更新
		void UpdateBlend();
	
	private:
		
		// スプライト(2D)
		static YGame::Sprite2D* spCurtenSpr_;

		// 透過度イージング
		static YMath::Ease<float> sBlendEas_;
	};
}
