#pragma once
#include "IPet.h"

namespace YGame
{
	class Horse :
		public IPet
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
		void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

		/// <summary>
		/// �Փˎ����擾
		/// </summary>
		/// <returns>�Փˎ����</returns>
		inline CollisionInfo GetCollisionInfo() override;

	public:

		Horse() = default;

		~Horse() = default;

	public:

	};
}
