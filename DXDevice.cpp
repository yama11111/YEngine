#include "DXDevice.h"
#include "DXAdapter.h"
#include "Result.h"

bool DXDevice::Create()
{
	DXAdapter* adpt = DXAdapter::GetInstance();

	// �Ή����x���̔z��
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
		// �̗p�����A�_�v�^�[�Ńf�o�C�X����
		if (Result::Check(D3D12CreateDevice(adpt->Template(), levels[i],
			IID_PPV_ARGS(&device))))
		{
			// �f�o�C�X�𐶐��ł������_�Ń��[�v�𔲂���
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