#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Shake.h"
#include "Timer.h"
#include "Lerp.h"

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
	
	protected:
		
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


		bool isSmooth_ = false;

		YMath::Timer moveTimer_;

		YMath::Ease<YMath::Vector3> moveEase_;

	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pos"> : �ʒu</param>
		/// <param name="rota"> : ��]</param>
		void Initialize(const YMath::Vector3 pos, const YMath::Vector3 rota);
		
		/// <summary>
		/// ������ (�Ǐ]ver)
		/// </summary>
		/// <param name="pos"> : �ʒu</param>
		/// <param name="pFollowPoint"> : �Ǐ]�_�|�C���^</param>
		/// <param name="isFollow"> : �Ǐ]���邩</param>
		void Initialize(const YMath::Vector3 pos, YMath::Vector3* pFollowPoint, bool isFollow);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
	
	public:
		// ���炩�Ɉړ�
		void SmoothMoving(const unsigned int frame, const YMath::Vector3& pos, const float exponent);
		// �J�����V�F�C�N
		virtual void Shaking(const float swing, const float dekey, const float place);
		// �r���[�v���W�F�N�V����
		virtual ViewProjection GetViewProjection();
		// �J��������
		virtual YMath::Vector3 Direction();
		// �Ǐ]�_�ݒ�
		virtual void SetFollowPoint(YMath::Vector3* pFollowPoint);
		// �Ǐ]�ݒ�
		virtual void SetIsFollow(const bool isFollow);
	private:
		// �����_�X�V
		void UpdateTarget();
	public:
		Camera() = default;
		~Camera() = default;
	};
}