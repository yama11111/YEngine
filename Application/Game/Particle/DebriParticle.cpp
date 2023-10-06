#include "DebriParticle.h"
#include "BaseParticle.h"
#include "ParticleManager.h"
#include "DrawObjectForModel.h"
#include "ConstBufferObject.h"
#include "CBColor.h"
#include "MathUtil.h"
#include "Speed.h"
#include <memory>

using YGame::DebriParticle;
using YMath::Vector3;
using YMath::Vector4;

namespace YGame
{
	class impl_DebriParticle final :
		public DebriParticle,
		public BaseParticle
	{

	public:

		// ����
		static impl_DebriParticle* Create();

		// ������
		void Initialize(
			const uint32_t aliveFrame,
			const YMath::Vector3& pos,
			const float endScale,
			const Vector3& power,
			const Vector3& acceleration,
			const Vector3& maxSpeed,
			const float endAlpha,
			const float exponent,
			ViewProjection* pVP);

		// �X�V
		void Update() override;

	private:

		DrawObjectForModel* pObj_ = nullptr;

		// �F�萔�o�b�t�@
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;

		// �X�s�[�h
		YMath::Speed speed_;

		// �X�P�[���C�[�W���O
		YMath::Ease<float> scaleEas_;

		// �i�s�̓C�[�W���O
		YMath::Ease<YMath::Vector3> movePowerEas_;
	};

	impl_DebriParticle* impl_DebriParticle::Create()
	{
		impl_DebriParticle* newParticle = new impl_DebriParticle();

		DrawObjectForModel* newObj = DrawObjectForModel::Create({}, nullptr, nullptr, false);

		// �I�u�W�F�N�g�̃|�C���^��ێ�
		newParticle->pObj_ = newObj;
		newParticle->SetObject(newObj);

		newParticle->cbColor_.reset(ConstBufferObject<CBColor>::Create(false));

		return newParticle;
	}

	void impl_DebriParticle::Initialize(
		const uint32_t aliveFrame,
		const YMath::Vector3& pos,
		const float endScale,
		const Vector3& power,
		const Vector3& acceleration,
		const Vector3& maxSpeed,
		const float endAlpha,
		const float exponent,
		ViewProjection* pVP)
	{
		BaseParticle::Initialize(aliveFrame, { pos }, "ModelPhong", 1);

		cbColor_->data_.baseColor = Vector4(1.0f, 1.0f, 0.0f, 0.75f);
		pObj_->InsertConstBuffer(cbColor_.get());
		pObj_->SetViewProjection(pVP);

		scaleEas_.Initialize(endScale, endScale / 2.0f, exponent);

		speed_.Initialize(maxSpeed, acceleration, false);
		movePowerEas_.Initialize(power, {}, exponent);
	}

	void impl_DebriParticle::Update()
	{
		if (isAlive_ == false) { return; }

		// �^�C�}�[�̊���
		float ratio = aliveTimer_.Ratio();

		// ���񂾂�x��
		speed_.Update(movePowerEas_.Out(ratio));
		obj_->transform_.pos_ += speed_.Velocity();

		// ���񂾂񏬂���
		float scaleVal = scaleEas_.In(ratio);
		obj_->transform_.scale_ = Vector3(scaleVal, scaleVal, scaleVal);


		obj_->Update();

		BaseParticle::UpdateLife();
	}
}

// �p�[�e�B�N���ÓI�ɗp��
static const size_t skParticleNum = 100;
static std::array<std::unique_ptr<YGame::impl_DebriParticle>, skParticleNum> sParticles;
static const std::string skTag = "DebriParticle";
static bool sIsInit = false;

void DebriParticle::StaticInitialize()
{
	if (sIsInit == false)
	{
		// ����
		for (size_t i = 0; i < sParticles.size(); i++)
		{
			sParticles[i].reset(impl_DebriParticle::Create());
		}

		sIsInit = true;
	}

	// �p�[�e�B�N���}�l�[�W���[�ɑ}��
	std::list<BaseParticle*> particlePtrs;

	for (size_t i = 0; i < sParticles.size(); i++)
	{
		particlePtrs.emplace_back(sParticles[i].get());
	}

	ParticleManager::GetInstance()->InsertParticles(skTag, particlePtrs);
}

static YGame::impl_DebriParticle* DeadParticlePtr()
{
	// ����ł���p�[�e�B�N����Ԃ�
	for (size_t i = 0; i < sParticles.size(); i++)
	{
		if (sParticles[i]->IsAlive() == false)
		{
			return sParticles[i].get();
		}
	}

	return nullptr;
}

void DebriParticle::Emit(
	const size_t num,
	const Vector3& pos,
	ViewProjection* pVP)
{
	// �ŗL�ݒ�
	static const uint32_t kAliveFrame = 35;

	static const float kScaleVal = 0.25f;

	static const YMath::Vector3 kMinAccelVal = { 0.1f, 0.05f, 0.1f };
	static const YMath::Vector3 kMaxAccelVal = { 0.2f, 0.10f, 0.2f };

	static const float kMaxSpeedVal = 0.5f;

	static const float kEndAlpha = 0.6f;

	static const float kExponent = 6.0f;

	for (size_t i = 0; i < num; i++)
	{
		// ����ł���p�[�e�B�N���������� (�����Ȃ�e��)
		impl_DebriParticle* pParticle = DeadParticlePtr();
		if (pParticle == nullptr) { return; }

		Vector3 powerDirection = 
			YMath::GetRand(Vector3(-1.0f, -1.0f, -1.0f), Vector3(+1.0f, +1.0f, +1.0f), 100.0f);

		// �����_���ȉ����x�ŌX�̓�����ω�
		Vector3 accel = YMath::GetRand(kMinAccelVal, kMaxAccelVal, 100.0f);

		Vector3 maxSpeed = { kMaxSpeedVal, kMaxSpeedVal , kMaxSpeedVal };

		pParticle->Initialize(kAliveFrame, pos, kScaleVal, powerDirection, accel, maxSpeed, kEndAlpha, kExponent, pVP);
	}
}
