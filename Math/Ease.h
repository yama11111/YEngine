#pragma once

namespace Math
{
	class Ease
	{
	public:
		float ratio;
	protected:
		float increase;
		float decrease;
	public:
		Ease();
		Ease(const float increase, const float decrease);
		void Initialize(const float increase, const float decrease);
		virtual void Update(const bool isEase);
		float In(const float start, const float end, const float power);
		float Out(const float start, const float end, const float power);
	};

	class Ease2 : public Ease 
	{
	public:
		enum Extra
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
		Ease2();
		Ease2(const float increase, const float decrease, const float value, const Extra extra);
		void Initialize(const float increase, const float decresae, const float value, const Extra extra);
		void Update(const bool isEase);
	};
}
