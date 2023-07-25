#pragma once
#include "ISceneFactory.h"

namespace YScene
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

		// テスト
		static const std::string Test_;
		
		
		// 課題
		static const std::string Task_;

	public:
		
		/// <summary> 
		/// シーン生成
		/// </summary>
		/// <param name="sceneName"> : シーン名</param>
		/// <returns>シーン</returns>
		BaseScene* CreateScene(const std::string& sceneName) override;
	
	};
}
