#pragma once
#include "ConstBuffer.h"
#include "DXCommandList.h"

class ConstBufferManager
{
private:
	DXCommandList* cmdList = nullptr;
	UINT indexM = 0;
	UINT indexT = 0;
public:
	void CreateCB(ConstBufferMaterial& cb, const Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
	void CreateCB(ConstBufferTransform& cb);
	void SetCommand(ConstBufferMaterial& cb);
	void SetCommand(ConstBufferTransform& cb);
public:
	static ConstBufferManager* GetInstance();
private:
	ConstBufferManager();
	~ConstBufferManager() = default;
	ConstBufferManager(const ConstBufferManager&) = delete;
	const ConstBufferManager& operator=(const ConstBufferManager&) = delete;
};

