#pragma once
#include "DXResourceInfo.h"

struct DXResource
{
	ID3D12Resource* buff = nullptr; // �o�b�t�@

	void Create(const DXResourceInfo& rscInfo);
};

