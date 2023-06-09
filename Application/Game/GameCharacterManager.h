#pragma once
#include "IGameCharacter.h"
#include "GameObjectCollisionManager.h"

namespace YGame
{
	class GameCharacterManager
	{
		
	public:

		/// <summary>
		/// ������
		/// </summary>
		void Initialize();

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

	public:

		/// <summary>
		/// �N���A
		/// </summary>
		void Clear();

		/// <summary>
		/// �}��
		/// </summary>
		/// <param name="character"> : �L�����N�^�[</param>
		void PushBack(IGameCharacter* character);

	private:

		// �I�u�W�F�N�g���X�g
		std::list<std::unique_ptr<IGameCharacter>> characters_;

		// �I�u�W�F�N�g���m�̔���}�l�[�W���[
		GameObjectCollisionManager collMan_;

	};
}
