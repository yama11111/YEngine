#pragma once
#include "BaseGraphic.h"

namespace YGame
{
	class DefaultGraphic
	{

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void LoadResource();

		/// <summary>
		/// �f�t�H���g�l�̃O���t�B�b�N�̃|�C���^�擾
		/// </summary>
		/// <param name="tag"> : �^�O</param>
		/// <returns>�f�t�H���g�̃O���t�B�b�N�̃|�C���^</returns>
		static BaseGraphic* Ptr(const std::string& tag);
	};
}

