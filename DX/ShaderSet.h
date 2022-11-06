#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	// シェーダーセットインターフェース
	class IShaderSet
	{
	protected:
		// シェーダーファイル読み込み
		void LoadShader(const wchar_t* fileName, const char* entryPoint, const char* target,
			ID3DBlob*& shaderBlob, ID3DBlob* errorBlob);
	private:
		// 読み込みエラー時処理
		void LoadShaderErrorProcess(ID3DBlob* errorBlob);
	};

	// スプライト用シェーダーセット
	class SpriteShaderSet : public IShaderSet
	{
	public:
		// 頂点シェーダオブジェクト
		Microsoft::WRL::ComPtr<ID3DBlob> vsBlob_ = nullptr;
		// ピクセルシェーダオブジェクト
		Microsoft::WRL::ComPtr<ID3DBlob> psBlob_ = nullptr;
	public:
		// シェーダーファイル読み込み
		void Load(ID3DBlob* errorBlob);
	};

	// モデル用シェーダーセット
	class ModelShaderSet : public IShaderSet
	{
	public:
		// 頂点シェーダオブジェクト
		Microsoft::WRL::ComPtr<ID3DBlob> vsBlob_ = nullptr;
		// ピクセルシェーダオブジェクト
		Microsoft::WRL::ComPtr<ID3DBlob> psBlob_ = nullptr;
	public:
		// シェーダーファイル読み込み
		void Load(ID3DBlob* errorBlob);
	};
}
