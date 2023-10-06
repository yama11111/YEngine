#pragma once
#include "DrawObjectForSprite2D.h"
#include "UINumber.h"
#include "CBColor.h"
#include "Ease.h"
#include "Timer.h"
#include "Power.h"

namespace YGame
{
	class CardDrawer
	{
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親トランスフォームポインタ</param>
		/// <param name="number"> : 番号</param>
		/// <param name="isClear"> : クリアフラグ</param>
		void Initialize(Transform* pParent, const int32_t number, const bool isClear = false);
		
		/// <summary>
		/// リセット
		/// </summary>
		/// <param name="isClear"> : クリアフラグ</param>
		void Reset(const bool isClear = false);
		
		/// <summary>
		/// 更新
		/// </summary>
		void Update();
		
		/// <summary>
		/// 描画
		/// </summary>
		void Draw(uint16_t p);
	
	public:
		
		/// <summary>
		/// 決定
		/// </summary>
		void Decision() { isDecided_ = true;  }
		
		/// <summary>
		/// 選択設定
		/// </summary>
		/// <param name="isSelect"></param>
		void SetSelect(const bool isSelect) { isSelected_ = isSelect; }
	
	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();
	
	private:
	
		// 核
		Transform core_;

		// 数字用オブジェクト
		Transform numberTra_;
		std::unique_ptr<UINumber> numberUI_;
		
		// ステージカード
		std::unique_ptr<DrawObjectForSprite2D> cardObj_;
		std::unique_ptr<ConstBufferObject<CBColor>> color_;

		// 数字
		int32_t number_ = 0;

		// 選択されているか
		bool isSelected_ = false;
		// 選択されていたか
		bool isElderSelected_ = false;
		// 決定されたか
		bool isDecided_ = false;

		// 移動用イージング
		YMath::Ease<float> moveEas_;
		// 拡大用イージング
		YMath::Ease<float> scaleEas_;
		// 選択用パワー
		YMath::Power selectPow_;

		// 数字用色
		//std::unique_ptr<ConstBufferObject<CBColor>> color_;
		
		// クリアしたか
		bool isClear_ = false;

	private:

		static Sprite2D* spCardSpr_;

	private:

		// 選択アニメーション更新
		void UpdateSelectAnimation();
	};
}
