#pragma once
#include "IEnemy.h"

namespace YGame
{
	class Slime final :
		public IEnemy
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="status"> : �g�����X�t�H�[�����</param>
		void Initialize(const Transform::Status& status);

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="isUpdate"> : �X�V���邩</param>
		void Update(const bool isUpdate) override;

		/// <summary>
		/// �Փˎ����擾
		/// </summary>
		/// <returns>�Փˎ����</returns>
		CollisionInfo GetCollisionInfo() override;

	public:

		Slime() = default;

		~Slime() = default;

	protected:

		void Hit() override;

	};
}
