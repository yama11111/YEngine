#include "Vertices.h"
#include "YAssert.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Mesh.h"
#include "PostEffect.h"

using YDX::VertexCommon;
using YDX::Vertices;
using YDX::VertexIndex;

ID3D12GraphicsCommandList* VertexCommon::spCmdList_ = nullptr;

void VertexCommon::StaticInitialize(ID3D12GraphicsCommandList* pCommandList)
{
	assert(pCommandList);
	spCmdList_ = pCommandList;
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

	// ���_�o�b�t�@�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p

	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = dataSize; // ���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// ���_�o�b�t�@�̐���
	buffer_.Create(&heapProp, &resDesc);


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
	spCmdList_->IASetVertexBuffers(0, 1, &view_);
	
	// �`��R�}���h
	spCmdList_->DrawInstanced((UINT)v_.size(), 1, 0, 0); // �S�Ă̒��_���g���ĕ`��
}

template <typename T>
void VertexIndex<T>::Initialize(const std::vector<T> v, const std::vector<uint16_t> idx)
{
	// ���_�����R�s�[
	this->v_ = v;
	
	// �C���f�b�N�X�����R�s�[
	this->idx_ = idx;

	// ----- vertices ----- //

	this->Create();

	// ----- index ----- //

	// �C���f�b�N�X�T�C�Y
	UINT dataSize = static_cast <UINT> (sizeof(uint16_t) * idx.size());

	// ���_�o�b�t�@�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p

	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = dataSize; // ���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// �C���f�b�N�X�o�b�t�@�̐���
	idxBuffer_.Create(&heapProp, &resDesc);


	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	
	uint16_t* idxMap = nullptr; // ���z������
	
	Result(idxBuffer_.Get()->Map(0, nullptr, (void**)&idxMap));
	
	// �S�C���f�b�N�X�ɑ΂��ăC���f�b�N�X���R�s�[
	for (int i = 0; i < this->idx_.size(); i++) { idxMap[i] = this->idx_[i]; }
	
	// �q���������
	idxBuffer_.Get()->Unmap(0, nullptr);


	// �C���f�b�N�X�o�b�t�@�r���[�̍쐬
	
	// GPU���z�A�h���X
	idxView_.BufferLocation = idxBuffer_.Get()->GetGPUVirtualAddress();
	idxView_.Format = DXGI_FORMAT_R16_UINT;
	
	// �C���f�b�N�X�o�b�t�@�̃T�C�Y
	idxView_.SizeInBytes = dataSize;
}

template <typename T>
void VertexIndex<T>::Draw()
{
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	this->spCmdList_->IASetVertexBuffers(0, 1, &this->view_);
	
	// �C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	this->spCmdList_->IASetIndexBuffer(&idxView_);
	
	// �`��R�}���h
	this->spCmdList_->DrawIndexedInstanced((UINT)idx_.size(), 1, 0, 0, 0); // �S�Ă̒��_���g���ĕ`��
}

template class YDX::Vertices<YGame::Sprite2D::VData>;
template class YDX::Vertices<YGame::Sprite3D::VData>;
template class YDX::Vertices<YGame::Mesh::VData>;
template class YDX::Vertices<YGame::PostEffect::VData>;
template class YDX::VertexIndex<YGame::Sprite2D::VData>;
template class YDX::VertexIndex<YGame::Sprite3D::VData>;
template class YDX::VertexIndex<YGame::Mesh::VData>;
template class YDX::VertexIndex<YGame::PostEffect::VData>;