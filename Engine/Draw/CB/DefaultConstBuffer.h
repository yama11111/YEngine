#pragma once
#include "BaseConstBuffer.h"

namespace YGame
{
	class DefaultConstBuffer
	{

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void StaticInitialize();

		/// <summary>
		/// �f�t�H���g�l�̒萔�o�b�t�@�̃|�C���^�擾
		/// </summary>
		/// <param name="tag"> : �^�O</param>
		/// <returns>�f�t�H���g�l�̒萔�o�b�t�@�̃|�C���^</returns>
		static BaseConstBuffer* Ptr(const std::string& tag);
	};
}

