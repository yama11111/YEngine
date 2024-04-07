#include "Outside.h"
#include "OutsideDrawer.h"

using YGame::Outside;
using YMath::BitFrag;

namespace
{

}

std::unique_ptr<Outside> Outside::Create(const Transform::Status& status, const std::string& key)
{
	std::unique_ptr<Outside> newObj = std::make_unique<Outside>();

	newObj->Initialize(status, key);

	return std::move(newObj);
}

void Outside::Initialize(const Transform::Status& status, const std::string& key)
{
	GameObject::Initialize("Outside", status);

	SetUpdateKey(key);
	SetDrawKeys({ key });

	SetDrawer(OutsideDrawer::Create({ nullptr, nullptr, key, 2 }));
}

void Outside::UpdateBeforeCollision()
{
	GameObject::UpdateBeforeCollision();
}

void Outside::UpdateAfterCollision()
{
	GameObject::UpdateAfterCollision();
}