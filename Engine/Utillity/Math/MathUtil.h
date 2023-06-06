#pragma once
#include "Vector4.h"

namespace YMath
{
	// ����������
	void Srand();
	
	// �����擾
	int GetRand(const int start, const int end);
	float GetRand(const float start, const float end, const float place);

	// ����
	template<typename T>
	T Sign(const T num);

	// �͈͐���
	template<typename T>
	T Clamp(const T num, const T lower, const T upper);

	// �F�ϊ�((0�`255)��(0.0�`1.0))
	Vector4 GetColor(const int R, const int G, const int B, const int A);

	// �x�����烉�W�A���ɕϊ�
	float ConvertFromDegreeToRadian(const float degree);
}
