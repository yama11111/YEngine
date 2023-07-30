#include "DustParticle.h"
#include "BaseParticle.h"
#include "ParticleManager.h"
#include "DrawObjectForModel.h"
#include "ConstBufferObject.h"
#include "CBColor.h"
#include "MathUtil.h"
#include "Speed.h"
#include <memory>

using YGame::DustParticle;
using YMath::Vector3;

namespace YGame
{
	class impl_DustParticle final :
		public DustParticle,
		public BaseParticle
	{

	public:
		
		// ����
		static impl_DustParticle* Create();

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

		// �A���t�@�l�C�[�W���O
		YMath::Ease<float> alphaEas_;

	};

	impl_DustParticle* impl_DustParticle::Create()
	{
		impl_DustParticle* newParticle = new impl_DustParticle();

		DrawObjectForModel* newObj = DrawObjectForModel::Create({}, nullptr, nullptr, false);

		// �I�u�W�F�N�g�̃|�C���^��ێ�
		newParticle->pObj_ = newObj;
		newParticle->SetObject(newObj);

		newParticle->cbColor_.reset(ConstBufferObject<CBColor>::Create(false));

		return newParticle;
	}

	void impl_DustParticle::Initialize(
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
		
		pObj_->InsertConstBuffer(cbColor_.get());
		pObj_->SetViewProjection(pVP);

		scaleEas_.Initialize(endScale / 2.0f, endScale, exponent);

		speed_.Initialize(maxSpeed, acceleration, false);
		movePowerEas_.Initialize(power, {}, exponent);

		alphaEas_.Initialize(endAlpha, 0.0f, exponent);
	}

	void impl_DustParticle::Update()
	{
		if (isAlive_ == false) { return; }

		// �^�C�}�[�̊���
		float ratio = aliveTimer_.Ratio();

		// ���񂾂�x��
		speed_.Update(movePowerEas_.Out(ratio));
		obj_->transform_.pos_ += speed_.Velocity();
		
		// ���񂾂�傫��
		float scaleVal = scaleEas_.Out(ratio);
		obj_->transform_.scale_ = Vector3(scaleVal, scaleVal, scaleVal);

		// ���񂾂񔖂�
		cbColor_->data_.baseColor.a_ = alphaEas_.In(ratio);


		obj_->Update();
		
		BaseParticle::UpdateLife();
	}
}

// �p�[�e�B�N���ÓI�ɗp��
static const size_t skParticleNum = 100;
static std::array<std::unique_ptr<YGame::impl_DustParticle>, skParticleNum> sParticles;
static const std::string skTag = "DustParticle";
static bool sIsInit = false;

void DustParticle::StaticInitialize()
{
	if (sIsInit == false)
	{
		// ����
		for (size_t i = 0; i < sParticles.size(); i++)
		{
			sParticles[i].reset(impl_DustParticle::Create());
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

static YGame::impl_DustParticle* DeadParticlePtr()
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

void DustParticle::Emit(
	const size_t num,
	const Vector3& pos,
	const Vector3& powerDirection,
	ViewProjection* pVP)
{
	// �ŗL�ݒ�
	static const uint32_t kAliveFrame = 15;

	static const float kScaleVal = 0.25f;

	static const YMath::Vector3 kMinAccelVal = { 0.1f, 0.05f, 0.1f };
	static const YMath::Vector3 kMaxAccelVal = { 0.2f, 0.10f, 0.2f };

	static const float kMaxSpeedVal = 0.5f;

	static const float kEndAlpha = 0.6f;
	
	static const float kExponent = 3.0f;
	
	for (size_t i = 0; i < num; i++)
	{
		// ����ł���p�[�e�B�N���������� (�����Ȃ�e��)
		impl_DustParticle* pParticle = DeadParticlePtr();
		if (pParticle == nullptr) { return; }

		// �����_���ȉ����x�ŌX�̓�����ω�
		Vector3 accel = YMath::GetRand(kMinAccelVal, kMaxAccelVal, 100.0f);

		Vector3 maxSpeed = { kMaxSpeedVal, kMaxSpeedVal , kMaxSpeedVal };

		pParticle->Initialize(kAliveFrame, pos, kScaleVal, powerDirection, accel, maxSpeed, kEndAlpha, kExponent, pVP);
	}
}
