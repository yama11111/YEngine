#include "PostEffect.h"
#include "MathVector.h"
#include "YAssert.h"
#include "Def.h"
#include <d3dx12.h>

#pragma region ���O���

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::PostEffect;
using YDX::PipelineSet;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Matrix4;

#pragma endregion

#pragma region ���[�g�p�����[�^�ԍ�

static const UINT TraIndex = static_cast<UINT>(PostEffect::Pipeline::RootParameterIndex::eTransformCB); // transform
static const UINT ColIndex = static_cast<UINT>(PostEffect::Pipeline::RootParameterIndex::eColorCB); // color
static const UINT TexConfigIndex = static_cast<UINT>(PostEffect::Pipeline::RootParameterIndex::eTexConfigCB); // texConfig
static const UINT Tex0Index = static_cast<UINT>(PostEffect::Pipeline::RootParameterIndex::eTex0DT); // tex0
static const UINT Tex1Index = static_cast<UINT>(PostEffect::Pipeline::RootParameterIndex::eTex1DT); // tex1

#pragma endregion

#pragma region Static

vector<unique_ptr<PostEffect>> PostEffect::sPostEffects_{};
array<PipelineSet, PostEffect::Pipeline::sShaderNum_> PostEffect::Pipeline::sPipelineSets_{};
list<unique_ptr<PostEffect::Pipeline::DrawSet>> PostEffect::Pipeline::sDrawSets_;
ID3D12Device* PostEffect::spDevice_ = nullptr;
ID3D12GraphicsCommandList* PostEffect::spCmdList_ = nullptr;
YDX::ScreenDesc PostEffect::sScreenDesc_{};

#pragma endregion


#pragma region PostEffect

