#pragma once
#include "DXResourceInfo.h"

struct DXResource
{
	ID3D12Resource* buff = nullptr; // バッファ

	void Create(const DXResourceInfo& rscInfo);
};

