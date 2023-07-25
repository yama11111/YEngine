#pragma once
#include "ISceneFactory.h"

namespace YScene
{
	class YGameSceneFactory : public ISceneFactory
	{

	public:
		
		// �^�C�g��
		static const std::string Title_;
		
		// �X�e�[�W�Z���N�g
		static const std::string Select_;
		
		// �v���C
		static const std::string Play_;

		// �e�X�g
		static const std::string Test_;
		
		
		// �ۑ�
		static const std::string Task_;

	public:
		
		/// <summary> 
		/// �V�[������
		/// </summary>
		/// <param name="sceneName"> : �V�[����</param>
		/// <returns>�V�[��</returns>
		BaseScene* CreateScene(const std::string& sceneName) override;
	
	};
}
