#include "DXVertexLayoutManager.h"

DXVertexLayoutManager::DXVertexLayoutManager() :
	inputLayout()
{
	//{
	//	 �Z�}���e�B�b�N��,
	//	 ���������Z�}���e�B�b�N��������ꍇ�Ɏg���C���f�b�N�X (0 �ł���),
	//	 �v�f���ƃr�b�g����Ԃ� (float XYZ(3��) -> R32G32B32_FLOAT),
	//	 *���̓X���b�g�C���f�b�N�X (0 �ł���),
	//	 �f�[�^�̃I�t�Z�b�g�l (D3D12_APPEND_ALIGNED_ELEMENT ���Ǝ���),
	//	 *���̓f�[�^��� (�W���� D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA),
	//	 *��x�ɕ`�悷��C���X�^���X�� (0 �ł���)
	//}

	D3D12_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
		//{
		//	"NORMAL",
		//	0,
		//	DXGI_FORMAT_R32G32B32_FLOAT,
		//	0,
		//	D3D12_APPEND_ALIGNED_ELEMENT,
		//	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
		//	0
		//},
		//{
		//	"TEXCOORD",
		//	0,
		//	DXGI_FORMAT_R32G32_FLOAT,
		//	0,
		//	D3D12_APPEND_ALIGNED_ELEMENT,
		//	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
		//	0
		//}
	};

	for (int i = 0; i < 1; i++)
	{
		inputLayout.push_back(layout[i]);
	}

}
