#pragma once
#include "Vec4.h"

namespace Math
{
	// ����������
	void Srand();
	// �����擾
	int GetRand(const int start, const int end);

	// ����
	template<typename T>
	T Sign(const T num);

	// �͈͐���
	template<typename T>
	T Clamp(const T num, const T lower, const T upper);

	// �F�ϊ�((0�`255)��(0.0�`1.0))
	Vec4 GetColor(const int R, const int G, const int B, const int A);
}

