#pragma once
#include <string>

class DebugTextAttacher
{

public:

	/// <summary>
	/// �f�o�b�O�`��
	/// </summary>
	/// <param name="isWindow"> : �E�B���h�E�ɂ��邩</param>
	void DrawDebugText(const bool isWindow);

	/// <summary>
	/// ���O�ύX
	/// </summary>
	/// <param name="name"> : ���O</param>
	void SetName(const std::string& name);

protected:

	/// <summary>
	/// �f�o�b�O�e�L�X�g�{��
	/// </summary>
	virtual void DrawDebugTextContent() = 0;

protected:

	// ���ʖ�
	std::string name_;

};

