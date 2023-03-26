#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Shake.h"

namespace YGame
{
	// �J�����N���X
	class Camera
	{
	public:
		// �ʒu
		YMath::Vector3 pos_;
		// ��]
		YMath::Vector3 rota_;
	private:
		// �Ǐ]�_�|�C���^
		YMath::Vector3* pFollowPoint_ = nullptr;
		// �Ǐ]�t���O
		bool isFollow_ = false;
		// �g�����X�t�H�[��
		Transform transform_;
		// �r���[�v���W�F�N�V����
		ViewProjection vp_;
		// �J�����V�F�C�N
		YMath::Shake shake_;
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="status"> : �g�����X�t�H�[���ݒ�p�X�e�[�^�X</param>
		/// <param name="status.pos_"> : �ʒu</param>
		/// <param name="status.rota_"> : ��]</param>
		/// <param name="status.scale_"> : �傫��</param>
		/// <param name="-------------------------------------------"></param>
		/// <param name="pFollowPoint"> : �Ǐ]�_�|�C���^</param>
		/// <param name="isFollow"> : �Ǐ]���邩</param>
		void Initialize(const Transform::Status& status, YMath::Vector3* pFollowPoint = nullptr, bool isFollow = false);
		// �X�V
		void Update();
	public:
		// �J�����V�F�C�N
		void Shaking(const int swing, const int dekey);
		// �r���[�v���W�F�N�V����
		ViewProjection GetViewProjection();
		// �J��������
		YMath::Vector3 Direction();
		// �h��Ă��邩
		bool IsAct() { return shake_.IsAct(); }
		// �Ǐ]�_�ݒ�
		void SetFollowPoint(YMath::Vector3* pFollowPoint, const bool isFollow = true);
		// �Ǐ]�ݒ�
		void SetIsFollow(const bool isFollow);
	private:
		// �����_�X�V
		void UpdateTarget();
	};
}