#pragma once
#include "DrawObjectForSprite2D.h"
#include "CBColor.h"
#include "Ease.h"
#include "Power.h"

namespace YGame
{
	class PauseManager final
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

	public:

		/// <summary>
		/// ポーズ中か
		/// </summary>
		/// <returns>ポーズ中か</returns>
		bool IsPause() const { return isPause_; }

		/// <summary>
		/// ポーズ中だったか
		/// </summary>
		/// <returns>ポーズ中か</returns>
		bool IsElderPause() const { return isElderPause_; }
	
	public:

		static void LoadResource();

	private:

		void ResumeReset();

	private:

		// 選択
		enum class Selection
		{
			Resume, // 戻る
			ReStart, // リスタート
			Change, // 遷移
		};

	private:

		// ポーズ中か
		bool isPause_ = false;

		// ポーズ中だったか
		bool isElderPause_ = false;

		// 現在の選択
		Selection current_ = Selection::Resume;
	
	private:

		std::unique_ptr<DrawObjectForSprite2D> pause_;
		
		std::unique_ptr<DrawObjectForSprite2D> curten_;
		std::unique_ptr<ConstBufferObject<CBColor>> curtenColor_;

		std::unique_ptr<DrawObjectForSprite2D> restart_;
		std::unique_ptr<ConstBufferObject<CBColor>> restartColor_;
		
		std::unique_ptr<DrawObjectForSprite2D> reset_;
		std::unique_ptr<ConstBufferObject<CBColor>> resetColor_;
		
		std::unique_ptr<DrawObjectForSprite2D> select_;
		std::unique_ptr<ConstBufferObject<CBColor>> selectColor_;
		
		YMath::Power restartPow_;
		YMath::Power resetPow_;
		YMath::Power selectPow_;

		YMath::Ease<YMath::Vector3> selectScaleEas_;
	};
}
