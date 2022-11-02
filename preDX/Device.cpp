#include "Device.h"
#include "Adapter.h"
#include "Utility/Result.h"

using DX::Device;
using DX::Utility::Result;

Device* Device::GetInstance()
{
	static Device instance;
	return &instance;
}

bool Device::Create()
{
	Adapter* adpt = Adapter::GetInstance();

	// 対応レベルの配列
	D3D_FEATURE_LEVEL levels[4] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	if (adpt->Get() == nullptr)
	{
		Result::Assert(false);
		return false;
	}

	for (size_t i = 0; i < _countof(levels); i++)
	{
		// 採用したアダプターでデバイス生成
		if (Result::Check(D3D12CreateDevice(adpt->Get(), levels[i],
			IID_PPV_ARGS(&device))))
		{
			// デバイスを生成できた時点でループを抜ける
			featureLevel = levels[i];
			break;
		}
	}

	if (device.Get() == nullptr)
	{
		Result::Assert(false);
		return false;
	}

	return true;
}

ID3D12Device* Device::Get()
{
	return device.Get();
}