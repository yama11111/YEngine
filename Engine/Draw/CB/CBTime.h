#pragma once
#include <string>

namespace YGame
{
	// ���ԗp�萔�o�b�t�@
	struct CBTime
	{

	public:

		// �萔�o�b�t�@�f�[�^�\����
		struct Data
		{
			// ����
			float time = 0.0f;
			
			float pad1;
			
			float pad2;
			
			float pad3;
		};

	public:

		/// <summary>
		/// �^�O�擾
		/// </summary>
		/// <returns>�^�O��</returns>
		static const std::string Tag()
		{
			return "CBTime";
		}
	};
}
