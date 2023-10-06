#pragma once
#include "Vector3.h"
#include "ViewProjection.h"

namespace YGame
{
	class DebriParticle
	{

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void StaticInitialize();

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="num"> : ��</param>
		/// <param name="pos"> : �ʒu</param>
		/// <param name="powerDirection"> : �͂̂��������</param>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		static void Emit(
			const size_t num,
			const YMath::Vector3& pos,
			ViewProjection* pVP);

	};
}
