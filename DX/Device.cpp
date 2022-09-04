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

	// �Ή����x���̔z��
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
		// �̗p�����A�_�v�^�[�Ńf�o�C�X����
		if (Result::Check(D3D12CreateDevice(adpt->Get(), levels[i],
			IID_PPV_ARGS(&device))))
		{
			// �f�o�C�X�𐶐��ł������_�Ń��[�v�𔲂���
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