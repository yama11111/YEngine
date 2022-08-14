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
	// 定数バッファの生成
	cbMate.Create(cbInfo);

	// 定数バッファのマッピング
	Result::Check(cbMate.buff->Map(0, nullptr, (void**)&cMapMate));
	// 値を書きこむと自動的に転送される
	cMapMate->color = color;

	cmdList = DXCommandList::GetInstance();
}

void ConstBuffer::SetCommand()
{
	// 定数バッファビュー(CBV)の設定コマンド
	cmdList->List()->SetGraphicsRootConstantBufferView(index, 
		cbMate.buff->GetGPUVirtualAddress());
}