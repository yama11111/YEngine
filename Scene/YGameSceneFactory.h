#pragma once
#include "ISceneFactory.h"

namespace YScene
{
	class YGameSceneFactory : public ISceneFactory
	{
	private:
		// �^�C�g��
		const std::string Title_	 = "TITLE";
		// �X�e�[�W�Z���N�g
		const std::string Select_	 = "SELECT";
		// �v���C
		const std::string Play_		 = "PLAY";
		// ���U���g
		const std::string Result_	 = "RESULT";

		// �G�f�B�^�[
		const std::string Edit_	 = "EDIT";

		// �e�X�g
		const std::string Test_	 = "TEST";

	public:
		// �V�[������
		BaseScene* CreateScene(const std::string& sceneName) override;
	};
}
