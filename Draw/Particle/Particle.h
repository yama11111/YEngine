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

	class FireWork : public IParticle
	{
	private:
		// �ʒu
		YMath::Ease<YMath::Vector3> posEas_;
		// ��]
		YMath::Ease<YMath::Vector3> rotaEas_;
		// �傫��
		YMath::Ease<float> scaleEas_;
		// �F
		std::unique_ptr<YGame::Color> color_;
		// �A���t�@�l
		YMath::Ease<float> alphaEas_;
	public:
		void Emit(
			const uint32_t aliveTime,
			const YMath::Ease<YMath::Vector3>& pos,
			const YMath::Ease<YMath::Vector3>& rota,
			const float scale, 
			const YMath::Vector4& color);
		void Update() override;
		void Draw() override;
	private:
		static YGame::Model* spModel_;
	public:
		static void StaticInitialize(YGame::Model* pModel);
	public:
		~FireWork() = default;
	};
}
