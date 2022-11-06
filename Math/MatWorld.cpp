#include "MatWorld.h"
#include "Calc.h"

using Math::MatWorld;

MatWorld::MatWorld() :
	m_(Mat4::Identity()),
	pos_(0.0f, 0.0f, 0.0f),
	rota_(0.0f, 0.0f, 0.0f),
	scale_(1.0f, 1.0f, 1.0f)
{
	Update();
}

MatWorld::MatWorld(const InitStatus& init) :
	m_(Mat4::Identity()),
	pos_(init.pos_),
	rota_(init.rota_),
	scale_(init.scale_)
{
	Update();
}

void MatWorld::Initialize(const InitStatus& init)
{
	pos_ = init.pos_;
	rota_ = init.rota_;
	scale_ = init.scale_;

	Update();
}

void MatWorld::Update()
{
	// ƒAƒtƒBƒ“•ÏŠ·
	m_ = Mat4::Identity();
	m_ *= MatScale(scale_) * MatRotation(rota_) * MatTranslation(pos_);
}
