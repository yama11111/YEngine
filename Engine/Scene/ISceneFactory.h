#pragma once
#include "BaseScene.h"
#include <string>

namespace YGame
{ 
	// 抽象シーンファクトリー
	class ISceneFactory
	{
	
	public:
		
		/// <summary>
		/// シーン生成
		/// </summary>
		/// <param name="sceneName"> : 名前</param>
		/// <returns>シーン</returns>
		virtual std::unique_ptr<BaseScene> CreateScene(const std::string& sceneName) = 0;
	
	public:
		
		// デストラクタ
		virtual ~ISceneFactory() = default;
	};
}
