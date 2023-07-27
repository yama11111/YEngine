#pragma once
#include "BaseCharacter.h"

namespace YGame
{
    class IEnemy :
        public BaseCharacter
    {

	public:

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw() override;

		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="info"> : �Փˎ����</param>
		virtual void OnCollision(const CollisionInfo& info) override;

    public:

        IEnemy() = default;
        
        virtual ~IEnemy() = default;

    protected:

		/// <summary>
		/// ��e
		/// </summary>
		virtual void Hit();

    };
}
