#pragma once
#include "StageDrawer.h"
#include "StageStatusDrawer.h"

#include "CBTexConfig.h"

namespace YGame
{
	class SelectDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// リセット
		/// </summary>
		void Reset();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

		/// <summary>
		/// ステージ番号設定
		/// </summary>
		/// <param name="index"> : ステージ番号</param>
		void SetStageIndex(const int32_t index);

	public:

		/// <summary>
		/// 生成アニメーション
		/// </summary>
		void PopAnimation();

		/// <summary>
		/// 追従点
		/// </summary>
		/// <returns>追従点</returns>
		YMath::Vector3 FollowPoint() const;
	
	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

		/// <summary>
		/// ビュープロジェクションポインタ設定
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void SetViewProjection(ViewProjection* pVP);
		
	private:

		struct Stage
		{
			Transform trfm;
			StageDrawer stage;
			StageStatusDrawer status;
			bool isPop = false;

			YMath::Power followPointPow_;
		};
	
	private:

		int32_t stageIndex_;
		
		std::vector<Stage> stages_;
		
		YMath::Ease<YMath::Vector3> followPointEas_;
		YMath::Ease<YMath::Vector2> offsetEas_;
		
		YMath::Timer popTimer_;

		std::unique_ptr<DrawObjectForSprite3D> back_;
		std::unique_ptr<ConstBufferObject<CBColor>> backColor_;
		std::unique_ptr<ConstBufferObject<CBTexConfig>> backTexConfig_;

		YMath::Timer offsetTimer_;

	private:

		static ViewProjection* spVP_;

		static Sprite3D* spBackSpr_;

	};
}
