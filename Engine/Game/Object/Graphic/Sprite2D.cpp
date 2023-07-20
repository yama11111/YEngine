#include "Sprite2D.h"
#include <cassert>

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::Sprite2D;
using YGame::PipelineSetting;
using YMath::Vector2;

vector<unique_ptr<Sprite2D>> Sprite2D::sSprites_{};

Sprite2D* Sprite2D::Create(const Status& status, const TexStatus& texStatus)
{
	// スプライト生成
	unique_ptr<Sprite2D> newSprite = std::make_unique<Sprite2D>();


	// テクスチャのサイズを取得
	float rscSizeX = static_cast<float>(texStatus.pTex_->Buffer()->GetDesc().Width);
	float rscSizeY = static_cast<float>(texStatus.pTex_->Buffer()->GetDesc().Height);

	// ----- Status ----- //

	// 反転設定
	float flipX = status.isFlipX_ ? -1.0f : 1.0f;
	float flipY = status.isFlipY_ ? -1.0f : 1.0f;

	// サイズを設定 (画像に合わせるならそのまま)
	Vector2 size = status.isDiv_ ? Vector2(rscSizeX, rscSizeY) : status.size_;

	// 左右上下のポイント設定 (0.0~1,0)
	float left = (0.0f - status.anchor_.x_) * size.x_ * flipX;
	float right = (1.0f - status.anchor_.x_) * size.x_ * flipX;
	float top = (0.0f - status.anchor_.y_) * size.y_ * flipY;
	float bottom = (1.0f - status.anchor_.y_) * size.y_ * flipY;

	// ----- TexStatus ----- //

	// テクスチャの左上と右下を設定 (画像に合わせるならそのまま)
	Vector2 texLT = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_;
	Vector2 texRB = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : (texStatus.leftTop_ + texStatus.size_);

	// UV座標を計算
	float texLeft = texLT.x_ / rscSizeX;
	float texRight = texRB.x_ / rscSizeX;
	float texTop = texLT.y_ / rscSizeY;
	float texBottom = texRB.y_ / rscSizeY;


	// インスタンス生成 (動的)
	newSprite->vt_.Initialize(
		{
			{ {  left,bottom,0.0f },{  texLeft,texBottom } }, // 左下
			{ {  left,top,   0.0f },{  texLeft,texTop } },    // 左上
			{ { right,bottom,0.0f },{ texRight,texBottom } }, // 右下
			{ { right,top,   0.0f },{ texRight,texTop } },    // 右上
		});

	// いろいろ設定
	newSprite->size_ = status.size_; // 大きさ
	newSprite->anchor_ = status.anchor_; // アンカーポイント
	newSprite->isFlipX_ = status.isFlipX_; // X反転
	newSprite->isFlipY_ = status.isFlipY_; // Y反転

	newSprite->pTex_ = texStatus.pTex_; // テクスチャインデックス
	newSprite->texLeftTop_ = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_; // テクスチャの左上
	newSprite->texSize_ = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : texStatus.size_; // テクスチャの大きさ


	// ポインタを獲得
	Sprite2D* newSpritePtr = newSprite.get();

	// スプライトを保存
	sSprites_.push_back(std::move(newSprite));

	// スプライトポインタを返す
	return newSpritePtr;
}

void Sprite2D::AllClear()
{
	// スプライト2D全消去
	for (size_t i = 0; i < sSprites_.size(); i++)
	{
		sSprites_[i].reset(nullptr);
	}
	sSprites_.clear();
}

void Sprite2D::SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices) const
{
	// 描画しないなら弾く
	if (isVisible_ == false) { return; }

	// テクスチャ
	pTex_->SetDrawCommand(rpIndices["Texture"]);

	// 頂点バッファを送る + 描画コマンド
	vt_.Draw();
}

PipelineSetting Sprite2D::GetPipelineSetting()
{
	PipelineSetting result;

	// 頂点レイアウト
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout =
	{
		// 頂点座標	 (x, y, z)
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		// UV座標	 (x, y)
		{
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		}
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

	result.primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE; // 三角形

	result.primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; // 三角形ストリップ

	return result;
}