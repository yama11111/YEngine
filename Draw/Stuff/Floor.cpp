#include "Floor.h"
#include <cassert>

using YGame::Floor;
using YGame::ModelObject;

void Floor::Initialize(const InitStatus& status)
{
	//for (size_t y = 0; y < status.yNum_; y++)
	//{
	//	std::vector<ModelCBSet> fs;
	//	for (size_t x = 0; x < status.xNum_; x++)
	//	{
	//		ModelCBSet f;
	//		f.Initialize({});

	//		f.scale_ = status.scale_;

	//		f.pos_ =
	//		{
	//			((f.scale_.x_ * 2.0f) * x) - ((status.xNum_ - 1) * (f.scale_.x_)),
	//			-f.scale_.y_,
	//			((f.scale_.z_ * 2.0f) * y) - ((status.yNum_ - 1) * (f.scale_.z_))
	//		};
	//		f.pos_ += status.pos_;

	//		float c = 1.0f - (((x + y) % 2 == 0) * 0.5f);
	//		//f.color_ = { c,c,c,1.0f };

	//		f.UpdateMatrix();
	//		fs.push_back(f);
	//	}
	//	objs.push_back(fs);
	//}
}

void Floor::Update()
{
	// XV
	for (size_t y = 0; y < objs_.size(); y++)
	{
		for (size_t x = 0; x < objs_[y].size(); x++)
		{
			objs_[y][x]->UpdateMatrix();
		}
	}
}

void Floor::Draw()
{
	// •`‰æ
	for (size_t y = 0; y < objs_.size(); y++)
	{
		for (size_t x = 0; x < objs_[y].size(); x++)
		{
			pModel_->Draw(objs_[y][x].get());
		}
	}
}
