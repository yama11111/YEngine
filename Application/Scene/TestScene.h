#pragma once
#include "BaseScene.h"
#include "BaseDrawer.h"

#include "Ease.h"
#include "BezierEase.h"
#include "SplineEase.h"

#include "Timer.h"
#include "Power.h"

namespace YGame
{
	// �e�X�g�V�[��
	class TestScene : public BaseScene
	{

	private:

		Model*pGraph_ = nullptr;

		std::unique_ptr<DrawObjectForModel> obj_;
		std::unique_ptr<DrawObjectForModel> start_;
		std::unique_ptr<DrawObjectForModel> end_;
		
		std::unique_ptr<ConstBufferObject<CBColor>> cbColorObj_;
		std::unique_ptr<ConstBufferObject<CBColor>> cbColorStart_;
		std::unique_ptr<ConstBufferObject<CBColor>> cbColorEnd_;

		YMath::Ease<YMath::Vector3> ease_;
		YMath::BezierEase<YMath::Vector3> bezier_;
		YMath::SplineEase<YMath::Vector3> spline_;

		YMath::Timer timer_;
		YMath::Power power_;

		YGame::ViewProjection vp_;

		uint32_t lerpIdx = 0;
		uint32_t ratioIdx = 0;

	public:

		/// <summary>
		/// �ǂݍ���
		/// </summary>
		void Load() override;

		/// <summary>
		/// ������
		/// </summary>
		void Initialize() override;

		/// <summary>
		/// �I������
		/// </summary>
		void Finalize() override;

		/// <summary>
		/// �X�V
		/// </summary>
		void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

	public:

		// �R���X�g���N�^
		TestScene() = default;
		
		// �f�X�g���N�^
		~TestScene() = default;

	};
}
