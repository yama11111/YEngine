#include "Shake.h"

using Math::Shake;

void Shake::Initialize()
{
	value = {};
	isShake = false;
	swingValue = 0;
	dekey = 0;
	rand = Random::GetInstance();
}

void Shake::Shaking(const float swing, const float dekey) 
{
	value = {};
	isShake = true;
	this->dekey = dekey;
	swingValue = swing;
}

void Shake::Update() {
	// ”ÍˆÍ‚ð‹·‚ß‚é
	if (swingValue > 0) {
		swingValue -= dekey;
	}

	// ”ÍˆÍ“à‚Ì—”¶¬
	if (isShake) {
		value.x = rand->GetRandF(-swingValue, swingValue);
		value.y = rand->GetRandF(-swingValue, swingValue);
		value.z = rand->GetRandF(-swingValue, swingValue);
	}

	if (swingValue <= 0) {
		value = { 0.0f, 0.0f, 0.0f };
		swingValue = 0;
		isShake = false;
	}
}