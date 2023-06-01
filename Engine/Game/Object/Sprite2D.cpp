#include "Sprite2D.h"
#include "CalcTransform.h"
#include <cassert>

#pragma region ���O���

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::Sprite2D;
using YDX::PipelineSet;
using YMath::Vector2;
using YMath::Matrix4;
using YGame::DrawLocation;
using YGame::DrawLocationNum;

#pragma endregion

#pragma region ���[�g�p�����[�^�ԍ�

static const UINT TraIndex = static_cast<UINT>(Sprite2D::Pipeline::RootParameterIndex::eTransformCB); // transform
static const UINT ColIndex = static_cast<UINT>(Sprite2D::Pipeline::RootParameterIndex::eColorCB); // color
static const UINT TexConfigIndex = static_cast<UINT>(Sprite2D::Pipeline::RootParameterIndex::eTexConfigCB); // texConfig
static const UINT TexIndex = static_cast<UINT>(Sprite2D::Pipeline::RootParameterIndex::eTexDT); // tex

#pragma endregion

#pragma region Static

vector<unique_ptr<Sprite2D>> Sprite2D::sSprites_{};
array<PipelineSet, Sprite2D::Pipeline::sShaderNum_> Sprite2D::Pipeline::sPipelineSets_{};
array<array<list<unique_ptr<Sprite2D::Pipeline::DrawSet>>,
	Sprite2D::Pipeline::sShaderNum_>, DrawLocationNum> Sprite2D::Pipeline::sDrawSets_;

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
	float left = (0.0f - status.anchor_.x_) * size.x_ * flipX;
	float right = (1.0f - status.anchor_.x_) * size.x_ * flipX;
	float top = (0.0f - status.anchor_.y_) * size.y_ * flipY;
	float bottom = (1.0f - status.anchor_.y_) * size.y_ * flipY;

	// ----- TexStatus ----- //

	// �e�N�X�`���̍���ƉE����ݒ� (�摜�ɍ��킹��Ȃ炻�̂܂�)
	Vector2 texLT = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_;
	Vector2 texRB = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : (texStatus.leftTop_ + texStatus.size_);

	// UV���W���v�Z
	float texLeft = texLT.x_ / rscSizeX;
	float texRight = texRB.x_ / rscSizeX;
	float texTop = texLT.y_ / rscSizeY;
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
	newSprite->size_ = status.size_; // �傫��
	newSprite->anchor_ = status.anchor_; // �A���J�[�|�C���g
	newSprite->isFlipX_ = status.isFlipX_; // X���]
	newSprite->isFlipY_ = status.isFlipY_; // Y���]

	newSprite->pTex_ = texStatus.pTex_; // �e�N�X�`���C���f�b�N�X
	newSprite->texLeftTop_ = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_; // �e�N�X�`���̍���
	newSprite->texSize_ = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : texStatus.size_; // �e�N�X�`���̑傫��


	// �|�C���^���l��
	Sprite2D* newSpritePtr = newSprite.get();

	// �X�v���C�g��ۑ�
	sSprites_.push_back(std::move(newSprite));

	// �X�v���C�g�|�C���^��Ԃ�
	return newSpritePtr;
}

void Sprite2D::AllClear()
{
	// �X�v���C�g2D�S����
	for (size_t i = 0; i < sSprites_.size(); i++)
	{
		sSprites_[i].reset(nullptr);
	}
	sSprites_.clear();
}

