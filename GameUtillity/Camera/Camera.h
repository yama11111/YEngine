#pragma once
#include "Model.h"
#include "Shake.h"

namespace YGame
{
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
		// �I�u�W�F�N�g
		std::unique_ptr<YGame::ObjectModel> obj_;
		// �r���[�v���W�F�N�V����
		YGame::ViewProjection vp_;
		// �J�����V�F�C�N
		YMath::Shake shake_;
	public:
		struct InitStatus 
		{
			YGame::BaseObject::Status objState_;
			YMath::Vector3* pFollowPos_ = nullptr;
			bool isFollow_ = false;
		};
	public:
		// ������
		void Initialize(const InitStatus& state);
		// trfm �� vp
		void Update();
	public:
		// �J�����V�F�C�N
		void Shaking(const int swing, const int dekey);
		// �r���[�v���W�F�N�V����
		YGame::ViewProjection GetViewProjection();
		// �J��������
		YMath::Vector3 Direction();
		// �h��Ă��邩
		bool IsAct() { return shake_.IsAct(); }
		// �Ǐ]�_�ݒ�
		void SetFollowPoint(YMath::Vector3* pFollowPoint, const bool isFollow = true);
		// �Ǐ]�ݒ�
		void SetIsFollow(const bool isFollow);
	private:
		void UpdateTarget();
	};
}