#include "PostEffect.h"
#include "CalcTransform.h"
#include "YAssert.h"
#include "Def.h"

#pragma region ���O���

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::PostEffect;
using YDX::PipelineSet;
using YMath::Vector2;
using YMath::Matrix4;

#pragma endregion

#pragma region ���[�g�p�����[�^�ԍ�

static const UINT TraIndex = static_cast<UINT>(PostEffect::Pipeline::RootParameterIndex::eTransformCB); // transform
static const UINT ColIndex = static_cast<UINT>(PostEffect::Pipeline::RootParameterIndex::eColorCB); // color
static const UINT TexConfigIndex = static_cast<UINT>(PostEffect::Pipeline::RootParameterIndex::eTexConfigCB); // texConfig
static const UINT TexIndex = static_cast<UINT>(PostEffect::Pipeline::RootParameterIndex::eTexDT); // tex

#pragma endregion

#pragma region Static

vector<unique_ptr<PostEffect>> PostEffect::sPostEffects_{};
array<PipelineSet, PostEffect::Pipeline::sShaderNum_> PostEffect::Pipeline::sPipelineSets_{};
list<unique_ptr<PostEffect::Pipeline::DrawSet>> PostEffect::Pipeline::sDrawSets_;
ID3D12Device* PostEffect::spDevice_ = nullptr;
ID3D12GraphicsCommandList* PostEffect::spCmdList_ = nullptr;
YDX::ScreenDesc* PostEffect::spScreenDesc_ = nullptr;

#pragma endregion


#pragma region PostEffect

PostEffect* PostEffect::Create(const Status& status, const TexStatus& texStatus)
{
	// �X�v���C�g����
	unique_ptr<PostEffect> newSprite = std::make_unique<PostEffect>();


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

	// RTV������
	newSprite->CreateRTV();
	
	// �[�x�o�b�t�@����
	newSprite->CreateDepthBuff(newSprite->texSize_);
	
	// DSV������
	newSprite->CreateDSV();


	// �|�C���^���l��
	PostEffect* newSpritePtr = newSprite.get();

	// �X�v���C�g��ۑ�
	sPostEffects_.push_back(std::move(newSprite));

	// �X�v���C�g�|�C���^��Ԃ�
	return newSpritePtr;
}

void PostEffect::AllClear()
{
	// �X�v���C�g2D�S����
	for (size_t i = 0; i < sPostEffects_.size(); i++)
	{
		sPostEffects_[i].reset(nullptr);
	}
	sPostEffects_.clear();
}

void PostEffect::SetDrawCommand(PostEffect::Object* pObj, const ShaderType& shaderType)
{
	// �`��Z�b�g�}��
	Pipeline::StaticPushBackDrawSet(this, pObj, shaderType);
}

