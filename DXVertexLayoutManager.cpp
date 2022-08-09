#include "DXVertexLayoutManager.h"

DXVertexLayoutManager::DXVertexLayoutManager() :
	inputLayout()
{
	//{
	//	 セマンティック名,
	//	 複数同じセマンティック名がある場合に使うインデックス (0 でいい),
	//	 要素数とビット数を返す (float XYZ(3つ) -> R32G32B32_FLOAT),
	//	 *入力スロットインデックス (0 でいい),
	//	 データのオフセット値 (D3D12_APPEND_ALIGNED_ELEMENT だと自動),
	//	 *入力データ種別 (標準は D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA),
	//	 *一度に描画するインスタンス数 (0 でいい)
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
