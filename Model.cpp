#include "Model.h"

ConstBufferManager* Model::cbManager = nullptr;
TextureManager* Model::texManager = nullptr;

Model::Model() :
	vtIdx(VertexIndex(
		{
			// �O
			{{ -5.0f, -5.0f, -5.0f }, {}, {0.0f, 1.0f}}, // ����
			{{ -5.0f,  5.0f, -5.0f }, {}, {0.0f, 0.0f}}, // ����
			{{  5.0f, -5.0f, -5.0f }, {}, {1.0f, 1.0f}}, // �E��
			{{  5.0f,  5.0f, -5.0f }, {}, {1.0f, 0.0f}}, // �E��

			// ��
			{{ -5.0f, -5.0f,  5.0f }, {}, {1.0f, 1.0f}}, // ����
			{{ -5.0f,  5.0f,  5.0f }, {}, {1.0f, 0.0f}}, // ����
			{{  5.0f, -5.0f,  5.0f }, {}, {0.0f, 1.0f}}, // �E��
			{{  5.0f,  5.0f,  5.0f }, {}, {0.0f, 0.0f}}, // �E��

			// ��
			{{ -5.0f, -5.0f, -5.0f }, {}, {1.0f, 1.0f}}, // ����
			{{ -5.0f, -5.0f,  5.0f }, {}, {0.0f, 1.0f}}, // ����
			{{ -5.0f,  5.0f, -5.0f }, {}, {1.0f, 0.0f}}, // �E��
			{{ -5.0f,  5.0f,  5.0f }, {}, {0.0f, 0.0f}}, // �E��

			// �E
			{{  5.0f, -5.0f, -5.0f }, {}, {0.0f, 1.0f}}, // ����
			{{  5.0f, -5.0f,  5.0f }, {}, {1.0f, 1.0f}}, // ����
			{{  5.0f,  5.0f, -5.0f }, {}, {0.0f, 0.0f}}, // �E��
			{{  5.0f,  5.0f,  5.0f }, {}, {1.0f, 0.0f}}, // �E��

			// ��
			{{ -5.0f, -5.0f,  5.0f }, {}, {0.0f, 0.0f}}, // ����
			{{ -5.0f, -5.0f, -5.0f }, {}, {0.0f, 1.0f}}, // ����
			{{  5.0f, -5.0f,  5.0f }, {}, {1.0f, 0.0f}}, // �E��
			{{  5.0f, -5.0f, -5.0f }, {}, {1.0f, 1.0f}}, // �E��

			// ��
			{{ -5.0f,  5.0f,  5.0f }, {}, {0.0f, 0.0f}}, // ����
			{{ -5.0f,  5.0f, -5.0f }, {}, {0.0f, 1.0f}}, // ����
			{{  5.0f,  5.0f,  5.0f }, {}, {1.0f, 0.0f}}, // �E��
			{{  5.0f,  5.0f, -5.0f }, {}, {1.0f, 1.0f}}, // �E��
		},
		{
			// �O
			0, 1, 2, // �O�p�`1��
			2, 1, 3, // �O�p�`2��

			// ��
			6, 7, 4, // �O�p�`1��
			4, 7, 5, // �O�p�`2��

			// ��
			8, 9, 10, // �O�p�`1��
			10, 9, 11, // �O�p�`2��

			// �E
			14, 15, 12, // �O�p�`1��
			12, 15, 13, // �O�p�`2��

			// ��
			16, 17, 18, // �O�p�`1��
			18, 17, 19, // �O�p�`2��

			//// ��
			22, 23, 20, // �O�p�`1��
			20, 23, 21, // �O�p�`2��
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