void PostEffect::StartRender()
{
	// ���\�[�X�o���A�ݒ�
	D3D12_RESOURCE_BARRIER barrierDesc{};
	barrierDesc.Transition.pResource = pTex_->Buffer(); // �e�N�X�`�����w��
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE; // �V�F�[�_�[���\�[�X ��Ԃ���
	barrierDesc.Transition.StateAfter  = D3D12_RESOURCE_STATE_RENDER_TARGET;  // �`�� ��Ԃ�

	// ���\�[�X�o���A��ύX
	spCmdList_->ResourceBarrier(1, &barrierDesc);

	// RTV�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap_->GetCPUDescriptorHandleForHeapStart();
	// DSV�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap_->GetCPUDescriptorHandleForHeapStart();
	
	// �����_�[�^�[�Q�b�g���Z�b�g
	spCmdList_->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	// �X�N���[���ݒ�̕`��R�}���h
	spScreenDesc_->SetDrawCommand();


	// ��ʃN���A
	//FLOAT clear[] = { ClearColor.r_,ClearColor.g_,ClearColor.b_,ClearColor.a_ };
	FLOAT clear[] = { 0.25f, 0.5f ,0.1f, 0.0f };
	spCmdList_->ClearRenderTargetView(rtvHandle, clear, 0, nullptr); // ���ۂ��F
	
	// �[�x�o�b�t�@�N���A
	spCmdList_->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void PostEffect::EndRender()
{
	// ���\�[�X�o���A�ݒ�
	D3D12_RESOURCE_BARRIER barrierDesc{};
	barrierDesc.Transition.pResource = pTex_->Buffer(); // �e�N�X�`�����w��
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // �`�� ��Ԃ���
	barrierDesc.Transition.StateAfter  = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE; // �V�F�[�_�[���\�[�X ��Ԃ�
	
	// ���\�[�X�o���A��߂�
	spCmdList_->ResourceBarrier(1, &barrierDesc);
}

void PostEffect::SetSize(const Vector2& size)
{
	if (size_ == size) { return; }
	SetAllStatus({ false, size, anchor_, isFlipX_, isFlipY_ }, { pTex_, false, texLeftTop_, texLeftTop_ });
}
void PostEffect::SetAnchorPoint(const Vector2& anchor)
{
	if (anchor_ == anchor) { return; }
	SetAllStatus({ false, size_, anchor, isFlipX_, isFlipY_ }, { pTex_, false, texLeftTop_, texLeftTop_ });
}
void PostEffect::SetFrip(const bool isFlipX, const bool isFlipY)
{
	if (isFlipX_ == isFlipX && isFlipY_ == isFlipY) { return; }
	SetAllStatus({ false, size_, anchor_, isFlipX, isFlipY }, { pTex_, false, texLeftTop_, texLeftTop_ });
}
void PostEffect::SetTextureLeftTop(const Vector2& leftTop, const bool adjust)
{
	if (texLeftTop_ == leftTop) { return; }

	float adjX = adjust && (texLeftTop_.x_ < leftTop.x_) ? (leftTop.x_ - texLeftTop_.x_) : 0.0f;
	float adjY = adjust && (texLeftTop_.y_ < leftTop.y_) ? (leftTop.y_ - texLeftTop_.y_) : 0.0f;

	SetAllStatus({ false, size_, anchor_, isFlipX_, isFlipY_ }, { pTex_, false, leftTop, texSize_ - Vector2(adjX, adjY) });
}
void PostEffect::SetTextureSize(const Vector2& texSize)
{
	if (texSize_ == texSize) { return; }
	SetAllStatus({ false, size_, anchor_, isFlipX_, isFlipY_ }, { pTex_, false, texLeftTop_, texSize });
}
void PostEffect::SetTextureRectangle(const Vector2& leftTop, const Vector2& texSize)
{
	if (texLeftTop_ == leftTop && texSize_ == texSize) { return; }
	SetAllStatus({ false, size_, anchor_, isFlipX_, isFlipY_ }, { pTex_, false, leftTop, texSize });
}
void PostEffect::SetAllStatus(const Status& status, const TexStatus& texStatus)
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

void PostEffect::SetIsVisible(const bool isVisible)
{
	isVisible_ = isVisible;
}

void PostEffect::CreateRTV()
{
	// �f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // �����_�[�^�[�Q�b�g�r���[
	rtvHeapDesc.NumDescriptors = 1;

	// �f�X�N���v�^�q�[�v����
	YDX::Result(spDevice_->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap_)));


	// �����_�[�^�[�Q�b�g�r���[�ݒ�
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	
	// �V�F�[�_�[�̌v�Z���ʂ�SRGB�ɕϊ����ď�������
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	
	// �����_�[�^�[�Q�b�g�r���[����
	spDevice_->CreateRenderTargetView(pTex_->Buffer(), &rtvDesc, rtvHeap_->GetCPUDescriptorHandleForHeapStart());
}

void PostEffect::CreateDepthBuff(const YMath::Vector2& size)
{
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC depthResDesc{};
	depthResDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthResDesc.Width = (UINT16)size.x_;
	depthResDesc.Height = (UINT)size.y_;
	depthResDesc.DepthOrArraySize = 1;
	depthResDesc.Format = DXGI_FORMAT_D32_FLOAT; // �[�x�l�t�H�[�}�b�g
	depthResDesc.SampleDesc.Count = 1;
	depthResDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL; // �f�v�X�X�e���V��

	// �[�x�l�p�q�[�v�v���p�e�B
	D3D12_HEAP_PROPERTIES depthHeapProp = {}; // �o�b�t�@�ݒ�
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;

	// �[�x�l�̃N���A�ݒ�
	D3D12_CLEAR_VALUE clearValue{}; // �[�x�l�̃N���A�ݒ�
	clearValue.DepthStencil.Depth = 1.0f; // �[�x�l1.0f(�ő�l)�ŃN���A
	clearValue.Format = DXGI_FORMAT_D32_FLOAT; // �[�x�l�t�H�[�}�b�g

	// �[�x�o�b�t�@����
	depthBuff_.Create(&depthHeapProp, &depthResDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &clearValue);
}

