#include "DXAdapter.h"
#include "Result.h"
#include <vector>

void DXAdapter::Selection(IDXGIFactory7* dxgiFactory)
{
	// �A�_�v�^�[�̗񋓗p
	std::vector<IDXGIAdapter4*> adapters;

	// �p�t�H�[�}���X���������̂��珇�ɁA�S�ẴA�_�v�^�[���
	for (UINT i = 0;
		dxgiFactory->EnumAdapterByGpuPreference(
			i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
			IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND;
		i++)
	{
		// ���I�z��ɒǉ�
		adapters.push_back(tmpAdapter);
	}

	// �Ó��ȃA�_�v�^��I��
	for (size_t i = 0; i < adapters.size(); i++)
	{
		DXGI_ADAPTER_DESC3 adapterDesc;
		// �A�_�v�^�[�̏��擾
		adapters[i]->GetDesc3(&adapterDesc);
		// �\�t�g�E�F�A�f�o�C�X�����
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE))
		{
			// �f�o�C�X���̗p���ă��[�v�𔲂���
			tmpAdapter = adapters[i];
			break;
		}
	}
}

IDXGIAdapter4* DXAdapter::Template()
{
	return tmpAdapter;
}

DXAdapter* DXAdapter::GetInstance()
{
	static DXAdapter instance;
	return &instance;;
}