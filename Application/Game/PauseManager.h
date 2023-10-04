#pragma once
#include "DrawObjectForSprite2D.h"
#include "CBColor.h"
#include "Ease.h"
#include "Power.h"

namespace YGame
{
	class PauseManager final
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		void Initialize();

		/// <summary>
		/// ���Z�b�g
		/// </summary>
		void Reset();

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
		/// �|�[�Y����
		/// </summary>
		/// <returns>�|�[�Y����</returns>
		bool IsPause() const { return isPause_; }

		/// <summary>
		/// �|�[�Y����������
		/// </summary>
		/// <returns>�|�[�Y����</returns>
		bool IsElderPause() const { return isElderPause_; }
	
	public:

		static void LoadResource();

	private:

		void ResumeReset();

	private:

		// �I��
		enum class Selection
		{
			Resume, // �߂�
			ReStart, // ���X�^�[�g
			Change, // �J��
		};

	private:

		// �|�[�Y����
		bool isPause_ = false;

		// �|�[�Y����������
		bool isElderPause_ = false;

		// ���݂̑I��
		Selection current_ = Selection::Resume;
	
	private:

		std::unique_ptr<DrawObjectForSprite2D> pause_;
		
		std::unique_ptr<DrawObjectForSprite2D> curten_;
		std::unique_ptr<ConstBufferObject<CBColor>> curtenColor_;

		std::unique_ptr<DrawObjectForSprite2D> restart_;
		std::unique_ptr<ConstBufferObject<CBColor>> restartColor_;
		
		std::unique_ptr<DrawObjectForSprite2D> reset_;
		std::unique_ptr<ConstBufferObject<CBColor>> resetColor_;
		
		std::unique_ptr<DrawObjectForSprite2D> select_;
		std::unique_ptr<ConstBufferObject<CBColor>> selectColor_;
		
		YMath::Power restartPow_;
		YMath::Power resetPow_;
		YMath::Power selectPow_;

		YMath::Ease<YMath::Vector3> selectScaleEas_;
	};
}
