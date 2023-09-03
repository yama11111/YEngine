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
	YGame::Sprite2D* pNumberSpr2D = nullptr;
	YGame::Sprite3D* pNumberSpr3D = nullptr;
}

void UIDigit::StaticInitialize()
{
	Texture* pTex = Texture::Load("UI/numbers.png");

	pNumberSpr2D = Sprite2D::Create({ {"Texture0", pTex} });
	pNumberSpr3D = Sprite3D::Create({ {"Texture0", pTex} });
}

namespace YGame
{
	class impl_UIDigit final :
		public UIDigit
	{

	public:

		// スプライトの種類
		enum class SpriteType
		{
			eNone, e2D, e3D,
		};
	
	public:

		// 初期化
		void Initialize(
			const uint32_t num, 
			YMath::Matrix4* pParent, 
			const YMath::Vector3& offset = {},
			const bool isClearWhenTransition = true) override;

		// 初期化
		void Initialize(
			const uint32_t num,
			YMath::Matrix4* pParent,
			const bool isXAxisBillboard, const bool isYAxisBillboard,
			ViewProjection* pVP,
			const YMath::Vector3& offset = {},
			const bool isClearWhenTransition = true) override;

		// 更新
		void Update() override;

		// 描画
		void Draw(const std::string& shaderTag, const uint16_t priority) override;

		// 定数バッファ挿入
		void InsertConstBuffer(BaseConstBuffer* pCB) override;

		// 数設定
		void SetNumber(const uint32_t num) override;
		
		// オフセット設定
		void SetOffset(const YMath::Vector3& offset) override;

		// スプライト種類設定
		void SetSpriteType(const SpriteType& type) { type_ = type; }

	public:

		impl_UIDigit() = default;

		~impl_UIDigit() = default;

	private:

		// オブジェクト
		std::unique_ptr<BaseDrawObject> obj_;

		// オフセット
		Vector3 offset_;
		
		// 定数バッファ
		std::unique_ptr<ConstBufferObject<CBTexConfig>> cbTexConfig_;

		// スプライトタイプ
		SpriteType type_ = SpriteType::eNone;
	};

	void impl_UIDigit::Initialize(
		const uint32_t num, 
		YMath::Matrix4* pParent, 
		const YMath::Vector3& offset, 
		const bool isClearWhenTransition)
	{
		assert(type_ == SpriteType::e2D);
		assert(pParent);

		Transform::Status status = Transform::Status::Default();

		obj_.reset(DrawObjectForSprite2D::Create(status, pNumberSpr2D, isClearWhenTransition));

		obj_->SetParent(pParent);

		cbTexConfig_.reset(ConstBufferObject<CBTexConfig>::Create(isClearWhenTransition));
		obj_->InsertConstBuffer(cbTexConfig_.get());
		
		// 10分の1のサイズ分でスケール + タイリング
		obj_->transform_.scale_ = { 0.1f,1.0f,0.0f };
		cbTexConfig_->data_.tiling = Vector2(0.1f, 1.0f);

		SetNumber(num);

		SetOffset(offset);
	}

	void impl_UIDigit::Initialize(
		const uint32_t num, 
		YMath::Matrix4* pParent, 
		const bool isXAxisBillboard, const bool isYAxisBillboard, 
		ViewProjection* pVP, 
		const YMath::Vector3& offset, 
		const bool isClearWhenTransition)
	{
		assert(type_ == SpriteType::e3D);
		assert(pParent);

		Transform::Status status = Transform::Status::Default();

		obj_.reset(DrawObjectForSprite3D::Create(status, isXAxisBillboard, isYAxisBillboard, pVP, pNumberSpr3D, isClearWhenTransition));

		obj_->SetParent(pParent);

		cbTexConfig_.reset(ConstBufferObject<CBTexConfig>::Create(isClearWhenTransition));
		obj_->InsertConstBuffer(cbTexConfig_.get());

		// 10分の1のサイズ分でスケール + タイリング
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

		// 数に合わせてテクスチャのオフセット変える
		cbTexConfig_->data_.offset = Vector2(0.1f * static_cast<float>(num), 0.0f);
	}

	void impl_UIDigit::SetOffset(const YMath::Vector3& offset)
	{
		offset_ = offset;
	}
}

UIDigit* UIDigit::Create(
	const uint32_t num, 
	YMath::Matrix4* pParent, 
	const YMath::Vector3& offset, 
	const bool isClearWhenTransition)
{
	impl_UIDigit* newInstance = new impl_UIDigit();

	newInstance->SetSpriteType(impl_UIDigit::SpriteType::e2D);
	newInstance->Initialize(num, pParent, offset, isClearWhenTransition);

	return newInstance;
}

UIDigit* UIDigit::Create(
	const uint32_t num, 
	YMath::Matrix4* pParent, 
	const bool isXAxisBillboard, const bool isYAxisBillboard, 
	ViewProjection* pVP, const 
	YMath::Vector3& offset, 
	const bool isClearWhenTransition)
{
	impl_UIDigit* newInstance = new impl_UIDigit();

	newInstance->SetSpriteType(impl_UIDigit::SpriteType::e3D);
	newInstance->Initialize(num, pParent, isXAxisBillboard, isYAxisBillboard, pVP, offset, isClearWhenTransition);

	return newInstance;
}
