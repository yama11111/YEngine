#include "Billboard.h"
#include <cassert>

using Game::Billboard;
using Game::TextureManager;

DX::PipelineSet Billboard::pplnSet_;
TextureManager* Billboard::pTexManager_ = nullptr;

void Billboard::StaticInitialize(TextureManager* pTexManager, std::vector<D3D12_ROOT_PARAMETER>* rootParams)
{
	assert(pTexManager);
	pTexManager_ = pTexManager;
	pplnSet_.Initialize(DX::PipelineSet::Type::BillboardT, rootParams);
}

void Billboard::StaticSetDrawCommand()
{
	pplnSet_.SetDrawCommand();
}

Billboard* Billboard::Create(const bool isYAxisBillboard)
{
	// インスタンス
	Billboard* instance = new Billboard();
	instance->vt_.Initialize({ {} });
	instance->isAxisY_ = isYAxisBillboard;
	instance->isInvisible_  = false;
	instance->cbBlbd_.Create();

	return instance;
}

void Billboard::Draw(Object& obj, const ViewProjection& vp, const UINT tex)
{
	if (isInvisible_) { return; }
	
	// ビルボード行列の計算
	Math::Vec3 axisZ = (vp.target_ - vp.eye_).Normalized();
	Math::Vec3 axisX = (vp.up_.Cross(axisZ)).Normalized();
	Math::Vec3 axisY = axisZ.Cross(axisX);

	// Y軸周りビルボードなら
	if (isAxisY_)
	{
		axisY = vp.up_.Normalized();
		axisZ = axisX.Cross(axisY);
	}

	// ビルボード行列
	Math::Mat4 matBillboard(
		axisX.x_, axisX.y_, axisX.z_, 0.0f,
		axisY.x_, axisY.y_, axisY.z_, 0.0f,
		axisZ.x_, axisZ.y_, axisZ.z_, 0.0f,
		0.0f,     0.0f,     0.0f,     1.0f
	);

	cbBlbd_.map_->matBlbd_ = matBillboard;

	obj.SetDrawCommand(vp.view_, vp.pro_);
	pTexManager_->SetDrawCommand(tex);
	vt_.Draw();
}
