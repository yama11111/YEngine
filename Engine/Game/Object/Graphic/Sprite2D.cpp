#include "Sprite2D.h"
#include <cassert>

using std::vector;
using std::unique_ptr;
using YGame::Sprite2D;
using YGame::PipelineSetting;
using YMath::Vector2;

vector<unique_ptr<Sprite2D>> Sprite2D::sSprites_{};

Sprite2D* Sprite2D::Create(
	const std::unordered_map<std::string, Texture*>& pTexs, 
	Vector2 anchor, 
	const bool isFlipX, 
	const bool isFlipY)
{
	assert(pTexs.size() > 0);

	unique_ptr<Sprite2D> newSprite = std::make_unique<Sprite2D>();

	// �e�N�X�`���̃T�C�Y���擾
	float rscSizeX = static_cast<float>(pTexs.begin()->second->Buffer()->GetDesc().Width);
	float rscSizeY = static_cast<float>(pTexs.begin()->second->Buffer()->GetDesc().Height);

	// ----- Status ----- //

	// ���]�ݒ�
	float flipX = isFlipX ? -1.0f : 1.0f;
	float flipY = isFlipY ? -1.0f : 1.0f;

	// �T�C�Y��ݒ� (�摜�ɍ��킹��Ȃ炻�̂܂�)
	Vector2 size = Vector2(rscSizeX, rscSizeY);

	// ���E�㉺�̃|�C���g�ݒ� (0.0~1,0)
	float left	 = (0.0f - anchor.x_) * size.x_ * flipX;
	float right	 = (1.0f - anchor.x_) * size.x_ * flipX;
	float top	 = (0.0f - anchor.y_) * size.y_ * flipY;
	float bottom = (1.0f - anchor.y_) * size.y_ * flipY;

	// ----- TexStatus ----- //

	// �e�N�X�`���̍���ƉE����ݒ� (�摜�ɍ��킹��Ȃ炻�̂܂�)
	Vector2 texLT = Vector2(0.0f, 0.0f);
	Vector2 texRB = Vector2(rscSizeX, rscSizeY);

	// UV���W���v�Z
	float texLeft	= texLT.x_ / rscSizeX;
	float texRight	= texRB.x_ / rscSizeX;
	float texTop	= texLT.y_ / rscSizeY;
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
	newSprite->size_	 = size; // �傫��
	newSprite->anchor_	 = anchor; // �A���J�[�|�C���g
	newSprite->isFlipX_	 = isFlipX; // X���]
	newSprite->isFlipY_	 = isFlipY; // Y���]

	newSprite->pTexs_ = pTexs; // �e�N�X�`���C���f�b�N�X

	// �|�C���^���l��
	Sprite2D* newSpritePtr = newSprite.get();

	// �X�v���C�g��ۑ�
	sSprites_.push_back(std::move(newSprite));

	// �X�v���C�g�|�C���^��Ԃ�
	return newSpritePtr;
}

void Sprite2D::AllClear()
{
	for (size_t i = 0; i < sSprites_.size(); i++)
	{
		sSprites_[i].reset(nullptr);
	}
	sSprites_.clear();
}

void Sprite2D::SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices)
{
	if (isVisible_ == false) { return; }

	// �e�N�X�`��
	for (auto itr = rpIndices.begin(); itr != rpIndices.end(); ++itr)
	{
		// ����L�[���Ȃ��ꍇ�x��
		assert(pTexs_.contains(itr->first));

		pTexs_[itr->first]->SetDrawCommand(itr->second);
	}

	// ���_�o�b�t�@�𑗂� + �`��R�}���h
	vt_.Draw();
}

PipelineSetting Sprite2D::GetPipelineSetting()
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

	result.cullMode = D3D12_CULL_MODE_NONE; // �J�����O���Ȃ�

	result.depthEnable = false; // �[�x�e�X�g���Ȃ�

	result.primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE; // �O�p�`

	result.primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; // �O�p�`�X�g���b�v

	return result;
}