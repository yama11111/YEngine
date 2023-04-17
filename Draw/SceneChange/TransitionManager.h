#pragma once
#include "ITransition.h"
#include <memory>

namespace YGame
{
	// �V�[���J�ڃ}�l�[�W���[
	class TransitionManager
	{
	public:
		// ���
		enum class Type
		{
			Blackout, // �Ó]
			InfectionBlocks, // �Z�H�u���b�N
			End, // ���T�C�Y�p (�g��Ȃ�)
		};
	private:
		// �g�����W�V�����z��
		std::vector<std::unique_ptr<ITransition>> tras_;
	public:
		// ������
		void Initialize();
		// ���Z�b�g(���g����������)
		void Reset();
		// �X�V
		void Update();
		// �`��
		void Draw();
	public:
		/// <summary>
		/// �J��
		/// </summary>
		/// <param name="type"> : �J�ڂ̎d��</param>
		/// <param name="-------------------------------"></param>
		/// <param name="Type::Blackout"> : �Ó]</param>
		/// <param name="Type::InfectionBlocks"> : �Z�H�u���b�N(��ʑS�̂����ߐs�������)</param>
		/// <param name="Type::End"> : ���T�C�Y�p (�g��Ȃ�)</param>
		void Activate(const Type& type);
	public:
		// �؂�ւ���Ă���r����
		bool IsPreChange() const;
		// �؂�ւ��̏u�Ԃ�
		bool IsChangeMoment() const;
		// �I�����Ă��邩
		bool IsEnd() const;
	public:
		// �ÓI������
		static void StaticInitialize();
	public:
		// �V���O���g��
		static TransitionManager* GetInstance();
	private:
		TransitionManager() = default;
		~TransitionManager() = default;
		TransitionManager(const TransitionManager&) = delete;
		const TransitionManager& operator=(const TransitionManager&) = delete;
	};

	// �V�[���J�ڂ̎��
	using TransitionType = TransitionManager::Type;
}

