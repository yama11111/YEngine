#include "BaseConstBuffer.h"
#include "GPUResource.h"
#include "ConstBufferCommon.h"
#include "YAssert.h"

#include "CBModelTransform.h"
#include "CBSprite2DTransform.h"
#include "CBSprite3DTransform.h"
#include "CBPostEffectTransform.h"
#include "CBColor.h"
#include "CBMaterial.h"
#include "CBLightGroup.h"
#include "CBTexConfig.h"

using YGame::BaseConstBuffer;
using YGame::CBModelTransform;
using YGame::CBModelTransform;
using YGame::CBSprite2DTransform;
using YGame::CBSprite3DTransform;
using YGame::CBPostEffectTransform;
using YGame::CBColor;
using YGame::CBMaterial;
using YGame::CBLightGroup;
using YGame::CBTexConfig;

// 定数バッファ
template <typename CBData>
class ConstBuffer final: 
	public BaseConstBuffer,
	private YDX::ConstBufferCommon
{

private:

	// マッピング用
	CBData* map_ = nullptr;
	
	// データポインタ
	CBData* pData_ = nullptr;

	// キー
	std::string key_;

	// バッファ
	YDX::GPUResource buff_;

	// CBV設定
	D3D12_CONSTANT_BUFFER_VIEW_DESC viewDesc_{};

public:

	// 定数バッファの生成 + マッピング
	void CreateBuffer(const bool isMutable)
	{
		// ヒープ設定
		D3D12_HEAP_PROPERTIES heapProp{};
		heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;

		// リソース設定
		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Height = 1;
		resDesc.Width = (sizeof(CBData) * 0xff) & ~0xff;
		resDesc.DepthOrArraySize = 1;
		resDesc.MipLevels = 1;
		resDesc.SampleDesc.Count = 1;
		resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		// 定数バッファの生成
		buff_.Create(&heapProp, &resDesc);

		// 定数バッファのマッピング
		YDX::Result(buff_.Get()->Map(0, nullptr, (void**)&map_));

		// CBV生成
		viewDesc_.BufferLocation = buff_.Get()->GetGPUVirtualAddress();
		viewDesc_.SizeInBytes = static_cast<UINT>(resDesc.Width);
		spDescHeap_->CreateCBV(viewDesc_, isMutable);
	}

	// 描画前コマンド
	void SetDrawCommand(const uint32_t rootParamIndex) override
	{
		if (pData_)
		{
			// 値を更新
			*map_ = *pData_;
		}

		// 定数バッファビュー設定コマンド
		spCmdList_->SetGraphicsRootConstantBufferView(static_cast<UINT>(rootParamIndex), viewDesc_.BufferLocation);
	}

	// 種類取得
	const std::string KeyName() const override { return key_; }

public:

	ConstBuffer(CBData* pData);
	
	~ConstBuffer() = default;

};

template<typename CBData>
ConstBuffer<CBData>::ConstBuffer(CBData* pData){}
template<>
ConstBuffer<CBModelTransform::CBData>::ConstBuffer(CBModelTransform::CBData* pData) :
	pData_(pData), key_(CBModelTransform::KeyName())
{}
template<>
ConstBuffer<CBSprite2DTransform::CBData>::ConstBuffer(CBSprite2DTransform::CBData* pData) :
	pData_(pData), key_(CBSprite2DTransform::KeyName())
{}
template<>
ConstBuffer<CBSprite3DTransform::CBData>::ConstBuffer(CBSprite3DTransform::CBData* pData) :
	pData_(pData), key_(CBSprite3DTransform::KeyName())
{}
template<>
ConstBuffer<CBPostEffectTransform::CBData>::ConstBuffer(CBPostEffectTransform::CBData* pData) :
	pData_(pData), key_(CBPostEffectTransform::KeyName())
{}
template<>
ConstBuffer<CBColor::CBData>::ConstBuffer(CBColor::CBData* pData) :
	pData_(pData), key_(CBColor::KeyName())
{}
template<>
ConstBuffer<CBMaterial::CBData>::ConstBuffer(CBMaterial::CBData* pData) :
	pData_(pData), key_(CBMaterial::KeyName())
{}
template<>
ConstBuffer<CBLightGroup::CBData>::ConstBuffer(CBLightGroup::CBData* pData) :
	pData_(pData), key_(CBLightGroup::KeyName())
{}
template<>
ConstBuffer<CBTexConfig::CBData>::ConstBuffer(CBTexConfig::CBData* pData) :
	pData_(pData), key_(CBTexConfig::KeyName())
{}