void Sprite2D::SetDrawCommand(Object* pObj, const DrawLocation& location, const ShaderType& shaderType)
{
	// �`��Z�b�g�}��
	Pipeline::StaticPushBackDrawSet(this, pObj, location, shaderType);
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
	float left = (0.0f - status.anchor_.x_) * size.x_ * flipX;
	float right = (1.0f - status.anchor_.x_) * size.x_ * flipX;
	float top = (0.0f - status.anchor_.y_) * size.y_ * flipY;
	float bottom = (1.0f - status.anchor_.y_) * size.y_ * flipY;

	// ----- TexStatus ----- //

	// �e�N�X�`���̍���ƉE����ݒ� (�摜�ɍ��킹��Ȃ炻�̂܂�)
	Vector2 texLT = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_;
	Vector2 texRB = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : (texStatus.leftTop_ + texStatus.size_);

	// UV���W���v�Z
	float texLeft = texLT.x_ / rscSizeX;
	float texRight = texRB.x_ / rscSizeX;
	float texTop = texLT.y_ / rscSizeY;
	float texBottom = texRB.y_ / rscSizeY;


	// ���_���Đݒ�
	v.push_back({ {  left,bottom,0.0f },{  texLeft,texBottom } }); // ����
	v.push_back({ {  left,top,   0.0f },{  texLeft,texTop } });	   // ����
	v.push_back({ { right,bottom,0.0f },{ texRight,texBottom } }); // �E��
	v.push_back({ { right,top,   0.0f },{ texRight,texTop } });	   // �E��
	vt_.TransferMap(v);

	// ���낢��ݒ�
	size_ = status.size_; // �傫��
	anchor_ = status.anchor_; // �A���J�[�|�C���g
	isFlipX_ = status.isFlipX_; // X���]
	isFlipY_ = status.isFlipY_; // Y���]

	pTex_ = texStatus.pTex_; // �e�N�X�`���C���f�b�N�X
	texLeftTop_ = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_; // �e�N�X�`���̍���
	texSize_ = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : texStatus.size_; // �e�N�X�`���̑傫��
}

void Sprite2D::SetIsVisible(const bool isVisible)
{
	isVisible_ = isVisible;
}

#pragma endregion


#pragma region Object

Sprite2D::Object* Sprite2D::Object::Create(
	const Status& status,
	CBColor* pColor,
	CBTexConfig* pTexConfig,
	const bool isMutable)
{
	// �C���X�^���X���� (���I)
	Object* instance = new Object();

	// �萔�o�b�t�@����
	instance->cBuff_.Create(isMutable);

	// ������(�f�t�H���g)
	instance->Initialize(status);
	instance->SetColor(pColor);
	instance->SetTexConfig(pTexConfig);

	// �C���X�^���X��Ԃ�
	return instance;
}

void Sprite2D::Object::SetDrawCommand(
	const UINT transformRPIndex,
	const UINT colorRPIndex,
	const UINT texConfigRPIndex)
{
	// �s��
	cBuff_.map_->matWorld_ = m_ * Default::sProjection_;
	cBuff_.SetDrawCommand(transformRPIndex);

	// �F
	pColor_->SetDrawCommand(colorRPIndex);

	// �e�N�X�`���ݒ�
	pTexConfig_->SetDrawCommand(texConfigRPIndex);
}

void Sprite2D::Object::SetColor(CBColor* pColor)
{
	// null�Ȃ�
	if (pColor == nullptr)
	{
		// �f�t�H���g���
		pColor_ = Default::sColor_.get();
		return;
	}

	// ���
	pColor_ = pColor;
}

void Sprite2D::Object::SetTexConfig(CBTexConfig* pTexConfig)
{
	// null�Ȃ�
	if (pTexConfig == nullptr)
	{
		// �f�t�H���g���
		pTexConfig_ = Default::sTexConfig_.get();
		return;
	}

	// ���
	pTexConfig_ = pTexConfig;
}

Matrix4 Sprite2D::Object::Default::sProjection_ = Matrix4::Identity();
unique_ptr<YGame::CBColor> Sprite2D::Object::Default::sColor_ = nullptr;
unique_ptr<YGame::CBTexConfig> Sprite2D::Object::Default::sTexConfig_ = nullptr;

