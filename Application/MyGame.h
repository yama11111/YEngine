#pragma once
#include "YFramework.h"

namespace YBase
{
	class MyGame : public YFramework
	{

	private:

		YGame::PostEffect* pPostEffect_ = nullptr;

		std::unique_ptr<YGame::PostEffect::Object> postEffectObj_;

		bool isDef_ = false;
		bool isUVShift_ = false;
		bool isChack_ = true;

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <returns>成功したか</returns>
		bool Initialize() override;
		
		/// <summary>
		/// 終了処理
		/// </summary>
		void Finalize() override;
		
		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

	public:

		/// <summary>
		/// ゲームシーン描画
		/// </summary>
		void DrawGameScene();

	};
}
