#pragma once

namespace Math
{
	float EaseIn(const float start, const float end, const float time, const float power);
	float EaseOut(const float start, const float end, const float time, const float power);

	class Ease
	{
	public:
		float ratio;
	protected:
		float increase;
	public:
		Ease();
		Ease(const float increase);
		void Initialize(const float increase);
		virtual void Update(const bool isEase);
		float In(const float start, const float end, const float power);
		float Out(const float start, const float end, const float power);
	};

	class Ease2 : public Ease
	{
	protected:
		float decrease;
	public:
		Ease2();
		Ease2(const float increase, const float decrease);
		void Initialize(const float increase, const float decrease);
		virtual void Update(const bool isEase) override;
	};

	class Ease3 : public Ease2 
	{
	public:
		enum class Extra
		{
			None,
			Back,
			Pass,
		};
	private:
		float back;
		float pass;
		Extra extra;
	public:
		Ease3();
		Ease3(const float increase, const float decrease, const float value, const Extra extra);
		void Initialize(const float increase, const float decresae, const float value, const Extra extra);
		void Update(const bool isEase);
	};
}
