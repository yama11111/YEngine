#pragma once
#include "ITransitionFactory.h"

namespace YScene
{
	class TransitionManager
	{
	
	private:
		
		// �g�����W�V����
		std::unique_ptr<BaseTransition> transition_;

		// �g�����W�V�����V�[����
		std::string transitionName_ = {};

		// �g�����W�V�����t�@�N�g���[
		static std::unique_ptr<ITransitionFactory> transitionFactory_;
		
	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="transitionName"> : �J�ږ�</param>
		void Initialize(const std::string& transitionName);

		/// <summary>
		/// ���Z�b�g (���g����������)
		/// </summary>
		void Reset();

		/// <summary>
		/// �I������
		/// </summary>
		void Finalize();

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
		/// �V�[���J�ڊJ�n
		/// </summary>
		/// <param name="loadFrame"> : �ǂݍ��ގ���</param>
		/// <param name="leftTop"> : 1�ԍ���̃u���b�N�̈ʒu</param>
		virtual void Activate(const uint32_t changeFrame, const uint32_t loadFrame);

	public:
		
		/// <summary>
		/// �J�ڃt�@�N�g���[�ݒ�
		/// </summary>
		/// <param name="transitionFactory"> : �J�ڃt�@�N�g���[</param>
		static void SetTransitionFactory(ITransitionFactory* transitionFactory);
		
		/// <summary>
		/// �V�[���J�ڐݒ�
		/// </summary>
		/// <param name="transitionName"> : �J�ڂ̖��O</param>
		void SetTransition(const std::string& transitionName);

		/// <summary>
		/// ���݂̃g�����W�V�������擾
		/// </summary>
		/// <returns>���݂̃g�����W�V������</returns>
		std::string CurrentTransitionName() const { return transitionName_; }

		/// <summary>
		/// ���쒆���擾
		/// </summary>
		/// <returns>���쒆��</returns>
		bool IsAct() const;

		/// <summary>
		/// ���؂ꒆ��
		/// </summary>
		/// <returns></returns>
		bool IsFalling() const;

		/// <summary> 
		/// �؂�ւ��̏u�Ԃ��擾
		/// </summary>
		/// <returns>�؂�ւ��̏u�Ԃ�</returns>
		bool IsChangeMoment() const;

		/// <summary>
		/// ���J������
		/// </summary>
		/// <returns>�؂�ւ���Ă���r����</returns>
		bool IsRising() const;

		/// <summary>
		/// �I�����Ă��邩�擾
		/// </summary>
		/// <returns>�I�����Ă��邩</returns>
		bool IsEnd() const;
	
	public:

		// �V���O���g��
		static TransitionManager* GetInstance();

	private:

		TransitionManager() = default;

		~TransitionManager() = default;

		TransitionManager(const TransitionManager&) = delete;

		const TransitionManager& operator=(const TransitionManager&) = delete;
	
	public:
		
		// �ÓI������
		static void StaticInitialize();
	
	};
}

