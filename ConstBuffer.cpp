#include "ConstBuffer.h"
#include "Result.h"

ConstBuffer::ConstBuffer()
{
}

void ConstBuffer::Create(const Vec4& color)
{
	cbInfo.heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	cbInfo.resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbInfo.resDesc.Width = (sizeof(ConstBufferDataMaterial) * 0xff) & ~0xff;
	cbInfo.resDesc.Height = 1;
	cbInfo.resDesc.DepthOrArraySize = 1;
	cbInfo.resDesc.MipLevels = 1;
	cbInfo.resDesc.SampleDesc.Count = 1;
	cbInfo.resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	// �萔�o�b�t�@�̐���
	cbMate.Create(cbInfo);

	// �萔�o�b�t�@�̃}�b�s���O
	Result::Check(cbMate.buff->Map(0, nullptr, (void**)&cMapMate));
	// �l���������ނƎ����I�ɓ]�������
	cMapMate->color = color;

	cmdList = DXCommandList::GetInstance();
}

void ConstBuffer::SetCommand()
{
	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	cmdList->List()->SetGraphicsRootConstantBufferView(index, 
		cbMate.buff->GetGPUVirtualAddress());
}