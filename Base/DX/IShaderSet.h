#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	class IShaderSet
	{

	public:

		/// <summary>
		/// シェーダーファイル読み込み
		/// </summary>
		virtual void Load() = 0;

	protected:
		
		/// <summary>
		/// シェーダーファイル読み込み
		/// </summary>
		/// <param name="fileName"> : シェーダーファイル名</param>
		/// <param name="entryPoint"> : エントリーポイント (main)</param>
		/// <param name="target"> : ターゲット (種類 + バージョン)</param>
		/// <param name="shaderBlob"> : シェーダーオブジェクト</param>
		/// <param name="errorBlob"> : エラー用</param>
		void LoadShader(const wchar_t* fileName, const char* entryPoint, const char* target,
			ID3DBlob*& shaderBlob, ID3DBlob* errorBlob);
	
	private:
		
		/// <summary>
		/// 読み込みエラー時処理
		/// </summary>
		/// <param name="errorBlob"> : エラー用</param>
		void LoadErrorProcess(ID3DBlob* errorBlob);

	};
}
