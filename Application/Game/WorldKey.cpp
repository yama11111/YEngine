#include "WorldKey.h"
#include <unordered_map>
#include <cassert>

using YGame::WorldKey;

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

	std::unordered_map<std::string, WorldKey> worldKeyMap =
	{
		{ "Start",		WorldKey::eStartKey, },
		{ "World",		WorldKey::eWorldKey, },
		{ "Journey",	WorldKey::eJourneyKey, },
		{ "Fever",		WorldKey::eFeverKey, },
		{ "Goal",		WorldKey::eGoalKey, },
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

WorldKey YGame::WorldKeyEnum(const std::string& key)
{
	assert(worldKeyMap.contains(key));
	return worldKeyMap[key];
}

std::string YGame::WorldKeyStr(const WorldKey key)
{
	assert(worldKeyStrMap.contains(key));
	return worldKeyStrMap[key];
}

std::string YGame::WorldKeyStr(const size_t keyIdx)
{
	assert(0 <= keyIdx && keyIdx < worldKeyStrVector.size());
	return worldKeyStrVector[keyIdx];
}

std::vector<WorldKey> YGame::WorldKeys()
{
	return worldKeyVector;
}

std::vector<std::string> YGame::WorldKeyStrs()
{
	return worldKeyStrVector;
}
