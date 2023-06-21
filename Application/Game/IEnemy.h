#pragma once
#include "IGameCharacter.h"

namespace YGame
{
    class IEnemy :
        public IGameCharacter
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
		/// <param name="pPair"> : ����̃L�����N�^�[�|�C���^</param>
		virtual void OnCollision(IGameCharacter* pPair) override;

    public:

        IEnemy() = default;
        
        virtual ~IEnemy() = default;

    protected:

    };
}
