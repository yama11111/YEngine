//#include "Floor.h"
//#include <cassert>
//
//using YGame::ObjectModel;
//
//YGame::Model* Floor::pModel_ = nullptr;
//UINT Floor::tex_ = UINT32_MAX;
//
//void Floor::StaticIntialize(const StaticInitStatus& state)
//{
//	assert(state.pModel_);
//	pModel_ = state.pModel_;
//	tex_ = state.tex_;
//}
//
//
//void Floor::Initialize(const InitStatus& state)
//{
//	for (size_t y = 0; y < state.yNum_; y++)
//	{
//		std::vector<ObjectModel> fs;
//		for (size_t x = 0; x < state.xNum_; x++)
//		{
//			ObjectModel f;
//			f.Initialize({});
//
//			f.scale_ = state.scale_;
//
//			f.pos_ =
//			{
//				((f.scale_.x_ * 2.0f) * x) - ((state.xNum_ - 1) * (f.scale_.x_)),
//				-f.scale_.y_,
//				((f.scale_.z_ * 2.0f) * y) - ((state.yNum_ - 1) * (f.scale_.z_))
//			};
//			f.pos_ += state.pos_;
//
//			float c = 1.0f - (((x + y) % 2 == 0) * 0.5f);
//			//f.color_ = { c,c,c,1.0f };
//
//			f.UpdateMatrix();
//			fs.push_back(f);
//		}
//		objs.push_back(fs);
//	}
//}
//
//void Floor::Update()
//{
//	for (size_t y = 0; y < objs.size(); y++)
//	{
//		for (size_t x = 0; x < objs[y].size(); x++)
//		{
//			objs[y][x].UpdateMatrix();
//		}
//	}
//}
//
//void Floor::Draw(const YGame::ViewProjection& vp)
//{
//	for (size_t y = 0; y < objs.size(); y++)
//	{
//		for (size_t x = 0; x < objs[y].size(); x++)
//		{
//			//pModel_->Draw(objs[y][x], vp);
//		}
//	}
//}
