#include "Sprite2D.h"
#include <cassert>

#pragma region ���O���

using std::unique_ptr;
using YGame::Sprite2DObject;
using YGame::Sprite2D;
using YDX::PipelineSet;
using YMath::Vector2;
using YMath::Matrix4;

#pragma endregion

#pragma region ���[�g�p�����[�^�ԍ�

static const UINT TraIndex = static_cast<UINT>(Sprite2D::Pipeline::RootParameterIndex::TransformCB); // obj
static const UINT ColIndex = static_cast<UINT>(Sprite2D::Pipeline::RootParameterIndex::ColorCB); // color
static const UINT TexIndex = static_cast<UINT>(Sprite2D::Pipeline::RootParameterIndex::TexDT); // tex

#pragma endregion

#pragma region Static

std::vector<std::unique_ptr<Sprite2D>> Sprite2D::sprites_{};
YDX::PipelineSet Sprite2D::Pipeline::sPipelineSet_{};

#pragma endregion

#pragma region Sprite2D

Sprite2D* Sprite2D::Create(const Status& status, const TexStatus& texStatus)
{
	// �X�v���C�g����
	unique_ptr<Sprite2D> newSprite = std::make_unique<Sprite2D>();


	// �e�N�X�`���̃T�C�Y���擾
	float rscSizeX = static_cast<float>(texStatus.pTex_->Buffer()->GetDesc().Width);
	float rscSizeY = static_cast<float>(texStatus.pTex_->Buffer()->GetDesc().Height);

	// ----- Status ----- //

	// ���]�ݒ�
	float flipX = status.isFlipX_ ? -1.0f : 1.0f;
	float flipY = status.isFlipY_ ? -1.0f : 1.0f;

	// �T�C�Y��ݒ� (�摜�ɍ��킹��Ȃ炻�̂܂�)
	Vector2 size = status.isDiv_ ? Vector2(rscSizeX, rscSizeY) : status.size_;

	// ���E�㉺�̃|�C���g�ݒ� (0.0~1,0)
	float left   = (0.0f - status.anchor_.x_) * size.x_ * flipX;
	float right  = (1.0f - status.anchor_.x_) * size.x_ * flipX;
	float top    = (0.0f - status.anchor_.y_) * size.y_ * flipY;
	float bottom = (1.0f - status.anchor_.y_) * size.y_ * flipY;

	// ----- TexStatus ----- //

	// �e�N�X�`���̍���ƉE����ݒ� (�摜�ɍ��킹��Ȃ炻�̂܂�)
	Vector2 texLT = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_;
	Vector2 texRB = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : (texStatus.leftTop_ + texStatus.size_);

	// UV���W���v�Z
	float texLeft   = texLT.x_ / rscSizeX;
	float texRight  = texRB.x_ / rscSizeX;
	float texTop    = texLT.y_ / rscSizeY;
	float texBottom = texRB.y_ / rscSizeY;
	

	// �C���X�^���X���� (���I)
	newSprite->vt_.Initialize(
		{
			{ {  left,bottom,0.0f },{  texLeft,texBottom } }, // ����
			{ {  left,top,   0.0f },{  texLeft,texTop } },    // ����
			{ { right,bottom,0.0f },{ texRight,texBottom } }, // �E��
			{ { right,top,   0.0f },{ texRight,texTop } },    // �E��
		});

	// ���낢��ݒ�
	newSprite->size_    = status.size_; // �傫��
	newSprite->anchor_  = status.anchor_; // �A���J�[�|�C���g
	newSprite->isFlipX_ = status.isFlipX_; // X���]
	newSprite->isFlipY_ = status.isFlipY_; // Y���]

	newSprite->pTex_	   = texStatus.pTex_; // �e�N�X�`���C���f�b�N�X
	newSprite->texLeftTop_ = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_; // �e�N�X�`���̍���
	newSprite->texSize_	   = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : texStatus.size_; // �e�N�X�`���̑傫��


	// �|�C���^���l��
	Sprite2D* newSpritePtr = newSprite.get();

	// �X�v���C�g��ۑ�
	sprites_.push_back(std::move(newSprite));

	// �X�v���C�g�|�C���^��Ԃ�
	return newSpritePtr;
}

void Sprite2D::AllClear()
{
	// �X�v���C�g2D�S����
	for (size_t i = 0; i < sprites_.size(); i++)
	{
		sprites_[i].reset(nullptr);
	}
	sprites_.clear();
}

