#pragma once
#include "Camera.h"

namespace YGame
{
	class ScrollCamera : private Camera
	{
	public:
		// �Ǐ]�_�Ƃ̋���
		YMath::Vector3 distance_;
		// �Ǐ]���Ȃ��͈�
		YMath::Vector3 tolerance_;
	public:
		/// <summary>
		/// ������ (�Ǐ]ver)
		/// </summary>
		/// <param name="distance"> : �Ǐ]�_�Ƃ̋��� (���̋�����ۂ�������)</param>
		/// <param name="pFollowPoint"> : �Ǐ]�_�|�C���^</param>
		/// <param name="tolerance"> : �Ǐ]���Ȃ��͈�</param>
		void Initialize(const YMath::Vector3 distance, YMath::Vector3* pFollowPoint, const YMath::Vector3 tolerance);
		// �X�V
		void Update();
	public:
		// �J�����V�F�C�N
		void Shaking(const float swing, const float dekey, const float place) override { Camera::Shaking(swing, dekey, place); }
		// �r���[�v���W�F�N�V����
		ViewProjection GetViewProjection() override { return Camera::GetViewProjection(); }
		// �J��������
		YMath::Vector3 Direction() override { return Camera::Direction(); }
		// �Ǐ]�_�ݒ�
		void SetFollowPoint(YMath::Vector3* pFollowPoint) override { Camera::SetFollowPoint(pFollowPoint); }
		// �Ǐ]�ݒ�
		void SetIsFollow(const bool isFollow) override { Camera::SetIsFollow(isFollow); }
	public:
		ScrollCamera() = default;
		~ScrollCamera() = default;
	};
}

