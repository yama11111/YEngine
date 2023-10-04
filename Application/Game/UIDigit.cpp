#include "UIDigit.h"
#include "DrawObjectForSprite2D.h"
#include "DrawObjectForSprite3D.h"
#include "ConstBufferObject.h"
#include "CBTexConfig.h"
#include <cassert>

using YGame::UIDigit;
using YMath::Vector2;
using YMath::Vector3;

namespace
{
	YGame::Texture* pTex = nullptr;
	YGame::Sprite2D* pNumberSpr2D = nullptr;
	YGame::Sprite3D* pNumberSpr3D = nullptr;
}

void UIDigit::LoadResource()
{
	pTex = Texture::Load("UI/numbers.png");

	pNumberSpr2D = Sprite2D::Create({ {"Texture0", pTex} });
	pNumberSpr3D = Sprite3D::Create({ {"Texture0", pTex} });
}

namespace YGame
{
	class impl_UIDigit final :
		public UIDigit
	{

	public:

		// �X�v���C�g�̎��
		enum class SpriteType
		{
			eNone, e2D, e3D,
		};
	
	public:

		// ������
		void Initialize2D(
			const uint32_t num, 
			YMath::Matrix4* pParent, 
			const YMath::Vector3& offset = {},
			const bool isClearWhenTransition = true) override;

		// ������
		void Initialize3D(
			const uint32_t num,
			YMath::Matrix4* pParent,
			const bool isXAxisBillboard, const bool isYAxisBillboard,
			ViewProjection* pVP,
			const YMath::Vector3& offset = {},
			const bool isClearWhenTransition = true) override;

		// �X�V
		void Update(const Transform::Status& status = {}) override;

		// �`��
		void Draw(const std::string& shaderTag, const uint16_t priority) override;

		// �萔�o�b�t�@�}��
		void InsertConstBuffer(BaseConstBuffer* pCB) override;

		// ���ݒ�
		void SetNumber(const uint32_t num) override;
		
		// �I�t�Z�b�g�ݒ�
		void SetOffset(const YMath::Vector3& offset) override;

		// �X�v���C�g��ސݒ�
		void SetSpriteType(const SpriteType& type) { type_ = type; }

	public:

		impl_UIDigit() = default;

		~impl_UIDigit() = default;

	private:

		// �I�u�W�F�N�g
		std::unique_ptr<DrawObjectForSprite2D> obj2D_;
		std::unique_ptr<DrawObjectForSprite3D> obj3D_;

		// �I�t�Z�b�g
		Vector3 offset_;
		
		// �萔�o�b�t�@
		std::unique_ptr<ConstBufferObject<CBTexConfig>> cbTexConfig_;

		// �X�v���C�g�^�C�v
		SpriteType type_ = SpriteType::eNone;

		// �J�ڎ��N���A�t���O
		bool isClearWhenTransition_ = false;
	};

	void impl_UIDigit::Initialize2D(
		const uint32_t num, 
		YMath::Matrix4* pParent, 
		const YMath::Vector3& offset, 
		const bool isClearWhenTransition)
	{
		assert(pParent);

		Transform::Status status = Transform::Status::Default();

		if (type_ != SpriteType::e2D ||
			obj2D_ == nullptr || 
			isClearWhenTransition_ != isClearWhenTransition)
		{
			obj2D_.reset(DrawObjectForSprite2D::Create(
				status, pNumberSpr2D, isClearWhenTransition));
		}
		else
		{
			obj2D_->Initialize(status, isClearWhenTransition);
		}

		obj2D_->SetParent(pParent);

		if (cbTexConfig_ == nullptr ||
			isClearWhenTransition_ != isClearWhenTransition)
		{
			cbTexConfig_.reset(ConstBufferObject<CBTexConfig>::Create(isClearWhenTransition));
		}

		obj2D_->InsertConstBuffer(cbTexConfig_.get());
		
		// 10����1�̃T�C�Y���ŃX�P�[�� + �^�C�����O
		obj2D_->transform_.scale_ = { 0.1f,1.0f,0.0f };
		cbTexConfig_->data_.tiling = Vector2(0.1f, 1.0f);

		SetNumber(num);

		SetOffset(offset);

		SetSpriteType(SpriteType::e2D);

		isClearWhenTransition_ = isClearWhenTransition;
	}