void Sprite2D::Draw(Sprite2DObject* pObj)
{
	// �`�悵�Ȃ��Ȃ�e��
	if (isInvisible_) { return; }

	// �萔�o�b�t�@���V�F�[�_�[�ɑ���
	pObj->SetDrawCommand(TraIndex, ColIndex);

	// �e�N�X�`��
	pTex_->SetDrawCommand(TexIndex);

	// ���_�o�b�t�@�𑗂� + �`��R�}���h
	vt_.Draw();
}

void Sprite2D::SetSize(const Vector2& size)
{
	if (size_ == size) { return; }
	SetAllStatus({ false, size, anchor_, isFlipX_, isFlipY_ }, { pTex_, false, texLeftTop_, texLeftTop_ });
}
void Sprite2D::SetAnchorPoint(const Vector2& anchor)
{
	if (anchor_ == anchor) { return; }
	SetAllStatus({ false, size_, anchor, isFlipX_, isFlipY_ }, { pTex_, false, texLeftTop_, texLeftTop_ });
}
void Sprite2D::SetFrip(const bool isFlipX, const bool isFlipY)
{
	if (isFlipX_ == isFlipX && isFlipY_ == isFlipY) { return; }
	SetAllStatus({ false, size_, anchor_, isFlipX, isFlipY }, { pTex_, false, texLeftTop_, texLeftTop_ });
}
void Sprite2D::SetTextureLeftTop(const Vector2& leftTop, const bool adjust)
{
	if (texLeftTop_ == leftTop) { return; }

	float adjX = adjust && (texLeftTop_.x_ < leftTop.x_) ? (leftTop.x_ - texLeftTop_.x_) : 0.0f;
	float adjY = adjust && (texLeftTop_.y_ < leftTop.y_) ? (leftTop.y_ - texLeftTop_.y_) : 0.0f;

	SetAllStatus({ false, size_, anchor_, isFlipX_, isFlipY_ }, { pTex_, false, leftTop, texSize_ - Vector2(adjX, adjY) });
}
void Sprite2D::SetTextureSize(const Vector2& texSize)
{
	if (texSize_ == texSize) { return; }
	SetAllStatus({ false, size_, anchor_, isFlipX_, isFlipY_ }, { pTex_, false, texLeftTop_, texSize });
}
void Sprite2D::SetTextureRectangle(const Vector2& leftTop, const Vector2& texSize)
{
	if (texLeftTop_ == leftTop && texSize_ == texSize) { return; }
	SetAllStatus({ false, size_, anchor_, isFlipX_, isFlipY_ }, { pTex_, false, leftTop, texSize });
}
void Sprite2D::SetAllStatus(const Status& status, const TexStatus& texStatus)
{
	// ���_�f�[�^
	std::vector<VData> v;

	// �e�N�X�`���̃T�C�Y���擾
	float rscSizeX = static_cast<float>(texStatus.pTex_->Buffer()->GetDesc().Width);
	float rscSizeY = static_cast<float>(texStatus.pTex_->Buffer()->GetDesc().Height);

	// ----- Status ----- //
	
	// ���]�ݒ�
	float flipX = status.isFlipX_ ? -1.0f : 1.0f;
	float flipY = status.isFlipY_ ? -1.0f : 1.0f;

	// �T�C�Y��ݒ� (�摜�ɍ��킹��Ȃ炻�̂܂�)
	Vector2 size = status.isDiv_ ? Vector2(rscSizeX, rscSizeY) : status.size_;

	// ���E�㉺�̃|�C���g�ݒ� (0.0~1,0)
	float left	 = (0.0f - status.anchor_.x_) * size.x_ * flipX;
	float right	 = (1.0f - status.anchor_.x_) * size.x_ * flipX;
	float top	 = (0.0f - status.anchor_.y_) * size.y_ * flipY;
	float bottom = (1.0f - status.anchor_.y_) * size.y_ * flipY;

	// ----- TexStatus ----- //

	// �e�N�X�`���̍���ƉE����ݒ� (�摜�ɍ��킹��Ȃ炻�̂܂�)
	Vector2 texLT = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_;
	Vector2 texRB = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : (texStatus.leftTop_ + texStatus.size_);

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
	size_	 = status.size_; // �傫��
	anchor_	 = status.anchor_; // �A���J�[�|�C���g
	isFlipX_ = status.isFlipX_; // X���]
	isFlipY_ = status.isFlipY_; // Y���]

	pTex_	    = texStatus.pTex_; // �e�N�X�`���C���f�b�N�X
	texLeftTop_ = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_; // �e�N�X�`���̍���
	texSize_    = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : texStatus.size_; // �e�N�X�`���̑傫��
}

