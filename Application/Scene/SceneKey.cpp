#include "SceneKey.h"
#include <unordered_map>
#include <cassert>

using YGame::SceneKey;

namespace
{
	// 世界のキー(string型)
	std::unordered_map<SceneKey, std::string> sceneKeyStrMap =
	{
		{ SceneKey::eTitleKey,	 "Title" },
		{ SceneKey::eSelectKey,	 "Select" },
		{ SceneKey::ePlayKey,	 "Play" },
		{ SceneKey::eResultKey,	 "Result" },
		{ SceneKey::eTestKey,	 "Test" },
	};

	std::vector<SceneKey> sceneKeyVector =
	{
		SceneKey::eTitleKey,
		SceneKey::eSelectKey,
		SceneKey::ePlayKey,
		SceneKey::eResultKey,
		SceneKey::eTestKey,
	};

	std::vector<std::string> sceneKeyStrVector =
	{
		"Title",
		"Select",
		"Play",
		"Result",
		"Test",
	};
}

std::string SceneKeyStr(const SceneKey key)
{
	assert(sceneKeyStrMap.contains(key));
	return sceneKeyStrMap[key];
}

std::string SceneKeyStr(const size_t keyIdx)
{
	assert(0 <= keyIdx && keyIdx < sceneKeyStrVector.size());
	return sceneKeyStrVector[keyIdx];
}

std::vector<SceneKey> SceneKeys()
{
	return sceneKeyVector;
}

std::vector<std::string> SceneKeyStrs()
{
	return sceneKeyStrVector;
}
