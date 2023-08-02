#pragma once
#include "BaseDrawObject.h"
#include "Ease.h"
#include "BezierEase.h"
#include "Timer.h"
#include "Power.h"

namespace YGame
{
	// �p�[�e�B�N�����N���X
	class BaseParticle
	{
	
	public:

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

		/// <summary>
		/// �����t���O�擾
		/// </summary>
		/// <returns>�����t���O</returns>
		bool IsAlive() const { return isAlive_; }

	public:

		BaseParticle() = default;
		
		virtual ~BaseParticle() = default;
	
	protected:
		
		// �����t���O
		bool isAlive_ = false;
		
		// �����^�C�}�[
		YMath::Timer aliveTimer_;

		// �I�u�W�F�N�g
		std::unique_ptr<BaseDrawObject> obj_;

		// �V�F�[�_�[�^�O
		std::string shaderTag_;
		
		// �`��D��x
		uint16_t drawPriority_ = 0;
	
	protected:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="aliveFrame"> : �������� (F)</param>
		/// <param name="status"> : �������X�e�[�^�X</param>
		/// <param name="shaderTag"> : �V�F�[�_�[�^�O</param>
		/// <param name="drawPriority"> : �`��D��x</param>
		void Initialize(
			const uint32_t aliveFrame,
			const Transform::Status& status,
			const std::string& shaderTag,
			const uint16_t drawPriority);
		
		/// <summary>
		/// �����X�V
		/// </summary>
		/// <returns> : �����Ă��邩</returns>
		void UpdateLife();

		/// <summary>
		/// �I�u�W�F�N�g�ݒ�
		/// </summary>
		/// <param name="obj"> : �I�u�W�F�N�g (���I�C���X�^���X)</param>
		void SetObject(BaseDrawObject* obj);
	};
}
