#include "Sprite3D.h"
#include "MathVector.h"
#include <cassert>

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::Sprite3D;
using YGame::PipelineSetting;
using YMath::Vector3;
using YMath::Matrix4;

std::vector<std::unique_ptr<Sprite3D>> Sprite3D::sSprites_{};
YDX::Vertices<Sprite3D::VData> Sprite3D::vt_{};
bool Sprite3D::isInitVertices_ = false;

Sprite3D* Sprite3D::Create(Texture* pTex)
{
	// ������
	if (isInitVertices_ == false)
	{
		vt_.Initialize({ {} });
		isInitVertices_ = true;
	}

	// �X�v���C�g����
	unique_ptr<Sprite3D> newSprite = std::make_unique<Sprite3D>();

	// �e�N�X�`���ԍ�
	newSprite->pTex_ = pTex;

	// �`�悷��
	newSprite->isVisible_ = true;


	// �|�C���^���l��
	Sprite3D* newSpritePtr = newSprite.get();

	// �X�v���C�g��ۑ�
	sSprites_.push_back(std::move(newSprite));

	// �X�v���C�g�|�C���^��Ԃ�
	return newSpritePtr;
}

void Sprite3D::AllClear()
{
	// �X�v���C�g3D�S����
	for (size_t i = 0; i < sSprites_.size(); i++)
	{
		sSprites_[i].reset(nullptr);
	}
	sSprites_.clear();
}

void Sprite3D::SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices)
{
	// �`�悵�Ȃ��Ȃ�e��
	if (isVisible_ == false) { return; }

	// �e�N�X�`��
	pTex_->SetDrawCommand(rpIndices["Texture"]);

	// ���_�o�b�t�@�𑗂� + �`��R�}���h
	vt_.Draw();
}

PipelineSetting Sprite3D::GetPipelineSetting()
{
	PipelineSetting result;

	// ���_���C�A�E�g
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout =
	{
		// ���_���W	 (x, y, z)
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
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

	result.cullMode = D3D12_CULL_MODE_NONE; // �J�����O���Ȃ�

	result.depthEnable = false; // �[�x�e�X�g���Ȃ�
	
	result.primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT; // �_

	result.primitive = D3D_PRIMITIVE_TOPOLOGY_POINTLIST; // �|�C���g���X�g

	return result;
}