void Sprite2D::Object::Default::StaticInitialize()
{
	// �v���W�F�N�V�����s���ݒ�
	sProjection_ = YMath::MatOrthoGraphic();

	// ���� + ������ (�F)
	sColor_.reset(CBColor::Create({ 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));

	// ���� + ������ (�e�N�X�`���ݒ�)
	sTexConfig_.reset(CBTexConfig::Create({ 1.0f,1.0f }, {}, false));
}

#pragma endregion


#pragma region Pipeline

void Sprite2D::Pipeline::ShaderSet::Load()
{
	// �G���[�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	// Default
	{
		ID3DBlob* vs = nullptr;
		ID3DBlob* ps = nullptr;

		// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		LoadShader(L"Resources/Shaders/Sprite2DVS.hlsl", "main", "vs_5_0", vs, errorBlob.Get());
		// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		LoadShader(L"Resources/Shaders/Sprite2DPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		defaultVSBlob_ = vs;
		defaultPSBlob_ = ps; 
	}
}

void Sprite2D::Pipeline::StaticInitialize()
{

#pragma region �V�F�[�_�[�ǂݍ���

	// �V�F�[�_�[
	ShaderSet shdrs;

	// �ǂݍ���
	shdrs.Load();

#pragma endregion


#pragma region ���_���C�A�E�g�̐ݒ�

	// ���_���C�A�E�g
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout =
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

	// �e�N�X�`���T���v���[�z��
	std::vector<D3D12_STATIC_SAMPLER_DESC> samplerDescs;

	// �e�N�X�`���T���v���[�̐ݒ�
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

	// �e�N�X�`���T���v���[�z��ɑ}��
	samplerDescs.push_back(samplerDesc);

#pragma endregion


#pragma region ���[�g�p�����[�^�̐ݒ�

	// ���[�g�p�����[�^
	std::vector<D3D12_ROOT_PARAMETER> rootParams;

	// �萔�o�b�t�@�̐�
	size_t rpIdxCBNum = static_cast<size_t> (RootParameterIndex::eTexDT);

	// �萔�o�b�t�@�̐�����
	for (size_t i = 0; i < rpIdxCBNum; i++)
	{
		// �萔�o�b�t�@
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // �萔�o�b�t�@�r���[
		rootParam.Descriptor.ShaderRegister = static_cast<UINT>(i); // �萔�o�b�t�@�ԍ�
		rootParam.Descriptor.RegisterSpace = 0;					  // �f�t�H���g�l
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

		// �z��ɑ}��
		rootParams.push_back(rootParam);
	}

	// �f�X�N���v�^�����W�̐ݒ�
	D3D12_DESCRIPTOR_RANGE descriptorRange{};
	descriptorRange.NumDescriptors = 1; // 1�x�̕`��Ɏg���e�N�X�`����1���Ȃ̂�1
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0; // �e�N�X�`�����W�X�^0��
	descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// �e�N�X�`�����W�X�^
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam.DescriptorTable.pDescriptorRanges = &descriptorRange;
	rootParam.DescriptorTable.NumDescriptorRanges = 1;
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

	// �z��ɑ}��
	rootParams.push_back(rootParam);

#pragma endregion


#pragma region �p�C�v���C���ݒ�

	// �p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	// �V�F�[�_�[�̐ݒ�
	pipelineDesc.VS.pShaderBytecode	 = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength	 = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode	 = shdrs.defaultPSBlob_.Get()->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength	 = shdrs.defaultPSBlob_.Get()->GetBufferSize();

	// �T���v���}�X�N�̐ݒ�
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

	// ���X�^���C�U�̐ݒ�
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�
	pipelineDesc.RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // �w�ʂ��J�����O���Ȃ�

	// �f�v�X�X�e���V���X�e�[�g�̐ݒ�
	pipelineDesc.DepthStencilState.DepthEnable = false; // �[�x�e�X�g���Ȃ�
	pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // ��ɏ㏑��

	// �u�����h�X�e�[�g
	D3D12_RENDER_TARGET_BLEND_DESC& blendDesc = pipelineDesc.BlendState.RenderTarget[0];
	blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA�S�Ẵ`�����l����`��

	blendDesc.BlendEnable = true;                // �u�����h��L���ɂ���
	blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD; // ���Z
	blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;   // �\�[�X�̒l��100%�g��
	blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO; // �f�X�g�̒l��  0%�g��

	// ����������
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD;			 // ���Z
	blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;      // �\�[�X�̃A���t�@�l
	blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; // 1.0f - �\�[�X�̃A���t�@�l

	// �}�`�̌`��ݒ�
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	// ���_���C�A�E�g�̐ݒ�
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout.data(); // ���_���C�A�E�g�̐擪�A�h���X
	pipelineDesc.InputLayout.NumElements = (UINT)inputLayout.size(); // ���_���C�A�E�g��

	// ���̑��̐ݒ�
	pipelineDesc.NumRenderTargets = 1; // �`��Ώۂ�1��
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255�w���RGBA
	pipelineDesc.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

#pragma endregion


#pragma region �v���~�e�B�u�`��̐ݒ�

	// �v���~�e�B�u�`��
	D3D_PRIMITIVE_TOPOLOGY primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; // �O�p�`�X�g���b�v

#pragma endregion


	//// �p�C�v���C���̐�����
	//for (size_t i = 0; i < sPipelineSets_.size(); i++)
	//{
	//	// �p�C�v���C��������
	//	sPipelineSets_[i].Initialize(samplerDescs, rootParams, pipelineDesc, primitive);
	//}

	sPipelineSets_[0].Initialize(samplerDescs, rootParams, pipelineDesc, primitive);

	// �`��ꏊ�̐�����
	for (size_t i = 0; i < sDrawSets_.size(); i++)
	{
		// �ϊ�
		DrawLocation location = static_cast<DrawLocation>(i);

		// �N���A
		StaticClearDrawSet(location);
	}
}

void Sprite2D::Pipeline::StaticClearDrawSet(const DrawLocation& location)
{
	// �C���f�b�N�X�ɕϊ�
	size_t index = static_cast<size_t>(location);

	// �p�C�v���C���̐�����
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// ����Ȃ�
		if (sDrawSets_[index][i].empty() == false)
		{
			// �N���A
			sDrawSets_[index][i].clear();
		}
	}
}

