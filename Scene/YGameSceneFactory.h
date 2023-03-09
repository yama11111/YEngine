#pragma once
#include "ISceneFactory.h"

namespace YScene
{
	class YGameSceneFactory : public ISceneFactory
	{
	private:
		// �^�C�g��
		const std::string Title	 = "TITLE";
		// �X�e�[�W�Z���N�g
		const std::string Select = "SELECT";
		// �v���C
		const std::string Play	 = "PLAY";
		// ���U���g
		const std::string Result = "RESULT";

		// 
		const std::string Coll	 = "COLL";

		//
		const std::string Demo	 = "DEMO";

	public:
		// �V�[������
		BaseScene* CreateScene(const std::string& sceneName) override;
	};
}
