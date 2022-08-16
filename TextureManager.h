#pragma once
#include "Vec4.h"
#include "DXSRVHeap.h"

class TextureManager
{
private:
	DXSRVHeap* srvH = nullptr;
public:
	UINT Create(const Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
	UINT Load(const wchar_t* fileName);
	void SetCommand(const UINT index);
public:
	static TextureManager* GetInstance();
private:
	TextureManager();
	~TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	const TextureManager& operator=(const TextureManager&) = delete;
};

