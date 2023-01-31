#pragma once
#include "BaseScene.h"
#include <string>

namespace YScene
{ 
	// 抽象シーンファクトリー
	class ISceneFactory
	{
	public:
		// デストラクタ
		virtual ~ISceneFactory() = default;
		// シーン生成
		virtual BaseScene* CreateScene(const std::string& sceneName) = 0;
	};
}
