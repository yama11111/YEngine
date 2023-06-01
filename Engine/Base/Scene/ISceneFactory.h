#pragma once
#include "BaseScene.h"
#include <string>

namespace YScene
{ 
	// ���ۃV�[���t�@�N�g���[
	class ISceneFactory
	{
	
	public:
		
		// �V�[������
		virtual BaseScene* CreateScene(const std::string& sceneName) = 0;
	
	public:
		
		// �f�X�g���N�^
		virtual ~ISceneFactory() = default;
	};
}
