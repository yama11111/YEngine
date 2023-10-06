#pragma once
#include "BaseScene.h"
#include <string>

namespace YGame
{ 
	// 抽象シーンファクトリー
	class ISceneFactory
	{
	
	public:
		
		// シーン生成
		virtual BaseScene* CreateScene(const std::string& sceneName) = 0;
	
	public:
		
		// デストラクタ
		virtual ~ISceneFactory() = default;
	};
}