	void impl_UIDigit::Initialize3D(
		const uint32_t num, 
		YMath::Matrix4* pParent, 
		const bool isXAxisBillboard, const bool isYAxisBillboard, 
		ViewProjection* pVP, 
		const YMath::Vector3& offset, 
		const bool isClearWhenTransition)
	{
		assert(pParent);

		Transform::Status status = Transform::Status::Default();

		if (type_ != SpriteType::e3D ||
			obj3D_ == nullptr ||
			isClearWhenTransition_ != isClearWhenTransition)
		{
			obj3D_.reset(DrawObjectForSprite3D::Create(
				status, isXAxisBillboard, isYAxisBillboard, pVP, pNumberSpr3D, isClearWhenTransition));
		}
		else
		{
			obj3D_->Initialize(status, isClearWhenTransition);
			obj3D_->SetBillboardFrag(isXAxisBillboard, isYAxisBillboard);
			obj3D_->SetViewProjection(pVP);
		}

		obj3D_->SetParent(pParent);

		if (cbTexConfig_ == nullptr ||
			isClearWhenTransition_ != isClearWhenTransition)
		{
			cbTexConfig_.reset(ConstBufferObject<CBTexConfig>::Create(isClearWhenTransition));
		}

		obj3D_->InsertConstBuffer(cbTexConfig_.get());

		// �e�N�X�`���̃T�C�Y���擾
		float rscSizeX = static_cast<float>(pTex->Buffer()->GetDesc().Width) / 10.0f;
		float rscSizeY = static_cast<float>(pTex->Buffer()->GetDesc().Height);
		
		// 10����1�̃T�C�Y���ŃX�P�[�� + �^�C�����O
		obj3D_->transform_.scale_ = Vector3(rscSizeX, rscSizeY, 0.0f) / 100.0f;
		cbTexConfig_->data_.tiling = Vector2(0.1f, 1.0f);

		SetNumber(num);

		SetOffset(offset);

		SetSpriteType(SpriteType::e3D);

		isClearWhenTransition_ = isClearWhenTransition;
	}

	void impl_UIDigit::Update(const Transform::Status& status)
	{
		Transform::Status s = status;
		s.pos_ += offset_;

		if (type_ == SpriteType::e2D)
		{
			obj2D_->Update(s);
		}
		else if (type_ == SpriteType::e3D)
		{
			obj3D_->Update(s);
		}
	}

	void impl_UIDigit::Draw(const std::string& shaderTag, const uint16_t priority)
	{
		if (type_ == SpriteType::e2D)
		{
			obj2D_->Draw(shaderTag, priority);
		}
		else if (type_ == SpriteType::e3D)
		{
			obj3D_->Draw(shaderTag, priority);
		}
	}
	
	void impl_UIDigit::InsertConstBuffer(BaseConstBuffer* pCB)
	{
		if (type_ == SpriteType::e2D)
		{
			obj2D_->InsertConstBuffer(pCB);
		}
		else if (type_ == SpriteType::e3D)
		{
			obj3D_->InsertConstBuffer(pCB);
		}
	}

	void impl_UIDigit::SetNumber(const uint32_t num)
	{
		assert(0 <= num && num <= 9);

		// ���ɍ��킹�ăe�N�X�`���̃I�t�Z�b�g�ς���
		cbTexConfig_->data_.offset = Vector2(0.1f * static_cast<float>(num), 0.0f);
	}

	void impl_UIDigit::SetOffset(const YMath::Vector3& offset)
	{
		offset_ = offset;
	}
}

UIDigit* UIDigit::Create2D(
	const uint32_t num, 
	YMath::Matrix4* pParent, 
	const YMath::Vector3& offset, 
	const bool isClearWhenTransition)
{
	impl_UIDigit* newInstance = new impl_UIDigit();

	newInstance->Initialize2D(num, pParent, offset, isClearWhenTransition);

	return newInstance;
}

UIDigit* UIDigit::Create3D(
	const uint32_t num, 
	YMath::Matrix4* pParent, 
	const bool isXAxisBillboard, const bool isYAxisBillboard, 
	ViewProjection* pVP, const 
	YMath::Vector3& offset, 
	const bool isClearWhenTransition)
{
	impl_UIDigit* newInstance = new impl_UIDigit();

	newInstance->Initialize3D(num, pParent, isXAxisBillboard, isYAxisBillboard, pVP, offset, isClearWhenTransition);

	return newInstance;
}
