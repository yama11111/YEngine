#pragma once
#include "ISceneFactory.h"

namespace YGame
{
	class YGameSceneFactory : public ISceneFactory
	{

	public:
		
		// タイトル
		static const std::string Title_;
		
		// ステージセレクト
		static const std::string Select_;
		
		// プレイ
		static const std::string Play_;

		// リザルト
		static const std::string Result_;

		// テスト
		static const std::string Test_;

	public:
		
		/// <summary> 
		/// シーン生成
		/// </summary>
		/// <param name="sceneName"> : シーン名</param>
		/// <returns>シーン</returns>
		std::unique_ptr<BaseScene> CreateScene(const std::string& sceneName) override;
	
	};
}
