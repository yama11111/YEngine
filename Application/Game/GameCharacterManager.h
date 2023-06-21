#pragma once
#include "IGameCharacter.h"

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
		/// <param name="character"> : �L�����N�^�[ (���I)</param>
		void PushBack(IGameCharacter* character);

	private:

		/// <summary>
		/// �A�^������S�`�F�b�N
		/// </summary>
		void CheckAllCollision();

		/// <summary>
		/// �y�A�̃A�^������`�F�b�N
		/// </summary>
		/// <param name="pCharacterA"> : �L����A</param>
		/// <param name="pCharacterB"> : �L����B</param>
		static void CheckCollisionPair(IGameCharacter* pCharacterA, IGameCharacter* pCharacterB);

	private:

		// �I�u�W�F�N�g���X�g
		std::list<std::unique_ptr<IGameCharacter>> characters_;

	};
}
