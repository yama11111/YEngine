#pragma once
#include "IItem.h"

namespace YGame
{
	class Coin final : 
		public IItem
	{
	
	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="status"> : �g�����X�t�H�[�����</param>
		/// <param name="pPet"> : �y�b�g�|�C���^</param>
		void Initialize(const Transform::Status& status);

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="isUpdate"> : �X�V���邩</param>
		void Update(const bool isUpdate) override;

		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="info"> : �Փˎ����</param>
		void OnCollision(const CollisionInfo& info) override;
	
	private:
	
	};
}