void Sprite2D::Pipeline::StaticPushBackDrawSet(
	Sprite2D* pSprite2D, Sprite2D::Object* pObj, 
	const DrawLocation& location, const ShaderType& shaderType)
{
	// �`��Z�b�g����
	unique_ptr<Pipeline::DrawSet> newDrawSet = std::make_unique<Pipeline::DrawSet>();

	// ������
	newDrawSet->pSprite2D_ = pSprite2D;
	newDrawSet->pObj_ = pObj;

	// �C���f�b�N�X�ɕϊ�
	size_t locationIdx = static_cast<size_t>(location);

	// �C���f�b�N�X�ɕϊ�
	size_t shaderIdx = static_cast<size_t>(shaderType);

	// �}��
	sDrawSets_[locationIdx][shaderIdx].push_back(std::move(newDrawSet));
}

void Sprite2D::Pipeline::StaticDraw(const DrawLocation& location)
{
	// �C���f�b�N�X�ɕϊ�
	size_t index = static_cast<size_t>(location);

	// �p�C�v���C���̐�����
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// �p�C�v���C�����Z�b�g
		sPipelineSets_[i].SetDrawCommand();

		// ���f���`��
		for (std::unique_ptr<DrawSet>& drawSet : sDrawSets_[index][i])
		{
			// �`��
			drawSet->Draw();
		}
	}
}

void Sprite2D::Pipeline::DrawSet::Draw()
{
	// �`�悵�Ȃ��Ȃ�e��
	if (pSprite2D_->isVisible_ == false) { return; }

	// �萔�o�b�t�@���V�F�[�_�[�ɑ���
	pObj_->SetDrawCommand(TraIndex, ColIndex, TexConfigIndex);

	// �e�N�X�`��
	pSprite2D_->pTex_->SetDrawCommand(TexIndex);

	// ���_�o�b�t�@�𑗂� + �`��R�}���h
	pSprite2D_->vt_.Draw();
}

#pragma endregion