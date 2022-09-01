#pragma once
#include "Ray.h"
#include "Cursor.h"
#include <memory>

class Scope
{
public:
	std::unique_ptr<Ray> ray;
	std::unique_ptr <Cursor> cursor;
	Vec3 worldPos = { 0.0f,0.0f,0.0f };
	Sprite* s[Cursor::CursorTexNum::Num] = {nullptr, nullptr};
public:
	void Initialize(Model* model, const UINT tex);
	void InitStatus();
	void Update(const Vec2& pos, const MatViewProjection& vP);
	void Draw2D();
	void Draw3D(MatViewProjection& vP);
	~Scope();
};

