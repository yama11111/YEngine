#include "MatWorld.h"
#include "Calc.h"

using Object::MatWorld;
using Math::Mat4;

MatWorld::MatWorld() :
	m(Mat4::Identity()),
	pos(0.0f, 0.0f, 0.0f),
	rota(0.0f, 0.0f, 0.0f),
	scale(1.0f, 1.0f, 1.0f)
{
}

MatWorld::MatWorld(const InitStatus& init) :
	pos(init.pos), rota(init.rota), scale(init.scale)
{
	m = Mat4::Identity();
	m *= MatScale(scale) * MatRotation(rota) * MatTranslation(pos);
}

void MatWorld::Update()
{
	m = Mat4::Identity();
	m *= MatScale(scale) * MatRotation(rota) * MatTranslation(pos);
}
