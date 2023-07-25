#include "PostEffect.h"
#include "MathVector.h"
#include "YAssert.h"
#include "Def.h"
#include <d3dx12.h>
#include <array>

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::PostEffect;
using YGame::PipelineSetting;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Matrix4;

vector<unique_ptr<PostEffect>> PostEffect::sPostEffects_{};
ID3D12Device* PostEffect::spDevice_ = nullptr;
ID3D12GraphicsCommandList* PostEffect::spCmdList_ = nullptr;

PostEffect* PostEffect::Create(const size_t rtvNum)
{
	unique_ptr<PostEffect> newPostEffect = std::make_unique<PostEffect>();

	// ���_�o�b�t�@����
	newPostEffect->vt_.Initialize(
		{
			{ Vector3(0.0f,        +WinSize.y_, 0.0f), Vector2(0.0f, 1.0f) }, // ����
			{ Vector3(0.0f,               0.0f, 0.0f), Vector2(0.0f, 0.0f) }, // ����
			{ Vector3(+WinSize.x_, +WinSize.y_, 0.0f), Vector2(1.0f, 1.0f) }, // �E��
			{ Vector3(+WinSize.x_,        0.0f, 0.0f), Vector2(1.0f, 0.0f) }, // �E��
		});

	// �����_�[�e�N�X�`������
	for (size_t i = 0; i < rtvNum; i++)
	{
		Texture* pTex = Texture::CreateRender();
		
		newPostEffect->pTexs_.emplace_back(pTex);
	}

	newPostEffect->CreateRTV();

	newPostEffect->CreateDepthBuff(WinSize);

	newPostEffect->CreateDSV();

	newPostEffect->phase_ = Phase::None;
	
	newPostEffect->screenDesc_.Initialize({ 0,0 }, WinSize, rtvNum);

	// �|�C���^���l��
	PostEffect* newPostEffectPtr = newPostEffect.get();

	// �|�X�g�G�t�F�N�g��ۑ�
	sPostEffects_.push_back(std::move(newPostEffect));

	// �|�C���^��Ԃ�
	return newPostEffectPtr;
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

void PostEffect::AllClear()
{
	// �X�v���C�g2D�S����
	for (size_t i = 0; i < sPostEffects_.size(); i++)
	{
		sPostEffects_[i].reset(nullptr);
	}
	sPostEffects_.clear();
}

void PostEffect::StartRender()
{
	// ���Ԓʂ肶��Ȃ��Ȃ�x��
	assert(phase_ == Phase::None);

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
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> rtvHandles;

	for (size_t i = 0; i < rtvHandles.size(); i++)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle =
			CD3DX12_CPU_DESCRIPTOR_HANDLE(
				rtvHeap_->GetCPUDescriptorHandleForHeapStart(), static_cast<INT>(i),
				spDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));

		rtvHandles.emplace_back(rtvHandle);
	}

	// DSV�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap_->GetCPUDescriptorHandleForHeapStart();

	// �����_�[�^�[�Q�b�g���Z�b�g
	spCmdList_->OMSetRenderTargets(2, rtvHandles.data(), true, &dsvHandle);

	// �X�N���[���ݒ�̕`��R�}���h
	screenDesc_.SetDrawCommand();

	for (size_t i = 0; i < rtvHandles.size(); i++)
	{
		// ��ʃN���A
		//FLOAT clear[] = { ClearColor.r_,ClearColor.g_,ClearColor.b_,ClearColor.a_ };
		FLOAT clear[] = { 0.25f, 0.5f ,0.1f, 0.0f };
		spCmdList_->ClearRenderTargetView(rtvHandles[i], clear, 0, nullptr); // ���ۂ��F
	}

	// �[�x�o�b�t�@�N���A
	spCmdList_->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	// �i�K��i�߂�
	phase_ = Phase::Rendering;
}

void PostEffect::EndRender()
{
	// ���Ԓʂ肶��Ȃ��Ȃ�x��
	assert(phase_ == Phase::Rendering);

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

	// �i�K��i�߂�
	phase_ = Phase::End;
}

void PostEffect::SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices)
{
	// ���Ԓʂ肶��Ȃ��Ȃ�x��
	assert(phase_ == Phase::End);

	if (isVisible_ == false) { return; }

	// �e�N�X�`��0
	pTexs_[0]->SetDrawCommand(rpIndices["Texture0"]);

	// �e�N�X�`��1
	pTexs_[1]->SetDrawCommand(rpIndices["Texture1"]);

	// ���_�o�b�t�@�𑗂� + �`��R�}���h
	vt_.Draw();

	// �i�K���ŏ��ɖ߂�
	phase_ = Phase::None;
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
}

PipelineSetting PostEffect::GetPipelineSetting()
{
	PipelineSetting result;

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

	result.inputLayout = inputLayout;

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
	result.samplerDescs.emplace_back(samplerDesc);

	result.fillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�

	result.cullMode = D3D12_CULL_MODE_NONE; // �w�ʂ��J�����O���Ȃ�

	result.depthEnable = false; // �[�x�e�X�g���Ȃ�

	result.primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE; // �O�p�`

	result.primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; // �O�p�`�X�g���b�v

	return result;
}