template class ConstBuffer<CBModelTransform::CBData>;
template class ConstBuffer<CBModelTransform::CBData>;
template class ConstBuffer<CBSprite2DTransform::CBData>;
template class ConstBuffer<CBSprite3DTransform::CBData>;
template class ConstBuffer<CBPostEffectTransform::CBData>;
template class ConstBuffer<CBColor::CBData>;
template class ConstBuffer<CBMaterial::CBData>;
template class ConstBuffer<CBLightGroup::CBData>;
template class ConstBuffer<CBTexConfig::CBData>;

//template<typename CBData>
//BaseConstBuffer* BaseConstBuffer::Create<CBData>(CBData* pCBData, const bool isMutable)
//{
//	ConstBuffer<CBData>* newCB = new ConstBuffer<CBData>(pCBData);
//
//	// 生成 + マッピング
//	newCB->CreateBuffer(isMutable);
//
//	return newCB;
//}

template<>
BaseConstBuffer* BaseConstBuffer::Create<CBModelTransform::CBData>(CBModelTransform::CBData* pCBData, const bool isMutable)
{
	ConstBuffer<CBModelTransform::CBData>* newCB = new ConstBuffer<CBModelTransform::CBData>(pCBData);

	// 生成 + マッピング
	newCB->CreateBuffer(isMutable);

	return newCB;
}
template<>
BaseConstBuffer* BaseConstBuffer::Create<CBSprite2DTransform::CBData>(CBSprite2DTransform::CBData* pCBData, const bool isMutable)
{
	ConstBuffer<CBSprite2DTransform::CBData>* newCB = new ConstBuffer<CBSprite2DTransform::CBData>(pCBData);

	// 生成 + マッピング
	newCB->CreateBuffer(isMutable);

	return newCB;
}
template<>
BaseConstBuffer* BaseConstBuffer::Create<CBSprite3DTransform::CBData>(CBSprite3DTransform::CBData* pCBData, const bool isMutable)
{
	ConstBuffer<CBSprite3DTransform::CBData>* newCB = new ConstBuffer<CBSprite3DTransform::CBData>(pCBData);

	// 生成 + マッピング
	newCB->CreateBuffer(isMutable);

	return newCB;
}
template<>
BaseConstBuffer* BaseConstBuffer::Create<CBPostEffectTransform::CBData>(CBPostEffectTransform::CBData* pCBData, const bool isMutable)
{
	ConstBuffer<CBPostEffectTransform::CBData>* newCB = new ConstBuffer<CBPostEffectTransform::CBData>(pCBData);

	// 生成 + マッピング
	newCB->CreateBuffer(isMutable);

	return newCB;

}
template<>
BaseConstBuffer* BaseConstBuffer::Create<CBColor::CBData>(CBColor::CBData* pCBData, const bool isMutable)
{
	ConstBuffer<CBColor::CBData>* newCB = new ConstBuffer<CBColor::CBData>(pCBData);

	// 生成 + マッピング
	newCB->CreateBuffer(isMutable);

	return newCB;

}
template<>
BaseConstBuffer* BaseConstBuffer::Create<CBMaterial::CBData>(CBMaterial::CBData* pCBData, const bool isMutable)
{
	ConstBuffer<CBMaterial::CBData>* newCB = new ConstBuffer<CBMaterial::CBData>(pCBData);

	// 生成 + マッピング
	newCB->CreateBuffer(isMutable);

	return newCB;

}
template<>
BaseConstBuffer* BaseConstBuffer::Create<CBLightGroup::CBData>(CBLightGroup::CBData* pCBData, const bool isMutable)
{
	ConstBuffer<CBLightGroup::CBData>* newCB = new ConstBuffer<CBLightGroup::CBData>(pCBData);

	// 生成 + マッピング
	newCB->CreateBuffer(isMutable);

	return newCB;
}
template<>
BaseConstBuffer* BaseConstBuffer::Create<CBTexConfig::CBData>(CBTexConfig::CBData* pCBData, const bool isMutable)
{
	ConstBuffer<CBTexConfig::CBData>* newCB = new ConstBuffer<CBTexConfig::CBData>(pCBData);

	// 生成 + マッピング
	newCB->CreateBuffer(isMutable);

	return newCB;
}
