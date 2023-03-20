#include "Sprite2D.h"

#pragma region ���O���

using YGame::Sprite2DCommon;
using YGame::Sprite2D;
using YGame::ObjectSprite2D;
using YMath::Vector2;
using YMath::Matrix4;

#pragma endregion

#pragma region ���[�g�p�����[�^�ԍ�

static const UINT ObjIndex	 = static_cast<UINT>(Sprite2DCommon::RootParameterIndex::ObjCB); // obj
static const UINT ColIndex	 = static_cast<UINT>(Sprite2DCommon::RootParameterIndex::ColorCB); // color
static const UINT TexIndex	 = static_cast<UINT>(Sprite2DCommon::RootParameterIndex::TexDT); // tex

#pragma endregion

ObjectSprite2D* ObjectSprite2D::Create(const Status& state)
{
	// �C���X�^���X���� (���I)
	ObjectSprite2D* instance = new ObjectSprite2D();
	
	// �萔�o�b�t�@����
	instance->cBuff_.Create();
	// ������
	instance->Initialize(state);

	// �C���X�^���X��Ԃ�
	return instance;
}

void Sprite2D::Draw(ObjectSprite2D* pObj, Color* pColor, const UINT tex)
{
	// �`�悵�Ȃ��Ȃ�e��
	if (isInvisible_) { return; }

	// ----- �V�F�[�_�[�ɒ萔�o�b�t�@�𑗂� ----- //
	
	// �s��
	pObj->cBuff_.map_->matWorld_ = pObj->m_ * projection_;
	pObj->cBuff_.SetDrawCommand(ObjIndex);

	// �F
	pColor->SetDrawCommand(ColIndex);

	// �e�N�X�`��
	pTexManager_->SetDrawCommand(TexIndex, tex);
	
	// ���_�o�b�t�@�𑗂� + �`��R�}���h
	vt_.Draw();
}
void Sprite2D::Draw(ObjectSprite2D* pObj, const UINT tex)
{
	// �f�t�H���g�̐F��n���ĕ`��
	Draw(pObj, defColor_.get(), tex);
}
void Sprite2D::Draw(ObjectSprite2D* pObj, Color* pColor)
{
	// �`�悵�Ȃ��Ȃ�e��
	if (isInvisible_) { return; }

	// ----- �V�F�[�_�[�ɒ萔�o�b�t�@�𑗂� ----- //

	// �s��
	pObj->cBuff_.map_->matWorld_ = pObj->m_ * projection_;
	pObj->cBuff_.SetDrawCommand(ObjIndex);

	// �F
	pColor->SetDrawCommand(ColIndex);

	// �e�N�X�`��
	pTexManager_->SetDrawCommand(TexIndex, tex_);
	
	// ���_�o�b�t�@�𑗂� + �`��R�}���h
	vt_.Draw();
}
void Sprite2D::Draw(ObjectSprite2D* pObj)
{
	// �f�t�H���g�̐F��n���ĕ`��
	Draw(pObj, defColor_.get());
}

Sprite2D* Sprite2D::Create(const Status& state, const TexStatus& texState, const bool div)
{
	// �C���X�^���X
	Sprite2D* instance = new Sprite2D();
	
	// ----- Status ----- //

	// ���]�ݒ�
	float flipX = state.isFlipX_ ? -1.0f : 1.0f;
	float flipY = state.isFlipY_ ? -1.0f : 1.0f;

	// ���E�㉺�̃|�C���g�ݒ� (0.0~1,0)
	float left   = (0.0f - state.anchor_.x_) * state.size_.x_ * flipX;
	float right  = (1.0f - state.anchor_.x_) * state.size_.x_ * flipX;
	float top    = (0.0f - state.anchor_.y_) * state.size_.y_ * flipY;
	float bottom = (1.0f - state.anchor_.y_) * state.size_.y_ * flipY;

	// ----- TexStatus ----- //

	// �e�N�X�`���̃T�C�Y���擾
	float rscSizeX = static_cast<float>(pTexManager_->TextureBuffer(texState.index_)->GetDesc().Width);
	float rscSizeY = static_cast<float>(pTexManager_->TextureBuffer(texState.index_)->GetDesc().Height);

	// �e�N�X�`���̍���ƉE����ݒ� (�摜�ɍ��킹��Ȃ炻�̂܂�)
	Vector2 texLT = div ? texState.leftTop_ : Vector2(0.0f, 0.0f);
	Vector2 texRB = div ? (texState.leftTop_ + texState.size_) : Vector2(rscSizeX, rscSizeY);

	// UV���W���v�Z
	float texLeft   = texLT.x_ / rscSizeX;
	float texRight  = texRB.x_ / rscSizeX;
	float texTop    = texLT.y_ / rscSizeY;
	float texBottom = texRB.y_ / rscSizeY;
	

	// �C���X�^���X���� (���I)
	instance->vt_.Initialize(
		{
			{ {  left,bottom,0.0f },{  texLeft,texBottom } }, // ����
			{ {  left,top,   0.0f },{  texLeft,texTop } },    // ����
			{ { right,bottom,0.0f },{ texRight,texBottom } }, // �E��
			{ { right,top,   0.0f },{ texRight,texTop } },    // �E��
		});

	// ���낢��ݒ�
	instance->size_    = state.size_; // �傫��
	instance->anchor_  = state.anchor_; // �A���J�[�|�C���g
	instance->isFlipX_ = state.isFlipX_; // X���]
	instance->isFlipY_ = state.isFlipY_; // Y���]

	instance->tex_		  = texState.index_; // �e�N�X�`���C���f�b�N�X
	instance->texLeftTop_ = div ? texState.leftTop_ : Vector2(0.0f, 0.0f); // �e�N�X�`���̍���
	instance->texSize_    = div ? texState.size_ : Vector2(rscSizeX, rscSizeY); // �e�N�X�`���̑傫��

	instance->defColor_.reset(Color::Create()); // �F (���̂܂�)

	// �C���X�^���X��Ԃ�
	return instance;
}

