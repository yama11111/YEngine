//#pragma once
//#include "UIButtonDrawer.h"
//#include "Lerp.h"
//#include "Power.h"
//
//namespace YGame
//{
//    class UIChargeButtonDrawer :
//        public UIButtonDrawer
//    {
//
//    public:
//		
//		/// <summary>
//		/// 初期化
//		/// </summary>
//		/// <param name="pButtonTex"> : ボタンテクスチャ</param>
//		/// <param name="pPressedTex"> : 押されたボタンテクスチャ</param>
//		/// <param name="pPressedTex"> : 死んだボタンテクスチャ</param>
//        /// <param name="frame"> : 溜まる時間</param>
//        void Initialize(Texture* pButtonTex, Texture* pPressedTex, Texture* pDeadTex, const unsigned int frame);
//
//        /// <summary>
//		/// 更新
//		/// </summary>
//		/// <param name="isPush"> : 押したか</param>
//        void Update(const bool isPush) override;
//
//		/// <summary>
//		/// 描画
//		/// </summary>
//		/// <param name="pObject"> : オブジェクトポインタ</param>
//		void Draw(Sprite2D::Object* pObject) override;
//		
//		/// <summary>
//		/// チャージ満タンか取得
//		/// </summary>
//		/// <returns>チャージ満タンか</returns>
//		bool IsChargeMax() { return chargePower_.IsMax(); }
//
//    public:
//
//		
//		std::unique_ptr<Sprite2D::Object> chargeGaugeObj1_;
//		std::unique_ptr<Sprite2D::Object> chargeGaugeObj2_;
//		std::unique_ptr<Sprite2D::Object> chargeGaugeObj3_;
//
//        // チャージタイマー
//        YMath::Power chargePower_;
//
//        // チャージイージング
//		YMath::Ease<float> chargeWidthEase_;
//
//		
//	public:
//		
//		static Sprite2D* spChargeGauge_;
//		
//		static std::unique_ptr<CBColor> sChargeGaugeColor1_;
//		static std::unique_ptr<CBColor> sChargeGaugeColor2_;
//		static std::unique_ptr<CBColor> sChargeGaugeColor3_;
//
//	public:
//
//		static void StaticInitialize();
//    };
//}
