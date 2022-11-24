#pragma once
#include "Vec2.h"
#include "Vec3.h"

namespace Math
{
	// ���
	template<typename T>
	T Lerp(const T& a, const T& b, const float t);

	// 3�������
	Vec3 Slerp(const Vec3& v1, const Vec3& v2, float t);

	// �C�[�Y�C��(���񂾂񑁂�)
	template<typename T>
	T EaseIn(const T& start, const T& end, const float time, const float power);
	// �C�[�Y�A�E�g(���񂾂�x��)
	template<typename T>
	T EaseOut(const T& start, const T& end, const float time, const float power);

	// �C�[�W���O�N���X
	template<typename T>
	class Ease
	{
	private:
		// �����l
		T start_ = T();
		// �ŏI�l
		T end_ = T();
		// �ɋ}(�w��)
		float power_ = 0.0f;
	public:
		// ������
		void Initialize(const T& start, const T& end, const float power);
		// �C�[�Y�C��(���񂾂񑁂�)
		T In(const float time);
		// �C�[�Y�A�E�g(���񂾂�x��)
		T Out(const float time);
	public:
		// �����l�ݒ�
		void SetStart(const T& start) { start_ = start; };
		// �ŏI�l�ݒ� 
		void SetEnd(const T& end) { end_ = end; };
		// �ɋ}�ݒ�
		void SetPower(const float power) { power_ = power; }
	};
}
