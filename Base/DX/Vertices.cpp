#include "Vertices.h"
#include "YAssert.h"

using DX::Vertices;
using DX::VertexIndex3D;
using Math::Vec3;

template <typename T>
ID3D12GraphicsCommandList* Vertices<T>::pCmdList_ = nullptr;

template <typename T>
void Vertices<T>::StaticInitialize(ID3D12GraphicsCommandList* pCommandList)
{
	assert(pCommandList);
	pCmdList_ = pCommandList;
}

template <typename T>
void Vertices<T>::Initialize(const std::vector<T> v)
{
	// ���_�����R�s�[
	v_ = v;

	// �o�b�t�@�ƃr���[�쐬
	Create();
}

template<typename T>
void Vertices<T>::TransferMap(const std::vector<T> v)
{
	// ���_�����N���A
	v_.clear();
	// ���_�����R�s�[
	v_ = v;
	// �S���_�ɑ΂��č��W���R�s�[
	for (int i = 0; i < v_.size(); i++) { vertMap_[i] = v_[i]; }
}

template<typename T>
void Vertices<T>::Create()
{
	// ���_�T�C�Y
	UINT dataSize = static_cast <UINT> (sizeof(v_[0]) * v_.size());

	// �����p�ݒ�
	GPUResource::CreateStatus state{};

	// ���_�o�b�t�@�ݒ�
	state.heapProp_.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
	// ���\�[�X�ݒ�
	state.resDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	state.resDesc_.Width = dataSize; // ���_�f�[�^�S�̂̃T�C�Y
	state.resDesc_.Height = 1;
	state.resDesc_.DepthOrArraySize = 1;
	state.resDesc_.MipLevels = 1;
	state.resDesc_.SampleDesc.Count = 1;
	state.resDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// ���_�o�b�t�@�̐���
	buffer_.Create(state);

	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	Result(buffer_.Get()->Map(0, nullptr, (void**)&vertMap_));
	// �S���_�ɑ΂��č��W���R�s�[
	for (int i = 0; i < v_.size(); i++) { vertMap_[i] = v_[i]; }
	// �q���������
	buffer_.Get()->Unmap(0, nullptr);

	// ���_�o�b�t�@�r���[�̍쐬
	// GPU���z�A�h���X
	view_.BufferLocation = buffer_.Get()->GetGPUVirtualAddress();
	// ���_�o�b�t�@�̃T�C�Y
	view_.SizeInBytes = dataSize;
	// ���_1���̃f�[�^�T�C�Y
	view_.StrideInBytes = sizeof(v_[0]);
}

template <typename T>
void Vertices<T>::Draw()
{
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	pCmdList_->IASetVertexBuffers(0, 1, &view_);
	// �`��R�}���h
	pCmdList_->DrawInstanced((UINT)v_.size(), 1, 0, 0); // �S�Ă̒��_���g���ĕ`��
}

template class Vertices<DX::SpriteVData>;
template class Vertices<DX::ModelVData>;

void VertexIndex3D::Initialize(const std::vector<ModelVData> v, const std::vector<uint16_t> idx, const bool normalized)
{
	// ���_�����R�s�[
	v_ = v;
	// �C���f�b�N�X�����R�s�[
	idx_ = idx;

	// �@���v�Z
	if (normalized) { Normalized(); }

	// ----- vertices ----- //

	Create();

	// ----- index ----- //

	// �C���f�b�N�X�T�C�Y
	UINT dataSize = static_cast <UINT> (sizeof(uint16_t) * idx.size());

	// �����p�ݒ�
	GPUResource::CreateStatus state{};

	// ���_�o�b�t�@�ݒ�
	state.heapProp_.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
	// ���\�[�X�ݒ�
	state.resDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	state.resDesc_.Width = dataSize; // ���_�f�[�^�S�̂̃T�C�Y
	state.resDesc_.Height = 1;
	state.resDesc_.DepthOrArraySize = 1;
	state.resDesc_.MipLevels = 1;
	state.resDesc_.SampleDesc.Count = 1;
	state.resDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// �C���f�b�N�X�o�b�t�@�̐���
	idxBuffer_.Create(state);
	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	uint16_t* idxMap = nullptr; // ���z������
	Result(idxBuffer_.Get()->Map(0, nullptr, (void**)&idxMap));
	// �S�C���f�b�N�X�ɑ΂��ăC���f�b�N�X���R�s�[
	for (int i = 0; i < idx_.size(); i++) { idxMap[i] = idx_[i]; }
	// �q���������
	idxBuffer_.Get()->Unmap(0, nullptr);

	// �C���f�b�N�X�o�b�t�@�r���[�̍쐬
	// GPU���z�A�h���X
	idxView_.BufferLocation = idxBuffer_.Get()->GetGPUVirtualAddress();
	idxView_.Format = DXGI_FORMAT_R16_UINT;
	// �C���f�b�N�X�o�b�t�@�̃T�C�Y
	idxView_.SizeInBytes = dataSize;
}

void VertexIndex3D::Normalized() 
{
	for (size_t i = 0; i < idx_.size() / 3; i++)
	{
		// �O�p�`1���ƂɌv�Z���Ă���
		// �O�p�`�̃C���f�b�N�X�����o���āA��ʓI�ȕϐ��ɓ����
		unsigned short index0 = idx_[i * 3 + 0];
		unsigned short index1 = idx_[i * 3 + 1];
		unsigned short index2 = idx_[i * 3 + 2];
		// �O�p�`���\�����钸�_���W�x�N�g���ɑ��
		Vec3 p0 = v_[index0].pos_;
		Vec3 p1 = v_[index1].pos_;
		Vec3 p2 = v_[index2].pos_;
		// p0->p1�x�N�g���Ap0->p2�x�N�g�����v�Z (�x�N�g���̌��Z)
		Vec3 v1 = p1 - p0;
		Vec3 v2 = p2 - p0;
		// �O�ς͗������琂���ȃx�N�g��
		Vec3 normal = v1.Cross(v2);
		// ���K�� (������1�ɂ���)
		normal = normal.Normalized();
		// ���߂��@���𒸓_�f�[�^�ɑ��
		v_[index0].normal_ = normal;
		v_[index1].normal_ = normal;
		v_[index2].normal_ = normal;
	}
}

void VertexIndex3D::Draw()
{
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	pCmdList_->IASetVertexBuffers(0, 1, &view_);
	// �C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	pCmdList_->IASetIndexBuffer(&idxView_);
	// �`��R�}���h
	pCmdList_->DrawIndexedInstanced((UINT)idx_.size(), 1, 0, 0, 0); // �S�Ă̒��_���g���ĕ`��
}