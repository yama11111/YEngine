#include "BaseGraphic.h"

using YGame::BaseGraphic;

BaseGraphic::BaseGraphic(const std::string& typeTag) :
	fileName_(), typeTag_(typeTag), isVisible_(true)
{
}

/// https://zenn.dev/tatsuyas/articles/3511ff3bde0f90
bool BaseGraphic::operator==(const BaseGraphic & other) const
{
	return typeTag_ == other.typeTag_ && typeid(*this) == typeid(other);
}