#pragma endregion

#pragma region Pipeline

void Sprite2D::Pipeline::ShaderSet::Load()
{
	// �G���[�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	ID3DBlob* vs = nullptr;
	ID3DBlob* ps = nullptr;

	// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/Sprite2DVS.hlsl", "main", "vs_5_0", vs, errorBlob.Get());
	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/Sprite2DPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

	vsBlob_ = vs;
	psBlob_ = ps;
}

void Sprite2D::Pipeline::StaticInitialize()
{
	// �p�C�v���C���������p�ݒ�
	PipelineSet::InitStatus initStatus;


#pragma region �V�F�[�_�[�ǂݍ���

	ShaderSet shdrs;
	shdrs.Load();

#pragma endregion


#pragma region ���_���C�A�E�g�̐ݒ�

	initStatus.inputLayout_ =
	{
		// ���_���W	 (x, y, z)
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		// UV���W	 (x, y)
		{
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		}
	};

#pragma endregion


#pragma region �e�N�X�`���T���v���[�̐ݒ�

	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // ���܂�Ԃ�   (�^�C�����O)
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // �c�܂�Ԃ�   (�^�C�����O)
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // ���s�܂�Ԃ� (�^�C�����O)
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK; // �{�[�_�[�̎��͍�
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;   // �S�ă��j�A���
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX; // �~�j�}�b�v�ő�l
	samplerDesc.MinLOD = 0.0f;              // �~�j�}�b�v�ŏ��l
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // �s�N�Z���V�F�[�_�[����̂ݎg�p�\

	initStatus.samplerDescs_.push_back(samplerDesc);

#pragma endregion


#pragma region ���[�g�p�����[�^�̐ݒ�

	size_t rpIdxCBNum = static_cast<size_t> (RootParameterIndex::TexDT);

	for (size_t i = 0; i < rpIdxCBNum; i++)
	{
		// �萔�o�b�t�@
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // �萔�o�b�t�@�r���[
		rootParam.Descriptor.ShaderRegister = static_cast<UINT>(i); // �萔�o�b�t�@�ԍ�
		rootParam.Descriptor.RegisterSpace = 0;					  // �f�t�H���g�l
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

		initStatus.rootParams_.push_back(rootParam);
	}

	// �f�X�N���v�^�����W�̐ݒ�
	initStatus.descriptorRange_.NumDescriptors = 1; // 1�x�̕`��Ɏg���e�N�X�`����1���Ȃ̂�1
	initStatus.descriptorRange_.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	initStatus.descriptorRange_.BaseShaderRegister = 0; // �e�N�X�`�����W�X�^0��
	initStatus.descriptorRange_.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// �e�N�X�`�����W�X�^
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam.DescriptorTable.pDescriptorRanges = &initStatus.descriptorRange_;
	rootParam.DescriptorTable.NumDescriptorRanges = 1;
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

	initStatus.rootParams_.push_back(rootParam);

#pragma endregion


#pragma region �p�C�v���C���ݒ�

	// �V�F�[�_�[�̐ݒ�
	initStatus.pipelineDesc_.VS.pShaderBytecode = shdrs.vsBlob_.Get()->GetBufferPointer();
	initStatus.pipelineDesc_.VS.BytecodeLength  = shdrs.vsBlob_.Get()->GetBufferSize();
	initStatus.pipelineDesc_.PS.pShaderBytecode = shdrs.psBlob_.Get()->GetBufferPointer();
	initStatus.pipelineDesc_.PS.BytecodeLength  = shdrs.psBlob_.Get()->GetBufferSize();

	// ���X�^���C�U�̐ݒ�
	initStatus.pipelineDesc_.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // �w�ʂ��J�����O���Ȃ�

	// �f�v�X�X�e���V���X�e�[�g�̐ݒ�
	initStatus.pipelineDesc_.DepthStencilState.DepthEnable = false; // �[�x�e�X�g���Ȃ�
	initStatus.pipelineDesc_.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // ��ɏ㏑��

	// �}�`�̌`��ݒ�
	initStatus.pipelineDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

#pragma endregion


#pragma region �v���~�e�B�u�`��̐ݒ�

	initStatus.primitive_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; // �O�p�`�X�g���b�v

#pragma endregion


	// �p�C�v���C��������
	sPipelineSet_.Initialize(initStatus);

}

void Sprite2D::Pipeline::StaticSetDrawCommond()
{
	// �p�C�v���C�����Z�b�g
	sPipelineSet_.SetDrawCommand();
}

#pragma endregion