void PostEffect::CreateDSV()
{
	// �f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1; // �[�x�r���[��1��
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // �f�v�X�X�e���V���r���[
	
	// �[�x�r���[�p�f�X�N���v�^�[�q�[�v�쐬
	YDX::Result(spDevice_->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap_)));

	// �[�x�r���[�ݒ�
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT; // �[�x�l�t�H�[�}�b�g
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;

	// �[�x�r���[�쐬
	spDevice_->CreateDepthStencilView(
		depthBuff_.Get(),
		&dsvDesc,
		dsvHeap_->GetCPUDescriptorHandleForHeapStart());
}

void PostEffect::StaticInitialize(
	ID3D12Device* pDevice,
	ID3D12GraphicsCommandList* pCmdList,
	YDX::ScreenDesc* pScreenDesc)
{
	// null�`�F�b�N
	assert(pDevice);
	assert(pCmdList);
	assert(pScreenDesc);

	// ���
	spDevice_ = pDevice;
	spCmdList_ = pCmdList;
	spScreenDesc_ = pScreenDesc;
}

#pragma endregion


#pragma region Object

PostEffect::Object* PostEffect::Object::Create(
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

void PostEffect::Object::SetDrawCommand(
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

void PostEffect::Object::SetColor(CBColor* pColor)
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

void PostEffect::Object::SetTexConfig(CBTexConfig* pTexConfig)
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

Matrix4 PostEffect::Object::Default::sProjection_ = Matrix4::Identity();
unique_ptr<YGame::CBColor> PostEffect::Object::Default::sColor_ = nullptr;
unique_ptr<YGame::CBTexConfig> PostEffect::Object::Default::sTexConfig_ = nullptr;

void PostEffect::Object::Default::StaticInitialize()
{
	// �v���W�F�N�V�����s���ݒ�
	sProjection_ = YMath::MatOrthoGraphic();

	// ���� + ������ (�F)
	sColor_.reset(CBColor::Create({ 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));

	// ���� + ������ (�e�N�X�`���ݒ�)
	sTexConfig_.reset(CBTexConfig::Create({ 1.0f,1.0f }, {}, false));
}

#pragma endregion


#pragma region �V�F�[�_�[�ԍ�

static const UINT BloomIndex = static_cast<UINT>(PostEffect::ShaderType::eBloom);
static const UINT DefaultIndex = static_cast<UINT>(PostEffect::ShaderType::eDefault);

#pragma endregion


#pragma region Pipeline

void PostEffect::Pipeline::ShaderSet::Load()
{
	// �G���[�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	// Bloom
	{
		ID3DBlob* vs = nullptr;
		ID3DBlob* ps = nullptr;

		// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		LoadShader(L"Resources/Shaders/BloomVS.hlsl", "main", "vs_5_0", vs, errorBlob.Get());
		// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		LoadShader(L"Resources/Shaders/BloomPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		bloomVSBlob_ = vs;
		bloomPSBlob_ = ps;
	}

	// Default
	{
		ID3DBlob* vs = nullptr;
		ID3DBlob* ps = nullptr;

		// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		LoadShader(L"Resources/Shaders/PostEffectVS.hlsl", "main", "vs_5_0", vs, errorBlob.Get());
		// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		LoadShader(L"Resources/Shaders/PostEffectPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		defaultVSBlob_ = vs;
		defaultPSBlob_ = ps;
	}
}

void PostEffect::Pipeline::StaticInitialize()
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
	std::array<D3D12_GRAPHICS_PIPELINE_STATE_DESC, sPipelineSets_.size()> pipelineDescs{};

	// �V�F�[�_�[�̐ݒ�
	pipelineDescs[BloomIndex].VS.pShaderBytecode = shdrs.bloomVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[BloomIndex].VS.BytecodeLength = shdrs.bloomVSBlob_.Get()->GetBufferSize();
	pipelineDescs[BloomIndex].PS.pShaderBytecode = shdrs.bloomPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[BloomIndex].PS.BytecodeLength = shdrs.bloomPSBlob_.Get()->GetBufferSize();
	
	pipelineDescs[DefaultIndex].VS.pShaderBytecode = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[DefaultIndex].VS.BytecodeLength = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDescs[DefaultIndex].PS.pShaderBytecode = shdrs.defaultPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[DefaultIndex].PS.BytecodeLength = shdrs.defaultPSBlob_.Get()->GetBufferSize();

	// �p�C�v���C���̐�����
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// �T���v���}�X�N�̐ݒ�
		pipelineDescs[i].SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

		// ���X�^���C�U�̐ݒ�
		pipelineDescs[i].RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�
		pipelineDescs[i].RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����
		pipelineDescs[i].RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // �w�ʂ��J�����O���Ȃ�

		// �f�v�X�X�e���V���X�e�[�g�̐ݒ�
		pipelineDescs[i].DepthStencilState.DepthEnable = false; // �[�x�e�X�g���Ȃ�
		pipelineDescs[i].DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // ��ɏ㏑��

		// �u�����h�X�e�[�g
		D3D12_RENDER_TARGET_BLEND_DESC& blendDesc = pipelineDescs[i].BlendState.RenderTarget[0];
		blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA�S�Ẵ`�����l����`��

		blendDesc.BlendEnable = true;                // �u�����h��L���ɂ���
		blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD; // ���Z
		blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;   // �\�[�X�̒l��100%�g��
		blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO; // �f�X�g�̒l��  0%�g��
		
		if (i == BloomIndex)
		{
			// ���Z����
			blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // ���Z
			blendDesc.SrcBlend = D3D12_BLEND_ONE; // �\�[�X�̒l��100%�g��
			blendDesc.DestBlend = D3D12_BLEND_ONE; // �f�X�g�̒l��100%�g��
		}
		else
		{
			// ����������
			blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // ���Z
			blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA; // �\�[�X�̃A���t�@�l
			blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; // 1.0f - �\�[�X�̃A���t�@�l
		}

		// �}�`�̌`��ݒ�
		pipelineDescs[i].PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		// ���_���C�A�E�g�̐ݒ�
		pipelineDescs[i].InputLayout.pInputElementDescs = inputLayout.data(); // ���_���C�A�E�g�̐擪�A�h���X
		pipelineDescs[i].InputLayout.NumElements = (UINT)inputLayout.size(); // ���_���C�A�E�g��

		// ���̑��̐ݒ�
		pipelineDescs[i].NumRenderTargets = 1; // �`��Ώۂ�1��
		pipelineDescs[i].RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255�w���RGBA
		pipelineDescs[i].SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O
	}

#pragma endregion


#pragma region �v���~�e�B�u�`��̐ݒ�

	// �v���~�e�B�u�`��
	D3D_PRIMITIVE_TOPOLOGY primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; // �O�p�`�X�g���b�v

#pragma endregion


	// �p�C�v���C���̐�����
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// �p�C�v���C��������
		sPipelineSets_[i].Initialize(samplerDescs, rootParams, pipelineDescs[i], primitive);
	}

	// �N���A
	StaticClearDrawSet();
}