void Sprite2D::SetSize(const Vector2& size)
{
	if (size_ == size) { return; }
	SetAllStatus({ size, anchor_, isFlipX_, isFlipY_ }, { tex_, texLeftTop_, texLeftTop_ });
}
void Sprite2D::SetAnchorPoint(const Vector2& anchor)
{
	if (anchor_ == anchor) { return; }
	SetAllStatus({ size_, anchor, isFlipX_, isFlipY_ }, { tex_, texLeftTop_, texLeftTop_ });
}
void Sprite2D::SetFrip(const bool isFlipX, const bool isFlipY)
{
	if (isFlipX_ == isFlipX && isFlipY_ == isFlipY) { return; }
	SetAllStatus({ size_, anchor_, isFlipX, isFlipY }, { tex_, texLeftTop_, texLeftTop_ });
}
void Sprite2D::SetTextureLeftTop(const Vector2& leftTop, const bool adjust)
{
	if (texLeftTop_ == leftTop) { return; }

	float adjX = adjust && (texLeftTop_.x_ < leftTop.x_) ? (leftTop.x_ - texLeftTop_.x_) : 0.0f;
	float adjY = adjust && (texLeftTop_.y_ < leftTop.y_) ? (leftTop.y_ - texLeftTop_.y_) : 0.0f;

	SetAllStatus({ size_, anchor_, isFlipX_, isFlipY_ }, { tex_, leftTop, texSize_ - Vector2(adjX, adjY) }, true);
}
void Sprite2D::SetTextureSize(const Vector2& texSize)
{
	if (texSize_ == texSize) { return; }
	SetAllStatus({ size_, anchor_, isFlipX_, isFlipY_ }, { tex_, texLeftTop_, texSize }, true);
}
void Sprite2D::SetTextureRectangle(const Vector2& leftTop, const Vector2& texSize)
{
	if (texLeftTop_ == leftTop && texSize_ == texSize) { return; }
	SetAllStatus({ size_, anchor_, isFlipX_, isFlipY_ }, { tex_, leftTop, texSize }, true);
}
void Sprite2D::SetAllStatus(const Status& state, const TexStatus& texState, const bool div)
{
	std::vector<VData> v;

	// ----- Status ----- //
	
	// ���]�ݒ�
	float flipX = state.isFlipX_ ? -1.0f : 1.0f;
	float flipY = state.isFlipY_ ? -1.0f : 1.0f;

	// ���E�㉺�̃|�C���g�ݒ� (0.0~1,0)
	float left = (0.0f - state.anchor_.x_) * state.size_.x_ * flipX;
	float right = (1.0f - state.anchor_.x_) * state.size_.x_ * flipX;
	float top = (0.0f - state.anchor_.y_) * state.size_.y_ * flipY;
	float bottom = (1.0f - state.anchor_.y_) * state.size_.y_ * flipY;

	// ----- TexStatus ----- //

	// �e�N�X�`���̃T�C�Y���擾
	float rscSizeX = static_cast<float>(pTexManager_->TextureBuffer(texState.index_)->GetDesc().Width);
	float rscSizeY = static_cast<float>(pTexManager_->TextureBuffer(texState.index_)->GetDesc().Height);

	// �e�N�X�`���̍���ƉE����ݒ� (�摜�ɍ��킹��Ȃ炻�̂܂�)
	Vector2 texLT = div ? texState.leftTop_ : Vector2(0.0f, 0.0f);
	Vector2 texRB = div ? (texState.leftTop_ + texState.size_) : Vector2(rscSizeX, rscSizeY);

	// UV���W���v�Z
	float texLeft   = texLT.x_ / rscSizeX;
	float texRight  = texRB.x_ / rscSizeX;
	float texTop    = texLT.y_ / rscSizeY;
	float texBottom = texRB.y_ / rscSizeY;


	// ���_���Đݒ�
	v.push_back({ {  left,bottom,0.0f },{  texLeft,texBottom } }); // ����
	v.push_back({ {  left,top,   0.0f },{  texLeft,texTop } });	   // ����
	v.push_back({ { right,bottom,0.0f },{ texRight,texBottom } }); // �E��
	v.push_back({ { right,top,   0.0f },{ texRight,texTop } });	   // �E��
	vt_.TransferMap(v);

	// ���낢��ݒ�
	size_ = state.size_; // �傫��
	anchor_ = state.anchor_; // �A���J�[�|�C���g
	isFlipX_ = state.isFlipX_; // X���]
	isFlipY_ = state.isFlipY_; // Y���]

	tex_ = texState.index_; // �e�N�X�`���C���f�b�N�X
	texLeftTop_ = div ? texState.leftTop_ : Vector2(0.0f, 0.0f); // �e�N�X�`���̍���
	texSize_ = div ? texState.size_ : Vector2(rscSizeX, rscSizeY); // �e�N�X�`���̑傫��
}
