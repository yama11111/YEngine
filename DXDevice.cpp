#include "DXDevice.h"
#include "DXAdapter.h"
#include "Result.h"

bool DXDevice::Create()
{
	DXAdapter* adpt = DXAdapter::GetInstance();

	// 対応レベルの配列
	D3D_FEATURE_LEVEL levels[4] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	Result::Assert(adpt->Template() != nullptr);
	for (size_t i = 0; i < _countof(levels); i++)
	{
		// 採用したアダプターでデバイス生成
		if (Result::Check(D3D12CreateDevice(adpt->Template(), levels[i],
			IID_PPV_ARGS(&device))))
		{
			// デバイスを生成できた時点でループを抜ける
			featureLevel = levels[i];
			break;
		}
	}
	if (device == nullptr) return false;
	return true;
}

ID3D12Device* DXDevice::Device()
{
	return device;
}

DXDevice* DXDevice::GetInstance()
{
	static DXDevice instance;
	return &instance;;
}