void PostEffect::Pipeline::StaticClearDrawSet()
{
	// ����Ȃ�
	if (sDrawSets_.empty())
	{
		// �N���A
		sDrawSets_.clear();
	}
}

void PostEffect::Pipeline::StaticPushBackDrawSet(
	PostEffect* pPostEffect, PostEffect::Object* pObj, 
	const ShaderType& shaderType)
{
	// �`��Z�b�g����
	unique_ptr<Pipeline::DrawSet> newDrawSet = std::make_unique<Pipeline::DrawSet>();

	// ������
	newDrawSet->pPostEffect_ = pPostEffect;
	newDrawSet->pObj_ = pObj;
	newDrawSet->pipelineIndex_ = static_cast<size_t>(shaderType);

	// �}��
	sDrawSets_.push_back(std::move(newDrawSet));
}

void PostEffect::Pipeline::StaticDraw()
{
	// �|�X�g�G�t�F�N�g�`��
	for (std::unique_ptr<DrawSet>& drawSet : sDrawSets_)
	{
		// �p�C�v���C�����Z�b�g
		sPipelineSets_[drawSet->pipelineIndex_].SetDrawCommand();

		// �`��
		drawSet->Draw();
	}
}

void PostEffect::Pipeline::DrawSet::Draw()
{
	// �`�悵�Ȃ��Ȃ�e��
	if (pPostEffect_->isVisible_ == false) { return; }

	// �萔�o�b�t�@���V�F�[�_�[�ɑ���
	pObj_->SetDrawCommand(TraIndex, ColIndex, TexConfigIndex);

	// �e�N�X�`��
	pPostEffect_->pTex_->SetDrawCommand(TexIndex);

	// ���_�o�b�t�@�𑗂� + �`��R�}���h
	pPostEffect_->vt_.Draw();
}

#pragma endregion
