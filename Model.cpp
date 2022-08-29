#include "Model.h"
TextureManager* Model::texManager = nullptr;

Model::Model() :
	vtIdx(VertexIndex(
		{
			// �O
			{{ -1.0f, -1.0f, -1.0f }, {}, {0.0f, 1.0f}}, // ����
			{{ -1.0f,  1.0f, -1.0f }, {}, {0.0f, 0.0f}}, // ����
			{{  1.0f, -1.0f, -1.0f }, {}, {1.0f, 1.0f}}, // �E��
			{{  1.0f,  1.0f, -1.0f }, {}, {1.0f, 0.0f}}, // �E��

			// ��
			{{ -1.0f, -1.0f,  1.0f }, {}, {1.0f, 1.0f}}, // ����
			{{ -1.0f,  1.0f,  1.0f }, {}, {1.0f, 0.0f}}, // ����
			{{  1.0f, -1.0f,  1.0f }, {}, {0.0f, 1.0f}}, // �E��
			{{  1.0f,  1.0f,  1.0f }, {}, {0.0f, 0.0f}}, // �E��

			// ��
			{{ -1.0f, -1.0f, -1.0f }, {}, {1.0f, 1.0f}}, // ����
			{{ -1.0f, -1.0f,  1.0f }, {}, {0.0f, 1.0f}}, // ����
			{{ -1.0f,  1.0f, -1.0f }, {}, {1.0f, 0.0f}}, // �E��
			{{ -1.0f,  1.0f,  1.0f }, {}, {0.0f, 0.0f}}, // �E��

			// �E
			{{  1.0f, -1.0f, -1.0f }, {}, {0.0f, 1.0f}}, // ����
			{{  1.0f, -1.0f,  1.0f }, {}, {1.0f, 1.0f}}, // ����
			{{  1.0f,  1.0f, -1.0f }, {}, {0.0f, 0.0f}}, // �E��
			{{  1.0f,  1.0f,  1.0f }, {}, {1.0f, 0.0f}}, // �E��

			// ��
			{{ -1.0f, -1.0f,  1.0f }, {}, {0.0f, 0.0f}}, // ����
			{{ -1.0f, -1.0f, -1.0f }, {}, {0.0f, 1.0f}}, // ����
			{{  1.0f, -1.0f,  1.0f }, {}, {1.0f, 0.0f}}, // �E��
			{{  1.0f, -1.0f, -1.0f }, {}, {1.0f, 1.0f}}, // �E��

			// ��
			{{ -1.0f,  1.0f,  1.0f }, {}, {0.0f, 0.0f}}, // ����
			{{ -1.0f,  1.0f, -1.0f }, {}, {0.0f, 1.0f}}, // ����
			{{  1.0f,  1.0f,  1.0f }, {}, {1.0f, 0.0f}}, // �E��
			{{  1.0f,  1.0f, -1.0f }, {}, {1.0f, 1.0f}}, // �E��
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
	vtIdx.Init(true);
}

void Model::Draw(Object3D& obj, MatViewProjection& mVP, const UINT tex)
{
	obj.Affine(mVP);
	vtIdx.SetCommand();
	obj.SetCommand();
	texManager->SetCommand(tex);
	vtIdx.Draw();
}

void Model::StaticInit() 
{
	texManager = TextureManager::GetInstance();
}