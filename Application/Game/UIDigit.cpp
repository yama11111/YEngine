#include "UIDigit.h"
#include "DrawObjectForSprite2D.h"
#include "ConstBufferObject.h"
#include "CBTexConfig.h"
#include <cassert>

using YGame::UIDigit;
using YMath::Vector2;
using YMath::Vector3;

namespace
{
	YGame::Sprite2D* pNumberSpr = nullptr;
}

void UIDigit::StaticInitialize()
{
	pNumberSpr = Sprite2D::Create({ {"Texture0", Texture::Load("UI/numbers.png")} });
}

const float UIDigit::StaticDigitWidth()
{
	return 64.0f;
}

namespace YGame
{
	class impl_UIDigit final :
		public UIDigit
	{

	public:

		// ������
		void Initialize(
			const uint32_t num, 
			YMath::Matrix4* pParent, 
			const YMath::Vector3& offset = {},
			const bool isClearWhenTransition = true) override;

		// �X�V
		void Update() override;

		// �`��
		void Draw(const std::string& shaderTag, const uint16_t priority) override;

		// �萔�o�b�t�@�}��
		void InsertConstBuffer(BaseConstBuffer* pCB) override;

		// ���ݒ�
		void SetNumber(const uint32_t num) override;

		// �I�t�Z�b�g�ݒ�
		void SetOffset(const YMath::Vector3& offset) override;

	public:

		impl_UIDigit() = default;

		~impl_UIDigit() = default;

	private:

		// �I�u�W�F�N�g
		std::unique_ptr<BaseDrawObject> obj_;

		// �I�t�Z�b�g
		Vector3 offset_;
		
		// �萔�o�b�t�@
		std::unique_ptr<ConstBufferObject<CBTexConfig>> cbTexConfig_;

	};

	void impl_UIDigit::Initialize(
		const uint32_t num, 
		YMath::Matrix4* pParent, const YMath::Vector3& offset, 
		const bool isClearWhenTransition)
	{
		assert(pParent);

		Transform::Status status = Transform::Status::Default();

		obj_.reset(DrawObjectForSprite2D::Create(status, pNumberSpr));

		obj_->SetParent(pParent);

		cbTexConfig_.reset(ConstBufferObject<CBTexConfig>::Create(isClearWhenTransition));
		obj_->InsertConstBuffer(cbTexConfig_.get());
		
		// 10����1�̃T�C�Y���ŃX�P�[�� + �^�C�����O
		obj_->transform_.scale_ = { 0.1f,1.0f,0.0f };
		cbTexConfig_->data_.tiling = Vector2(0.1f, 1.0f);

		SetNumber(num);

		SetOffset(offset);
	}

	void impl_UIDigit::Update()
	{
		obj_->Update({ offset_, {}, {} });
	}

	void impl_UIDigit::Draw(const std::string& shaderTag, const uint16_t priority)
	{
		obj_->Draw(shaderTag, priority);
	}
	
	void impl_UIDigit::InsertConstBuffer(BaseConstBuffer* pCB)
	{
		obj_->InsertConstBuffer(pCB);
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

UIDigit* UIDigit::Create(
	const uint32_t num, 
	YMath::Matrix4* pParent, const YMath::Vector3& offset, 
	const bool isClearWhenTransition)
{
	impl_UIDigit* newInstance = new impl_UIDigit();

	newInstance->Initialize(num, pParent, offset, isClearWhenTransition);

	return newInstance;
}
