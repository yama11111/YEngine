#include "WorldKey.h"
#include <unordered_map>
#include <cassert>

namespace
{
	// 世界のキー(string型)
	std::unordered_map<WorldKey, std::string> worldKeyStrMap =
	{
		{ WorldKey::eStartKey,	 "Start" },
		{ WorldKey::eWorldKey,	 "World" },
		{ WorldKey::eJourneyKey, "Journey" },
		{ WorldKey::eFeverKey,	 "Fever" },
		{ WorldKey::eGoalKey,	 "Goal" },
	};

	std::vector<WorldKey> worldKeyVector =
	{
		WorldKey::eStartKey,
		WorldKey::eWorldKey,
		WorldKey::eJourneyKey,
		WorldKey::eFeverKey,
		WorldKey::eGoalKey,
	};

	std::vector<std::string> worldKeyStrVector =
	{
		"Start",
		"World",
		"Journey",
		"Fever",
		"Goal",
	};
}

std::string WorldKeyStr(const WorldKey key)
{
	assert(worldKeyStrMap.contains(key));
	return worldKeyStrMap[key];
}

std::string WorldKeyStr(const size_t keyIdx)
{
	assert(0 <= keyIdx && keyIdx < worldKeyStrVector.size());
	return worldKeyStrVector[keyIdx];
}

std::vector<WorldKey> WorldKeys()
{
	return worldKeyVector;
}

std::vector<std::string> WorldKeyStrs()
{
	return worldKeyStrVector;
}
