//#pragma once
//#include "Model.h"
//#include "Lerp.h"
//#include "Timer.h"
//
//namespace YParticle
//{
//	class IParticle
//	{
//	public:
//		YGame::ObjectModel obj_;
//		bool isAlive_ = false;
//	public:
//		virtual void Update() = 0;
//	};
//
//	class Dust : public IParticle
//	{
//	private:
//		YMath::Ease<YMath::Vector3> speed_;
//		YMath::Ease<YMath::Vector3> scale_;
//		YMath::Ease<float> alpha_;
//		YMath::Timer timer_;
//	public:
//		struct EmitStatus
//		{
//			YMath::Vector3 pos_;
//			YMath::Vector3 rota_;
//			float scale_;
//			YMath::Vector3 speed_;
//			uint32_t frame_;
//		};
//	public:
//		void Emit(const EmitStatus& state);
//		void Update() override;
//	};
//
//	class Exprosion : public IParticle
//	{
//	private:
//		YMath::Ease<YMath::Vector3> rota_;
//		YMath::Ease<YMath::Vector3> scale_;
//		YMath::Ease<YMath::Vector3> speed_;
//		YMath::Vector4 color_;
//		YMath::Ease<float> alpha_;
//		YMath::Timer timer_;
//	public:
//		struct EmitStatus
//		{
//			YMath::Vector3 pos_;
//			float scale_;
//			YMath::Vector3 speed_;
//			YMath::Vector4 color_;
//			uint32_t frame_;
//		};
//	public:
//		void Emit(const EmitStatus& state);
//		void Update() override;
//	};
//
//	//class Eruption : public IParticle
//	//{
//	//private:
//	//	YMath::Ease<YMath::Vector3> pos_;
//	//	YMath::Ease<YMath::Vector3> rota_;
//	//	YMath::Ease<YMath::Vector3> scale_;
//	//	YMath::Vector4 color_;
//	//	YMath::Ease<float> alpha_;
//	//	YMath::Timer timer_;
//	//public:
//	//	struct EmitStatus
//	//	{
//	//		YMath::Ease<YMath::Vector3> pos_;
//	//		YMath::Ease<YMath::Vector3> rota_;
//	//		YMath::Ease<YMath::Vector3> scale_;
//	//		YMath::Vector4 color_;
//	//		uint32_t frame_;
//	//	};
//	//public:
//	//	void Emit(const EmitStatus& state);
//	//	void Update() override;
//	//};
//}
