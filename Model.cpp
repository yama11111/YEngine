#include "Model.h"

ConstBufferManager* Model::cbManager = nullptr;
TextureManager* Model::texManager = nullptr;

Model::Model() :
	vtIdx(VertexIndex(
		{
			// 前
			{{ -5.0f, -5.0f, -5.0f }, {}, {0.0f, 1.0f}}, // 左下
			{{ -5.0f,  5.0f, -5.0f }, {}, {0.0f, 0.0f}}, // 左上
			{{  5.0f, -5.0f, -5.0f }, {}, {1.0f, 1.0f}}, // 右下
			{{  5.0f,  5.0f, -5.0f }, {}, {1.0f, 0.0f}}, // 右上

			// 後
			{{ -5.0f, -5.0f,  5.0f }, {}, {1.0f, 1.0f}}, // 左下
			{{ -5.0f,  5.0f,  5.0f }, {}, {1.0f, 0.0f}}, // 左上
			{{  5.0f, -5.0f,  5.0f }, {}, {0.0f, 1.0f}}, // 右下
			{{  5.0f,  5.0f,  5.0f }, {}, {0.0f, 0.0f}}, // 右上

			// 左
			{{ -5.0f, -5.0f, -5.0f }, {}, {1.0f, 1.0f}}, // 左下
			{{ -5.0f, -5.0f,  5.0f }, {}, {0.0f, 1.0f}}, // 左上
			{{ -5.0f,  5.0f, -5.0f }, {}, {1.0f, 0.0f}}, // 右下
			{{ -5.0f,  5.0f,  5.0f }, {}, {0.0f, 0.0f}}, // 右上

			// 右
			{{  5.0f, -5.0f, -5.0f }, {}, {0.0f, 1.0f}}, // 左下
			{{  5.0f, -5.0f,  5.0f }, {}, {1.0f, 1.0f}}, // 左上
			{{  5.0f,  5.0f, -5.0f }, {}, {0.0f, 0.0f}}, // 右下
			{{  5.0f,  5.0f,  5.0f }, {}, {1.0f, 0.0f}}, // 右上

			// 下
			{{ -5.0f, -5.0f,  5.0f }, {}, {0.0f, 0.0f}}, // 左下
			{{ -5.0f, -5.0f, -5.0f }, {}, {0.0f, 1.0f}}, // 左上
			{{  5.0f, -5.0f,  5.0f }, {}, {1.0f, 0.0f}}, // 右下
			{{  5.0f, -5.0f, -5.0f }, {}, {1.0f, 1.0f}}, // 右上

			// 上
			{{ -5.0f,  5.0f,  5.0f }, {}, {0.0f, 0.0f}}, // 左下
			{{ -5.0f,  5.0f, -5.0f }, {}, {0.0f, 1.0f}}, // 左上
			{{  5.0f,  5.0f,  5.0f }, {}, {1.0f, 0.0f}}, // 右下
			{{  5.0f,  5.0f, -5.0f }, {}, {1.0f, 1.0f}}, // 右上
		},
		{
			// 前
			0, 1, 2, // 三角形1つ目
			2, 1, 3, // 三角形2つ目

			// 後
			6, 7, 4, // 三角形1つ目
			4, 7, 5, // 三角形2つ目

			// 左
			8, 9, 10, // 三角形1つ目
			10, 9, 11, // 三角形2つ目

			// 右
			14, 15, 12, // 三角形1つ目
			12, 15, 13, // 三角形2つ目

			// 下
			16, 17, 18, // 三角形1つ目
			18, 17, 19, // 三角形2つ目

			//// 上
			22, 23, 20, // 三角形1つ目
			20, 23, 21, // 三角形2つ目
		}
		))
{
	vtIdx.Init();

	cbManager->CreateCB(cbM);
	cbManager->CreateCB(cbT);
}

void Model::Draw(MatWorld& mW, MatViewProjection& mVP, const UINT tex)
{
	cbT.cMapTrfm->mat = mW.m * mVP.view.m * mVP.pro.m;
	vtIdx.SetCommand();
	cbManager->SetCommand(cbM);
	cbManager->SetCommand(cbT);
	texManager->SetCommand(tex);
	vtIdx.Draw();
}

void Model::StaticInit() 
{
	cbManager = ConstBufferManager::GetInstance();
	texManager = TextureManager::GetInstance();
}
