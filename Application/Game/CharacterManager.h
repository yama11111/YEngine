#pragma once
#include "ICharacter.h"
#include <queue>

namespace YGame
{
	class CharacterManager
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
		/// �f�o�b�O�`��
		/// </summary>
		void DrawDebugText();

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
		void PushBack(ICharacter* character);

	public:

		/// <summary>
		/// �V���O���g��
		/// </summary>
		/// <returns></returns>
		static CharacterManager* GetInstance();

	private:

		CharacterManager() = default;

		~CharacterManager() = default;

		CharacterManager(const CharacterManager&) = delete;

		const CharacterManager& operator=(const CharacterManager&) = delete;


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
		static void CheckCollisionCharacterPair(ICharacter* pCharacterA, ICharacter* pCharacterB);
		
		/// <summary>
		/// �A�^������`�F�b�N
		/// </summary>
		/// <param name="pColliderA"> : �R���C�_�[A</param>
		/// <param name="pColliderB"> : �R���C�_�[B</param>
		static bool CheckCollision(BaseCollider* pColliderA, BaseCollider* pColliderB);

	private:

		// �I�u�W�F�N�g���X�g
		std::list<std::unique_ptr<ICharacter>> characters_;

	public:

		struct CharaUpdateStatus
		{
			ICharacter* pChara_ = nullptr;

			uint16_t priority_ = 0;
		};
	
	private:

		// �L�����N�^�[�X�V�����L���[ (�D�揇�ʕt�� : ��)
		std::priority_queue<CharaUpdateStatus> updateQueue_;
	};
	
	inline bool operator< (const CharacterManager::CharaUpdateStatus& status1, const CharacterManager::CharaUpdateStatus& status2)
	{
		return status1.priority_ < status2.priority_;
	}
	inline bool operator> (const CharacterManager::CharaUpdateStatus& status1, const CharacterManager::CharaUpdateStatus& status2)
	{
		return status1.priority_ > status2.priority_;
	}
}
