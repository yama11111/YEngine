#include "Sprite3D.h"
#include "MathVector.h"
#include <cassert>

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::Sprite3D;
using YGame::PipelineSetting;
using YMath::Vector3;
using YMath::Matrix4;

std::vector<std::unique_ptr<Sprite3D>> Sprite3D::sSprites_{};
YDX::Vertices<Sprite3D::VData> Sprite3D::vt_{};
bool Sprite3D::isInitVertices_ = false;

Sprite3D* Sprite3D::Create(Texture* pTex)
{
	// 初期化
	if (isInitVertices_ == false)
	{
		vt_.Initialize({ {} });
		isInitVertices_ = true;
	}

	// スプライト生成
	unique_ptr<Sprite3D> newSprite = std::make_unique<Sprite3D>();

	// テクスチャ番号
	newSprite->pTex_ = pTex;

	// 描画する
	newSprite->isVisible_ = true;


	// ポインタを獲得
	Sprite3D* newSpritePtr = newSprite.get();

	// スプライトを保存
	sSprites_.push_back(std::move(newSprite));

	// スプライトポインタを返す
	return newSpritePtr;
}

void Sprite3D::AllClear()
{
	// スプライト3D全消去
	for (size_t i = 0; i < sSprites_.size(); i++)
	{
		sSprites_[i].reset(nullptr);
	}
	sSprites_.clear();
}

void Sprite3D::SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices)
{
	// 描画しないなら弾く
	if (isVisible_ == false) { return; }

	// テクスチャ
	pTex_->SetDrawCommand(rpIndices["Texture"]);

	// 頂点バッファを送る + 描画コマンド
	vt_.Draw();
}

PipelineSetting Sprite3D::GetPipelineSetting()
{
	PipelineSetting result;

	// 頂点レイアウト
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout =
	{
		// 頂点座標	 (x, y, z)
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
	};

	result.inputLayout = inputLayout;

	// テクスチャサンプラーの設定
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 横折り返し   (タイリング)
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 縦折り返し   (タイリング)
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 奥行折り返し (タイリング)
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK; // ボーダーの時は黒
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;   // 全てリニア補間
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX; // ミニマップ最大値
	samplerDesc.MinLOD = 0.0f;              // ミニマップ最小値
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // ピクセルシェーダーからのみ使用可能

	// テクスチャサンプラー配列に挿入
	result.samplerDescs.emplace_back(samplerDesc);

	result.fillMode = D3D12_FILL_MODE_SOLID; // ポリゴン内塗りつぶし

	result.cullMode = D3D12_CULL_MODE_NONE; // カリングしない

	result.depthEnable = false; // 深度テストしない
	
	result.primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT; // 点

	result.primitive = D3D_PRIMITIVE_TOPOLOGY_POINTLIST; // ポイントリスト

	return result;
}