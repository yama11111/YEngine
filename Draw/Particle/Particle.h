#pragma once
#include "Model.h"
#include "Lerp.h"
#include "Timer.h"
#include "Power.h"

namespace YGame
{
	// �p�[�e�B�N�����N���X
	class IParticle
	{
	public:
		// �����t���O
		bool isAlive_ = false;
	protected:
		// �I�u�W�F�N�g
		std::unique_ptr<YGame::ModelObject> obj_;
		// �����^�C�}�[
		YMath::Timer aliveTim_;
	public:
		// �X�V
		virtual void Update() = 0;
		// �`��
		virtual void Draw() = 0;
	protected:
		// �r���[�v���W�F�N�V�����|�C���^
		static YGame::ViewProjection* spVP_;
	public:
		// �ÓI������
		static void StaticInitialize(YGame::ViewProjection* pVP);
	public:
		// �f�X�g���N�^
		virtual ~IParticle() = default;
	};
}
