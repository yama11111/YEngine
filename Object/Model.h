#pragma once
#include "Transform.h"
#include "MatViewProjection.h"
#include "Vertices.h"
#include "TextureManager.h"

namespace Object
{
	class Model
	{
	private:
		// 頂点インデックス
		DX::VertexIndex3D vtIdx;
	public:
		// コンストラクタ
		Model();
		// 描画
		void Draw(Transform& trfm, Math::MatViewProjection& vp, const UINT tex);
	private:
		// 静的テクスチャマネージャーポインタ
		static DX::TextureManager* pTexManager_;
	public:
		// 静的初期化
		static void StaticInitialize(DX::TextureManager* pTexManager);
	};
}
