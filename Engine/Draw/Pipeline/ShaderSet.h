#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <string>
#include <unordered_map>

namespace YGame
{
	class ShaderSet
	{

	public:

		// シェーダーの種類
		enum class ShaderType
		{
			// 頂点シェーダー
			eVertex,
			
			// ジオメトリシェーダー
			eGeometry,

			// ピクセルシェーダー
			ePixel,
		};

	public:

		/// <summary>
		/// シェーダーファイル読み込み
		/// </summary>
		/// <param name="shaderFileName"> : シェーダーの種類</param>
		/// <param name="type"> : シェーダーの種類</param>
		void LoadShader(const std::string& shaderFileName, const ShaderType type);

		/// <summary>
		/// シェーダーポインタ取得
		/// </summary>
		/// <param name="type"> : シェーダーの種類</param>
		/// <returns>シェーダーポインタ</returns>
		ID3DBlob* ShaderPtr(const ShaderType type);

	private:

		// シェーダー格納配列
		std::unordered_map<
			ShaderType,
			Microsoft::WRL::ComPtr<ID3DBlob>> shaders_;

	private:

		/// <summary>
		/// シェーダーオブジェクト読み込み
		/// </summary>
		/// <param name="fileName"> : シェーダーファイル名</param>
		/// <param name="entryPoint"> : エントリーポイント (main)</param>
		/// <param name="target"> : ターゲット (種類 + バージョン)</param>
		/// <param name="shaderBlob"> : シェーダーオブジェクト</param>
		/// <param name="errorBlob"> : エラー用</param>
		void CreateShaderObject(
			const wchar_t* fileName,
			const char* entryPoint,
			const char* target,
			ID3DBlob*& shaderBlob,
			ID3DBlob* errorBlob);

		/// <summary>
		/// 読み込みエラー時処理
		/// </summary>
		/// <param name="errorBlob"> : エラー用</param>
		void LoadErrorProcess(ID3DBlob* errorBlob);

	};
}