PostEffect* PostEffect::Create()
{
	// �X�v���C�g����
	unique_ptr<PostEffect> newPostEffect = std::make_unique<PostEffect>();

	// ���_�o�b�t�@����
	newPostEffect->vt_.Initialize(
		{
			{ Vector3(       0.0f, +WinSize.y_, 0.0f), Vector2(0.0f, 1.0f) }, // ����
			{ Vector3(       0.0f,        0.0f, 0.0f), Vector2(0.0f, 0.0f) }, // ����
			{ Vector3(+WinSize.x_, +WinSize.y_, 0.0f), Vector2(1.0f, 1.0f) }, // �E��
			{ Vector3(+WinSize.x_,        0.0f, 0.0f), Vector2(1.0f, 0.0f) }, // �E��
		});

	for (size_t i = 0; i < newPostEffect->pTexs_.size(); i++)
	{
		// �����_�[�e�N�X�`������
		newPostEffect->pTexs_[i] = Texture::CreateRender();
	}

	// RTV������
	newPostEffect->CreateRTV();

	// �[�x�o�b�t�@����
	newPostEffect->CreateDepthBuff(WinSize);

	// DSV������
	newPostEffect->CreateDSV();

	// �|�C���^���l��
	PostEffect* newPostEffectPtr = newPostEffect.get();

	// �X�v���C�g��ۑ�
	sPostEffects_.push_back(std::move(newPostEffect));

	// �X�v���C�g�|�C���^��Ԃ�
	return newPostEffectPtr;
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
	for (size_t i = 0; i < pTexs_.size(); i++)
	{
		// ���\�[�X�o���A�ݒ�
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = pTexs_[i]->Buffer(); // �e�N�X�`�����w��
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE; // �V�F�[�_�[���\�[�X ��Ԃ���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;  // �`�� ��Ԃ�

		// ���\�[�X�o���A��ύX
		spCmdList_->ResourceBarrier(1, &barrierDesc);
	}

	// RTV�̃n���h�����擾
	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, kTextureNum_> rtvHandles{};
	
	for (size_t i = 0; i < rtvHandles.size(); i++)
	{
		rtvHandles[i] = 
			CD3DX12_CPU_DESCRIPTOR_HANDLE(
			rtvHeap_->GetCPUDescriptorHandleForHeapStart(), static_cast<INT>(i),
			spDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
	}
	
	// DSV�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap_->GetCPUDescriptorHandleForHeapStart();
	
	// �����_�[�^�[�Q�b�g���Z�b�g
	spCmdList_->OMSetRenderTargets(2, rtvHandles.data(), true, &dsvHandle);

	// �X�N���[���ݒ�̕`��R�}���h
	sScreenDesc_.SetDrawCommand();

	for (size_t i = 0; i < rtvHandles.size(); i++)
	{
		// ��ʃN���A
		//FLOAT clear[] = { ClearColor.r_,ClearColor.g_,ClearColor.b_,ClearColor.a_ };
		FLOAT clear[] = { 0.25f, 0.5f ,0.1f, 0.0f };
		spCmdList_->ClearRenderTargetView(rtvHandles[i], clear, 0, nullptr); // ���ۂ��F
	}
	
	// �[�x�o�b�t�@�N���A
	spCmdList_->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void PostEffect::EndRender()
{
	for (size_t i = 0; i < pTexs_.size(); i++)
	{
		// ���\�[�X�o���A�ݒ�
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = pTexs_[i]->Buffer(); // �e�N�X�`�����w��
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // �`�� ��Ԃ���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE; // �V�F�[�_�[���\�[�X ��Ԃ�

		// ���\�[�X�o���A��ύX
		spCmdList_->ResourceBarrier(1, &barrierDesc);
	}
}

void PostEffect::CreateRTV()
{
	// �f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // �����_�[�^�[�Q�b�g�r���[
	rtvHeapDesc.NumDescriptors = 2;

	// �f�X�N���v�^�q�[�v����
	YDX::Result(spDevice_->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap_)));


	// �����_�[�^�[�Q�b�g�r���[�ݒ�
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	
	// �V�F�[�_�[�̌v�Z���ʂ�SRGB�ɕϊ����ď�������
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	
	for (size_t i = 0; i < pTexs_.size(); i++)
	{
		// �����_�[�^�[�Q�b�g�r���[����
		spDevice_->CreateRenderTargetView(pTexs_[i]->Buffer(), &rtvDesc, 
			CD3DX12_CPU_DESCRIPTOR_HANDLE(
				rtvHeap_->GetCPUDescriptorHandleForHeapStart(), static_cast<INT>(i),
				spDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)));
	}
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
	ID3D12GraphicsCommandList* pCmdList)
{
	// null�`�F�b�N
	assert(pDevice);
	assert(pCmdList);

	// ���
	spDevice_ = pDevice;
	spCmdList_ = pCmdList;
	
	// �X�N���[���ݒ菉����
	sScreenDesc_.Initialize({ 0,0 }, WinSize, kTextureNum_);
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

static const UINT DefaultIndex			 = static_cast<UINT>(PostEffect::ShaderType::eDefault);
static const UINT ColorInversionIndex	 = static_cast<UINT>(PostEffect::ShaderType::eColorInversion);
static const UINT UVShiftBlurIndex		 = static_cast<UINT>(PostEffect::ShaderType::eUVShiftBlur);
static const UINT GaussianBlurIndex		 = static_cast<UINT>(PostEffect::ShaderType::eGaussianBlur);
static const UINT BloomIndex			 = static_cast<UINT>(PostEffect::ShaderType::eBloom);

#pragma endregion


#pragma region Pipeline

void PostEffect::Pipeline::ShaderSet::Load()
{
	// �G���[�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

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

	// ColorInversion
	{
		ID3DBlob* ps = nullptr;

		// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		LoadShader(L"Resources/Shaders/ColorInversionPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		colorInversionPSBlob_ = ps;
	}

	// UVShiftBlur
	{
		ID3DBlob* ps = nullptr;

		// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		LoadShader(L"Resources/Shaders/UVShiftBlurPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		uvShiftBlurPSBlob_ = ps;
	}

	// Gaussian
	{
		ID3DBlob* ps = nullptr;

		// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		LoadShader(L"Resources/Shaders/GaussianBlurPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		gaussianBlurPSBlob_ = ps;
	}

	// Bloom
	{
		ID3DBlob* ps = nullptr;

		// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		LoadShader(L"Resources/Shaders/BloomPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		bloomPSBlob_ = ps;
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

	// �������̈���m��
	rootParams.reserve(static_cast<size_t>(RootParameterIndex::eTex1DT) + 1);

	// �萔�o�b�t�@�̐�
	size_t rpIdxCBNum = static_cast<size_t>(RootParameterIndex::eTexConfigCB) + 1;

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

	// �f�X�N���v�^�e�[�u���̐�
	size_t rpIdxDTNum = static_cast<size_t>(RootParameterIndex::eTex1DT) - static_cast<size_t>(RootParameterIndex::eTexConfigCB);

	// �f�X�N���v�^�����W
	std::array<D3D12_DESCRIPTOR_RANGE, kTextureNum_> descriptorRanges{};

	// �f�X�N���v�^�e�[�u���̐�����
	for (size_t i = 0; i < rpIdxDTNum; i++)
	{
		// �f�X�N���v�^�����W�̐ݒ�
		descriptorRanges[i].NumDescriptors = 1; // 1�x�̕`��Ɏg���e�N�X�`����1���Ȃ̂�1
		descriptorRanges[i].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		descriptorRanges[i].BaseShaderRegister = static_cast<UINT>(i); // �e�N�X�`�����W�X�^�ԍ�
		descriptorRanges[i].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		// �e�N�X�`�����W�X�^
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootParam.DescriptorTable.pDescriptorRanges = &descriptorRanges[i];
		rootParam.DescriptorTable.NumDescriptorRanges = 1;
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

		// �z��ɑ}��
		rootParams.push_back(rootParam);
	}

#pragma endregion


#pragma region �p�C�v���C���ݒ�

	// �p�C�v���C���ݒ�
	std::array<D3D12_GRAPHICS_PIPELINE_STATE_DESC, sPipelineSets_.size()> pipelineDescs{};

	// �V�F�[�_�[�̐ݒ�	
	pipelineDescs[DefaultIndex].VS.pShaderBytecode			 = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[DefaultIndex].VS.BytecodeLength			 = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDescs[DefaultIndex].PS.pShaderBytecode			 = shdrs.defaultPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[DefaultIndex].PS.BytecodeLength			 = shdrs.defaultPSBlob_.Get()->GetBufferSize();

	pipelineDescs[ColorInversionIndex].VS.pShaderBytecode	 = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[ColorInversionIndex].VS.BytecodeLength	 = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDescs[ColorInversionIndex].PS.pShaderBytecode	 = shdrs.colorInversionPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[ColorInversionIndex].PS.BytecodeLength	 = shdrs.colorInversionPSBlob_.Get()->GetBufferSize();

	pipelineDescs[UVShiftBlurIndex].VS.pShaderBytecode		 = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[UVShiftBlurIndex].VS.BytecodeLength		 = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDescs[UVShiftBlurIndex].PS.pShaderBytecode		 = shdrs.uvShiftBlurPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[UVShiftBlurIndex].PS.BytecodeLength		 = shdrs.uvShiftBlurPSBlob_.Get()->GetBufferSize();

	pipelineDescs[GaussianBlurIndex].VS.pShaderBytecode		 = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[GaussianBlurIndex].VS.BytecodeLength		 = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDescs[GaussianBlurIndex].PS.pShaderBytecode		 = shdrs.gaussianBlurPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[GaussianBlurIndex].PS.BytecodeLength		 = shdrs.gaussianBlurPSBlob_.Get()->GetBufferSize();

	pipelineDescs[BloomIndex].VS.pShaderBytecode			 = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[BloomIndex].VS.BytecodeLength				 = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDescs[BloomIndex].PS.pShaderBytecode			 = shdrs.bloomPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[BloomIndex].PS.BytecodeLength				 = shdrs.bloomPSBlob_.Get()->GetBufferSize();

	// �p�C�v���C���̐�����
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// �T���v���}�X�N�̐ݒ�
		pipelineDescs[i].SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

		// ���X�^���C�U�̐ݒ�
		pipelineDescs[i].RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�
		pipelineDescs[i].RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����
		pipelineDescs[i].RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // �w�ʂ��J�����O

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

	// �e�N�X�`��0
	pPostEffect_->pTexs_[0]->SetDrawCommand(Tex0Index);
	
	// �e�N�X�`��1
	pPostEffect_->pTexs_[1]->SetDrawCommand(Tex1Index);

	// ���_�o�b�t�@�𑗂� + �`��R�}���h
	pPostEffect_->vt_.Draw();
}

#pragma endregion
