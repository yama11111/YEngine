#pragma once
class Keys
{
public:
	unsigned char* keys;
	unsigned char* elderkeys;
public:
	static Keys* GetInstance();
	void Update();
	bool IsDown(const int key);
	bool IsTrigger(const int key);
	bool IsLongPress(const int key);
	bool IsRelease(const int key);
	int Horizontal();
	int Vertical();
private:
	Keys();
	~Keys();
	Keys(const Keys&) = delete;
	const Keys& operator=(const Keys&) = delete;
};