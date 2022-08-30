#pragma once
#include "Vec3.h"
#include "CollisionConfig.h"
class Collider 
{
private:
	float radius = 0.0f;
	int damage = 0;
	uint32_t COLL_ATTRIBUTE = 0xffffffff; // ‘®«
	uint32_t COLL_MASK = 0xffffffff; // ƒ}ƒXƒN
public:
	float GetRad() { return radius; }
	void SetRad(const float radius) { this->radius = radius; }
	float GetDamage() { return damage; }
	void SetDamage(const int damage) { this->damage = damage; }
	virtual Vec3 GetWorldPos() = 0;
	virtual void OnCollision(const int damage) {}

	uint32_t GetAttribute() { return COLL_ATTRIBUTE; }
	void SetAttribute(const uint32_t attribute) { COLL_ATTRIBUTE = attribute; }
	uint32_t GetMask() { return COLL_MASK; }
	void SetMask(const uint32_t mask) { COLL_MASK = mask; }
};
